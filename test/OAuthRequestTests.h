#include <OAuthRequest.h>

namespace OAuthTesting
{
    class OAuthRequestTests : public testing::Test
    {
    };

    TEST(OAuthRequestTests, testParameters)
    {
        std::string url = "http://example.com/request?b5=%3D%253D&a3=a&c%40=&a2=r%20b";
        OAuth::OAuthRequest request(OAuth::POST, url);

        ASSERT_THROW(request.addOAuthParameter("without_prefix", "value"), std::invalid_argument);
        request.addOAuthParameter("oauth_timestamp", "1356312");
        ASSERT_STREQ("?oauth_timestamp=1356312",
                request.getOAuthParameters().asQueryString().c_str());
    }
}
