#include <cassert>
#include <stdexcept>

#include "HttpRequest.h"
#include "utility/Url.h"

namespace OAuth
{
    const std::string HttpRequest::FORM_URLENCODED = "application/x-www-form-urlencoded";
    const std::string HttpRequest::HEADER_CONTENT_TYPE = "Content-Type";

    HttpRequest::HttpRequest(HttpRequestType httpRequestType, const std::string &url)
    {
        requestType = httpRequestType;
        this->setUrl(url);
        headers[HEADER_CONTENT_TYPE] = FORM_URLENCODED;
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

    void HttpRequest::setBody(const std::string &body)
    {
        this->body = body;
    }

    const std::string &HttpRequest::getBody() const
    {
        return body;
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
