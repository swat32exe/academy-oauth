#include <gtest/gtest.h>

#include <oauth2/Service.h>
#include <oauth2/Token.h>
#include <HttpRequest.h>

namespace OAuth2
{
    class ServiceTests2: public testing::Test
    {
    public:
        ServiceConfiguration testConfigurationCodeGrant1;
        ServiceConfiguration testConfigurationImplicitGrant1;

        ServiceTests2() :
            testConfigurationCodeGrant1(AUTH_CODE_GRANT,
                    "https://server.example.com/authorize",
                    "https://server.example.com/token",
                    "s6BhdRkqt3",
                    "https://client.example.com/cb",
                    "",
                    "johndoe",
                    "A3ddj3w"
            )
            , testConfigurationImplicitGrant1(IMPLICIT_GRANT,
                    "https://server.example.com/authorize",
                    "https://server.example.com/token",
                    "s6BhdRkqt3",
                    "https://client.example.com/cb",
                    "",
                    "johndoe",
                    "A3ddj3w"
            )
        {
        }
    };

    TEST_F(ServiceTests2, get_authorize_url_no_parameters_auth_code_grant)
    {
        Service service(testConfigurationCodeGrant1);
        ASSERT_EQ(
                "https://server.example.com/authorize?response_type=code&client_id=s6BhdRkqt3"
                "&redirect_uri=https%3A%2F%2Fclient.example.com%2Fcb&state=xyz",
                service.getAuthorizeUrl("xyz"));
    }

    TEST_F(ServiceTests2, get_authorize_url_no_parameters_implicit_grant)
    {
        Service service(testConfigurationImplicitGrant1);
        ASSERT_EQ(
            "https://server.example.com/authorize?response_type=token&client_id=s6BhdRkqt3"
            "&redirect_uri=https%3A%2F%2Fclient.example.com%2Fcb&state=xyz",
            service.getAuthorizeUrl("xyz"));
    }

    TEST_F(ServiceTests2, sign_request)
    {
        Service service(testConfigurationImplicitGrant1);
        Token token("mF_9.B5f-4.1JqM");
        OAuth::HttpRequest httpRequest(OAuth::POST, "https://data.example.com/");
        service.signRequest(httpRequest, token);
        ASSERT_EQ("Bearer mF_9.B5f-4.1JqM", httpRequest.getHeaders().find("Authorization")->second);
    }
}
