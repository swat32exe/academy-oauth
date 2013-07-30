#include <HttpRequest.h>

#include <cassert>

namespace OAuth
{
    const std::string HttpRequest::httpVersionString = "HTTP/1.1";

    const std::string &HttpRequest::getBody() const
    {
        return body;
    }

    const header_t &HttpRequest::getHeaders() const
    {
        return headers;
    }

    header_t &HttpRequest::getHeadersNonConst()
    {
        return headers;
    }

    HttpRequestType HttpRequest::getHttpRequestType() const
    {
        return httpRequestType;
    }

    const std::string &HttpRequest::getResource() const
    {
        return resource;
    }

    std::string HttpRequest::requestTypeAsString()
    {
        switch (httpRequestType) {
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

    HttpRequest::HttpRequest(HttpRequestType httpRequestType
            ,const std::string &resource
            ,const header_t &headers
            ,const std::string &body) :
        httpRequestType(httpRequestType)
        ,resource(resource)
        ,headers(headers)
        ,body(body)
    {
    }

    std::string HttpRequest::toString()
    {
        std::string asString = requestTypeAsString() + " " + resource + " " + httpVersionString + "\r\n";

        for (auto header : headers) {
            asString += header.first + ": " + header.second + "\r\n";
        }

        asString += "\r\n" + body;

        return asString;
    }

}
