#include <ParameterList.h>

namespace OAuthTesting
{
    class ParameterListTests : public testing::Test
    {
    };

    TEST(ParameterListTests, testAdd)
    {
        OAuth::ParameterList parameterList;
        parameterList.add("oauth_nonce", "1234567");
        ASSERT_STREQ("?oauth_nonce=1234567", parameterList.asQueryString().c_str());
        parameterList.add("oauth_timestamp", "17645612654");
        ASSERT_STREQ("?oauth_nonce=1234567&oauth_timestamp=17645612654",
                parameterList.asQueryString().c_str());
    }

    TEST(ParameterListTests, testAddQueryString)
    {
        OAuth::ParameterList parameterList;
        ASSERT_STREQ("?", parameterList.asQueryString().c_str());

        std::string queryString = "?oauth_consumer_key=key&oauth_secret=secret";
        parameterList.addQueryString(queryString);
        ASSERT_STREQ(queryString.c_str(), parameterList.asQueryString().c_str());

        std::string anotherQueryString = "oauth_signature=1qwe3f&oauth_version=1.0";
        parameterList.addQueryString(anotherQueryString);
        ASSERT_STREQ(queryString.append('&' + anotherQueryString).c_str(),
                parameterList.asQueryString().c_str());
    }

    TEST(ParameterListTests, testBaseString)
    {
        OAuth::ParameterList parameterList;
        ASSERT_STREQ("", parameterList.asBaseString().c_str());

        // Test sorting
        parameterList.addQueryString("c1=a3&a2=a3&a2=a1");
        ASSERT_STREQ("a2=a1&a2=a3&c1=a3", parameterList.asBaseString().c_str());
        parameterList.add("a0", "");
        ASSERT_STREQ("a0=&a2=a1&a2=a3&c1=a3", parameterList.asBaseString().c_str());
    }

    TEST(ParameterListTests, testBaseStringEncoding)
    {
        // Example from [RFC 5849 3.4.1.3.1. Parameter Sources]
        std::string queryString = "?b5=%3D%253D&a3=a&c%40=&a2=r%20b"
                "&oauth_consumer_key=9djdj82h48djs9d2"
                "&oauth_token=kkk9d7dh3k39sjv7"
                "&oauth_signature_method=HMAC-SHA1"
                "&oauth_timestamp=137131201"
                "&oauth_nonce=7d8f3e4a"
                "&c2&a3=2+q";
        std::string expectedBaseString = "a2=r%20b&a3=2%20q&a3=a&b5="
                "%3D%253D&c%40=&c2=&oauth_consumer_key=9dj"
                "dj82h48djs9d2&oauth_nonce=7d8f3e4a"
                "&oauth_signature_method=HMAC-SHA1"
                "&oauth_timestamp=137131201&oauth_token=kkk9d7dh3k39sjv7";

        OAuth::ParameterList parameterList(queryString);
        ASSERT_STREQ(expectedBaseString.c_str(), parameterList.asBaseString().c_str());
    }
}
