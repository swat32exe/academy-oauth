#include <cassert>
#include <stdexcept>

#include "HttpRequest.h"
#include "Utility.h"

namespace OAuth
{
    HttpRequest::HttpRequest(HttpRequestType httpRequestType, const std::string &url)
    {
        requestType = httpRequestType;
        this->setUrl(url);
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
            queryParameters.addQueryString(url.substr(queryPosition));
        } else {
            this->url = url;
        }
    }

    const std::string HttpRequest::getUrl() const
    {
        return url + queryParameters.asQueryString();
    }

    const std::string HttpRequest::getBaseStringUri() const
    {
        return Utility::urlEncode(url);
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
        bodyParameters.add(name, value);
    }

    const ParameterList &HttpRequest::getBodyParameters() const
    {
        return bodyParameters;
    }

    const std::string HttpRequest::getBody() const
    {
        return bodyParameters.asQueryString().substr(1);
    }

    void HttpRequest::addQueryParameter(const std::string &name, const std::string &value)
    {
        queryParameters.add(name, value);
    }

    const ParameterList &HttpRequest::getQueryParameters() const
    {
        return queryParameters;
    }
}
