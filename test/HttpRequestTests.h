#include <HttpRequest.h>

namespace OAuth
{
    class HttpRequestTests: public testing::Test
    {
    };

    TEST_F(HttpRequestTests, http_request_test1)
    {
        std::string plaintextRequest =
            "GET /js/jquery.js HTTP/1.1\r\n"
            "Accept: */*\r\n"
            "Accept-Encoding: gzip,deflate,sdch\r\n"
            "Accept-Language: en-US,en;q=0.8,ru;q=0.6,uk;q=0.4\r\n"
            "Connection: keep-alive\r\n"
            "Host: www.requestmaker.com\r\n"
            "Referer: http://www.requestmaker.com/\r\n"
            "User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/28.0.1500.72 Safari/537.36\r\n"
            "\r\n"
            "body";

        header_t headers;
        headers["Accept"] = "*/*";
        headers["Accept-Encoding"] = "gzip,deflate,sdch";
        headers["Accept-Language"] = "en-US,en;q=0.8,ru;q=0.6,uk;q=0.4";
        headers["Connection"] = "keep-alive";
        headers["Host"] = "www.requestmaker.com";
        headers["Referer"] = "http://www.requestmaker.com/";
        headers["User-Agent"] = "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/28.0.1500.72 Safari/537.36";

        HttpRequest httpRequest(HttpRequestType::GET, "/js/jquery.js",headers ,"body");

        ASSERT_EQ(HttpRequestType::GET, httpRequest.getHttpRequestType());
        ASSERT_EQ("/js/jquery.js", httpRequest.getResource());
        ASSERT_EQ(headers, httpRequest.getHeaders());
        ASSERT_EQ("body", httpRequest.getBody());

        ASSERT_EQ(plaintextRequest, httpRequest.toString());
    }
}
