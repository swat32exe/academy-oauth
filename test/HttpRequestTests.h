#include <string>

#include <HttpRequest.h>
#include <ParameterList.h>

namespace OAuthTesting
{
    class HttpRequestTests: public testing::Test
    {
    };

    TEST(HttpRequestTests, testRequestType)
    {
        OAuth::HttpRequest request(OAuth::POST,
                "http://example.com/request?b5=%3D%253D&a3=a&c%40=&a2=r%20b");
        ASSERT_EQ(OAuth::POST, request.getRequestType());
        ASSERT_STREQ("POST", request.getRequestTypeAsString().c_str());
    }

    TEST(HttpRequestTests, testUrl)
    {
        std::string url = "http://example.com/request?b5=%3D%253D&a3=a&c%40=&a2=r%20b";
        OAuth::HttpRequest request(OAuth::POST, url);
        ASSERT_STREQ(url.c_str(), request.getUrl().c_str());
        ASSERT_STREQ("http://example.com/request", request.getBaseStringUri().c_str());

        request.addQueryParameter("q", "1");
        ASSERT_STREQ((url + "&q=1").c_str(), request.getUrl().c_str());
    }

    TEST(HttpRequestTests, testParameters)
    {
        std::string url = "http://example.com/request?b5=%3D%253D&a3=a&c%40=&a2=r%20b";
        OAuth::HttpRequest request(OAuth::POST, url);

        OAuth::ParameterList queryList = request.getQueryParameters();
        ASSERT_STREQ("?b5=%3D%253D&a3=a&c%40=&a2=r%20b", queryList.asQueryString().c_str());

        ASSERT_THROW(request.addOAuthParameter("without_prefix", "value"), std::invalid_argument);
        request.addOAuthParameter("oauth_timestamp", "1356312");
        ASSERT_STREQ("?oauth_timestamp=1356312",
                request.getOAuthParameters().asQueryString().c_str());

        request.addBodyParameter("a2", "q1");
        request.addBodyParameter("b5", "%3D%253D");
        ASSERT_STREQ("a2=q1&b5=%3D%253D", request.getBody().c_str());
    }
}
