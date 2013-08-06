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

    TEST_F(ServiceTests, get_authorize_url_no_parameters)
    {
        Token token("tokenkey","tokensecret");
        OAuth::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php"
            ,"http://example.com/auth"
            ,"http://term.ie/oauth/example/access_token.php"
            ,"key"
            ,"secret"
            ,"http://example.com/callback"
            ,OAuth::SignatureMethod::HMAC_SHA1);
        OAuth::Service service(configuration, sendRequest);
        ASSERT_EQ("http://example.com/auth?oauth_token=tokenkey", service.getAuthorizeUrl(token));
    }

    TEST_F(ServiceTests, get_authorize_url_has_parameters)
    {
        Token token("tokenkey","tokensecret");
        OAuth::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php"
            ,"http://example.com/auth?some=parameter"
            ,"http://term.ie/oauth/example/access_token.php"
            ,"key"
            ,"secret"
            ,"http://example.com/callback"
            ,OAuth::SignatureMethod::HMAC_SHA1);
        OAuth::Service service(configuration, sendRequest);
        ASSERT_EQ("http://example.com/auth?some=parameter&oauth_token=tokenkey", service.getAuthorizeUrl(token));
    }
}
