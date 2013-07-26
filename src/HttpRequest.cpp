#include <HttpRequest.h>

#include <cassert>

namespace OAuth
{
    const std::string HttpRequest::httpVersionString = "HTTP/1.1";

    const std::string &HttpRequest::getBody() const
    {
        return body;
    }

    void HttpRequest::setBody(const std::string &body)
    {
        this->body = body;
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

    void HttpRequest::setHttpRequestType(HttpRequestType httpRequestType)
    {
        this->httpRequestType = httpRequestType;
    }

    const std::string &HttpRequest::getResource() const
    {
        return resource;
    }

    void HttpRequest::setResource(const std::string &resource)
    {
        this->resource = resource;
    }

    std::string HttpRequest::requestTypeAsString()
    {
        switch (httpRequestType) {
        case HttpRequestType::GET:
            return "GET";
        case HttpRequestType::POST:
            return "POST";
        default:
            assert("Unknown method" && false);
        }
    }

    void HttpRequest::setHeader(const std::string &name, const std::string &header)
    {
        this->headers[name] = header;
    }

    void HttpRequest::eraseHeader(const std::string &name)
    {
        auto header = headers.find(name);
        if (header != headers.end())
            headers.erase(header);
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
