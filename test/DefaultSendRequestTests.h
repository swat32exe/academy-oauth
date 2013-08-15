#include <gtest/gtest.h>
#include <regex>

#include <oauth/DefaultSendRequest.h>

namespace OAuth
{
    class DefaultSendRequestTests: public testing::Test
    {
    };

    TEST_F(DefaultSendRequestTests, send_request_test_post_1)
    {
        HttpRequest request(POST, "http://httpbin.org/post");
        request.addHeader("Some-Wierd-Header", "some_data");
        request.setBody("testParameter=value");
        std::string response = defaultSendRequest(request);

        std::regex hasTestHeader(".*\"Some-Wierd-Header\": \"some_data\".*");
        std::regex correctData(".*\"testParameter\": \"value\".*");

        ASSERT_TRUE(std::regex_match(response, hasTestHeader));
        ASSERT_TRUE(std::regex_match(response, correctData));
    }

    TEST_F(DefaultSendRequestTests, send_request_test_get_1)
    {
        HttpRequest request(GET, "http://httpbin.org/get?parameter=value");
        request.addHeader("Some-Wierd-Header", "some_data");
        std::string response = defaultSendRequest(request);

        std::regex hasTestHeader(".*\"Some-Wierd-Header\": \"some_data\".*");
        std::regex correctParameter(".*\"parameter\": \"value\".*");

        ASSERT_TRUE(std::regex_match(response, hasTestHeader));
        ASSERT_TRUE(std::regex_match(response, correctParameter));
    }
}
