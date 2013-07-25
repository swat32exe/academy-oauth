#ifndef HTTPREQUEST_H_
#define HTTPREQUEST_H_

#include <string>
#include <vector>
#include <map>

namespace OAuth
{
    class HttpRequest
    {
        std::string initialLine;
        std::map<std::string, std::string> headers;
        std::string body;

        void addHeadersFrom(std::string headersString);
    public:
        HttpRequest(const std::string &httpRequest);
        std::string ToString();

        const std::string &getBody() const;
        void setBody(const std::string &body);
        std::string getHeader(const std::string &header) const;
        void setHeader(std::string &name, const std::string &header);
        const std::string &getInitialLine() const;
        void setInitialLine(const std::string &initialLine);
    };
}

#endif
