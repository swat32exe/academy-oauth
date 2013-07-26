#ifndef HTTPREQUEST_H_
#define HTTPREQUEST_H_

#include <string>
#include <vector>
#include <map>

namespace OAuth
{
    typedef std::map<std::string, std::string> header_t;
    enum HttpRequestType { GET, POST };

    /**
     *  Class for working with HTTP requests.
     */
    class HttpRequest
    {
        const static std::string httpVersionString;

        HttpRequestType httpRequestType;
        /**
         *  Url path after host and port, e.g /index.php?p1=1
         */
        std::string resource;
        header_t headers;
        std::string body;

        /**
         *  Creates string representation of request type.
         *  e.g. "POST" for HttpRequestType::POST.
         */
        std::string requestTypeAsString();
    public:
        HttpRequest(HttpRequestType httpRequestType
            ,const std::string &resource
            ,const header_t &headers
            ,const std::string &body);
        /**
         * Creates string, that is ready to be sent.
         */
        std::string toString();

        HttpRequestType getHttpRequestType() const;
        const std::string &getResource() const;
        const std::string &getBody() const;
        const header_t &getHeaders() const;
        /**
         *  Returns non-constant reference to headers structure, so headers can be edited.
         */
        header_t &getHeadersNonConst();
    };
}

#endif
