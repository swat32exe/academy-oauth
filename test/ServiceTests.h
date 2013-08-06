#include <gtest/gtest.h>

#include <Service.h>
#include <ServiceConfiguration.h>

#include "SendRequest.h"


namespace OAuth
{
    class ServiceTests: public testing::Test
    {
    };

    TEST_F(ServiceTests, request_temporary_credentials_hmac_sha1)
    {
        OAuth::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php"
            ,"http://example.com/auth"
            ,"http://term.ie/oauth/example/access_token.php"
            ,"key"
            ,"secret"
            ,"http://example.com/callback"
            ,OAuth::SignatureMethod::HMAC_SHA1);
        OAuth::Service service(configuration, sendRequest);
        std::future<Token> futureToken = service.getRequestToken();
        Token token = futureToken.get();
        ASSERT_EQ("requestkey", token.getToken());
        ASSERT_EQ("requestsecret", token.getSecret());
    }
}
