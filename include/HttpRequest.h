#ifndef HTTPREQUEST_H_
#define HTTPREQUEST_H_

#include <string>
#include <vector>
#include <map>

namespace OAuth
{
    typedef std::map<std::string, std::string> header_t;
    enum HttpRequestType { GET, POST };

    class HttpRequest
    {
        const static std::string httpVersionString;

        HttpRequestType httpRequestType;
        std::string resource;
        header_t headers;
        std::string body;

        std::string requestTypeAsString();
    public:
        HttpRequest(HttpRequestType httpRequestType
            ,const std::string &resource
            ,const header_t &headers
            ,const std::string &body);
        std::string toString();

        HttpRequestType getHttpRequestType() const;
        void setHttpRequestType(HttpRequestType httpRequestType);
        const std::string &getResource() const;
        void setResource(const std::string &resource);
        const std::string &getBody() const;
        void setBody(const std::string &body);
        const header_t &getHeaders() const;
        void setHeader(const std::string &name, const std::string &header);
        void eraseHeader(const std::string &name);
    };
}

#endif
