#include <utility/Extractor.h>
#include <oauth/ParameterList.h>

#include <string>

namespace OAuthTesting
{
    class ExtractorTests : public testing::Test
    {
    };

    TEST(ExtractorTests, testBaseString)
    {
        OAuth::ParameterList parameterList;
        ASSERT_STREQ("", OAuth::Utility::extractBaseString(parameterList).c_str());

        // Test sorting
        parameterList.addQueryString("c1=a3&a2=a3&a2=a1");
        std::string baseString = OAuth::Utility::extractBaseString(parameterList);
        ASSERT_STREQ("a2%3Da1%26a2%3Da3%26c1%3Da3", baseString.c_str());
        parameterList.add("a0", "");
        baseString = OAuth::Utility::extractBaseString(parameterList);
        ASSERT_STREQ("a0%3D%26a2%3Da1%26a2%3Da3%26c1%3Da3", baseString.c_str());
    }

    TEST(ExtractorTests, testBaseStringEncoding)
    {
        // Example from [RFC 5849 3.4.1.3.1. Parameter Sources]
        std::string queryString = "?b5=%3D%253D&a3=a&c%40=&a2=r%20b"
                "&oauth_consumer_key=9djdj82h48djs9d2"
                "&oauth_token=kkk9d7dh3k39sjv7"
                "&oauth_signature_method=HMAC-SHA1"
                "&oauth_timestamp=137131201"
                "&oauth_nonce=7d8f3e4a"
                "&c2&a3=2+q";
        std::string expectedBaseString = "a2%3Dr%2520b%26a3%3D2%2520q%26a3%3Da%26b5%3D"
                "%253D%25253D%26c%2540%3D%26c2%3D%26oauth_consumer_key%3D9dj"
                "dj82h48djs9d2%26oauth_nonce%3D7d8f3e4a"
                "%26oauth_signature_method%3DHMAC-SHA1"
                "%26oauth_timestamp%3D137131201%26oauth_token%3Dkkk9d7dh3k39sjv7";

        OAuth::ParameterList parameterList(queryString);
        ASSERT_STREQ(expectedBaseString.c_str(),
                OAuth::Utility::extractBaseString(parameterList).c_str());
    }
}
