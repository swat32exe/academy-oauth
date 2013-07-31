#include <cassert>
#include <stdexcept>

#include "HttpRequest.h"
#include "ParameterList.h"

namespace OAuth
{
    const std::string HttpRequest::OAUTH_PREFIX = "oauth_";
    const std::string HttpRequest::DEFAULT_CONTENT_TYPE = "x-www-form-urlencoded";

    HttpRequest::HttpRequest(HttpRequestType httpRequestType, const std::string &url)
    {
        this->init(httpRequestType, url);
    }

    HttpRequest::HttpRequest(const HttpRequest &request)
    {
        this->init(request.requestType, request.getUrl());
        bodyParameters->add(request.getBodyParameters());
        queryParameters->add(request.getQueryParameters());
        oauthParameters->add(request.getOAuthParameters());
    }

    void HttpRequest::init(HttpRequestType httpRequestType, const std::string &url)
    {
        bodyParameters = std::unique_ptr<ParameterList>(new ParameterList());
        queryParameters = std::unique_ptr<ParameterList>(new ParameterList());
        oauthParameters = std::unique_ptr<ParameterList>(new ParameterList());

        requestType = httpRequestType;
        this->setUrl(url);
        this->addHeader("Content-Type", DEFAULT_CONTENT_TYPE);
    }

    std::string HttpRequest::getRequestTypeAsString() const
    {
        switch (requestType) {
        case GET:
            return "GET";
        case POST:
            return "POST";
        default:
            assert("Unknown method" && false);
            // Just to avoid warning.
            return "";
        }
    }

    HttpRequestType HttpRequest::getRequestType() const
    {
        return requestType;
    }

    void HttpRequest::setUrl(const std::string &url)
    {
        size_t queryPosition = url.find(ParameterList::QUERY_SEPARATOR);
        if (queryPosition != std::string::npos) {
            this->url = url.substr(0, queryPosition);
            queryParameters->addQueryString(url.substr(queryPosition));
        } else {
            this->url = url;
        }
    }

    const std::string HttpRequest::getUrl() const
    {
        return url + queryParameters->asQueryString();
    }

    const std::string HttpRequest::getBaseStringUri() const
    {
        return url;
    }

    void HttpRequest::addHeader(const std::string &name, const std::string &value)
    {
        headers[name] = value;
    }

    const header_t &HttpRequest::getHeaders() const
    {
        return headers;
    }

    void HttpRequest::addBodyParameter(const std::string &name, const std::string &value)
    {
        bodyParameters->add(name, value);
    }

    const ParameterList &HttpRequest::getBodyParameters() const
    {
        return *bodyParameters.get();
    }

    const std::string HttpRequest::getBody() const
    {
        return bodyParameters->asQueryString().substr(1);
    }

    void HttpRequest::addQueryParameter(const std::string &name, const std::string &value)
    {
        queryParameters->add(name, value);
    }

    const ParameterList &HttpRequest::getQueryParameters() const
    {
        return *queryParameters.get();
    }

    void HttpRequest::addOAuthParameter(const std::string &name, const std::string &value)
    {
        if (name.find(OAUTH_PREFIX) != 0) {
            throw std::invalid_argument("Name must start with \"" + OAUTH_PREFIX);
        }

        oauthParameters->add(name, value);
    }

    const ParameterList &HttpRequest::getOAuthParameters() const
    {
        return *oauthParameters.get();
    }
}
