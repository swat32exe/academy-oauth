#include <string>
#include <gtest/gtest.h>

#include <Service.h>
#include <ServiceConfiguration.h>
#include <SendRequest.h>
#include <Token.h>

namespace OAuth
{
    class GetAuthorizeUrlTests: public testing::Test
    {
    };

    TEST_F(GetAuthorizeUrlTests, no_parameters)
    {
        Token token("token","secret");
        OAuth::ServiceConfiguration configuration("http://req.u/init"
            ,"http://req.u/auth"
            ,"http://req.u/exchange"
            ,"key"
            ,"secret"
            ,OAuth::SignatureMethod::PLAINTEXT);
        OAuth::Service service(configuration, sendRequest);
        ASSERT_EQ("http://req.u/auth?oauth_token=token", service.getAuthorizeUrl(token));
    }

    TEST_F(GetAuthorizeUrlTests, has_parameters)
    {
        Token token("token","secret");
        OAuth::ServiceConfiguration configuration("http://req.u/init"
            ,"http://req.u/auth?some=parameter"
            ,"http://req.u/exchange"
            ,"key"
            ,"secret"
            ,OAuth::SignatureMethod::PLAINTEXT);
        OAuth::Service service(configuration, sendRequest);
        ASSERT_EQ("http://req.u/auth?some=parameter&oauth_token=token", service.getAuthorizeUrl(token));
    }
}
