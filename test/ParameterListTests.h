#include <oauth/ParameterList.h>

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
}
