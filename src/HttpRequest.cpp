#include <HttpRequest.h>

#include <iostream>
#include <regex>

namespace OAuth
{
    const std::string &HttpRequest::getBody() const
    {
        return body;
    }

    void HttpRequest::setBody(const std::string &body)
    {
        this->body = body;
    }

    std::string HttpRequest::getHeader(const std::string &name) const
    {
        auto header = headers.find(name);
        if (header == headers.end())
            return "";
        return header->second;
    }

    void HttpRequest::setHeader(std::string &name, const std::string &header)
    {
        this->headers[name] = header;
    }

    const std::string& HttpRequest::getInitialLine() const
    {
        return initialLine;
    }

    void HttpRequest::addHeadersFrom(std::string headersString)
    {
        headersString = "";
        // TODO:Implement
    }

    void HttpRequest::setInitialLine(const std::string &initialLine)
    {
        this->initialLine = initialLine;
    }

    HttpRequest::HttpRequest(const std::string &httpRequest)
    {
        int initialLineEndPosition = httpRequest.find("\r\n");
        initialLine = httpRequest.substr(0, initialLineEndPosition);

        int headersStartPosition = initialLineEndPosition + 2;
        int headersEndPosition = httpRequest.find("\r\n\r\n");
        int headersLength = headersStartPosition - headersEndPosition + 1;
        std::string headers = httpRequest.substr(headersStartPosition, headersLength);

        addHeadersFrom(headers);

        // There are 4 characters after headers before body
        body = httpRequest.substr(headersEndPosition + 4);
    }

    std::string HttpRequest::ToString()
    {
        std::string asString = initialLine + "\r\n";

        for (auto header : headers) {
            asString += header.first + ": " + header.second + "\r\n";
        }

        asString += "\r\n" + body;

        return asString;
    }

}
