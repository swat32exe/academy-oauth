#include <gtest/gtest.h>
#include <regex>

#include "SendRequest.h"

namespace OAuth
{
    class SendRequestTests: public testing::Test
    {
    };

    TEST_F(SendRequestTests, send_request_test_post_1)
    {
        header_t headers;
        headers["host"] = "httpbin.org";
        headers["Some-Wierd-Header"] = "some_data";
        HttpRequest request(POST, "/post", headers, "Hello, world!");
        std::string response = sendRequest(request);

        std::regex hasTestHeader(".*\"Some-Wierd-Header\": \"some_data\".*");
        std::regex correctData(".*\"data\": \"Hello, world!\".*");

        ASSERT_TRUE(std::regex_match(response, hasTestHeader));
        ASSERT_TRUE(std::regex_match(response, correctData));
    }

    TEST_F(SendRequestTests, send_request_test_get_1)
    {
        header_t headers;
        headers["host"] = "httpbin.org";
        headers["Some-Wierd-Header"] = "some_data";
        HttpRequest request(GET, "/get?parameter=value", headers, "Hello, world!");
        std::string response = sendRequest(request);

        std::regex hasTestHeader(".*\"Some-Wierd-Header\": \"some_data\".*");
        std::regex correctParameter(".*\"parameter\": \"value\".*");

        ASSERT_TRUE(std::regex_match(response, hasTestHeader));
        ASSERT_TRUE(std::regex_match(response, correctParameter));
    }
}
