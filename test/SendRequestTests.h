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
        HttpRequest request(POST, "http://httpbin.org/post");
        request.addHeader("Some-Wierd-Header", "some_data");
        request.addBodyParameter("testParameter","value");
        std::string response = sendRequest(request);

        std::regex hasTestHeader(".*\"Some-Wierd-Header\": \"some_data\".*");
        std::regex correctData(".*\"testParameter\": \"value\".*");

        ASSERT_TRUE(std::regex_match(response, hasTestHeader));
        ASSERT_TRUE(std::regex_match(response, correctData));
    }

    TEST_F(SendRequestTests, send_request_test_get_1)
    {
        HttpRequest request(GET, "http://httpbin.org/get?parameter=value");
        request.addHeader("Some-Wierd-Header", "some_data");
        std::string response = sendRequest(request);

        std::regex hasTestHeader(".*\"Some-Wierd-Header\": \"some_data\".*");
        std::regex correctParameter(".*\"parameter\": \"value\".*");

        ASSERT_TRUE(std::regex_match(response, hasTestHeader));
        ASSERT_TRUE(std::regex_match(response, correctParameter));
    }
}
