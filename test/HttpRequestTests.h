#include <HttpRequest.h>

namespace OAuth
{
    class DefaultBillingRulesTests: public testing::Test
    {
    };

    TEST_F(DefaultBillingRulesTests, t)
    {
        std::string plaintextRequest =
            "GET /js/jquery.js HTTP/1.1\r\n"
            "Host: www.requestmaker.com\r\n"
            "Connection: keep-alive\r\n"
            "Accept: */*\r\n"
            "User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/28.0.1500.72 Safari/537.36\r\n"
            "Referer: http://www.requestmaker.com/\r\n"
            "Accept-Encoding: gzip\r\n"
            "Accept-Encoding: deflate,sdch\r\n"
            "Accept-Language: en-US,en;q=0.8,ru;q=0.6,uk;q=0.4\r\n"
            "\r\n";
        HttpRequest httpRequest(plaintextRequest);

        ASSERT_EQ("GET /js/jquery.js HTTP/1.1", httpRequest.getInitialLine());
        ASSERT_EQ("", httpRequest.getBody());
        ASSERT_EQ("www.requestmaker.com", httpRequest.getHeader("Host"));
        ASSERT_EQ("gzip,deflate,sdch", httpRequest.getHeader("Accept-Encoding"));
    }
}
