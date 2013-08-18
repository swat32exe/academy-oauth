#include <gtest/gtest.h>

#include <oauth2/Service.h>
#include <oauth2/ServiceBuilder.h>
#include <oauth2/Token.h>
#include <HttpRequest.h>

namespace OAuth2
{
    class ServiceTests2: public testing::Test
    {
    public:
        ServiceBuilder authCodeGrantBuilder;
        ServiceBuilder implicitGrantBuilder;

        ServiceTests2()
        {
            authCodeGrantBuilder.setGrantType(AUTH_CODE_GRANT)
                    .setAuthEndpoint("https://server.example.com/authorize")
                    .setTokenEndpoint("https://server.example.com/token")
                    .setClientId("s6BhdRkqt3")
                    .setRedirectUri("https://client.example.com/cb");
            implicitGrantBuilder.setGrantType(IMPLICIT_GRANT)
                    .setAuthEndpoint("https://server.example.com/authorize")
                    .setTokenEndpoint("https://server.example.com/token")
                    .setClientId("s6BhdRkqt3")
                    .setRedirectUri("https://client.example.com/cb");
        }
    };

    TEST_F(ServiceTests2, get_authorize_url_no_parameters_auth_code_grant)
    {
        Service service = authCodeGrantBuilder.build();
        ASSERT_EQ(
                "https://server.example.com/authorize?response_type=code&client_id=s6BhdRkqt3"
                "&redirect_uri=https%3A%2F%2Fclient.example.com%2Fcb&state=xyz",
                service.getAuthorizeUrl("xyz"));
    }

    TEST_F(ServiceTests2, get_authorize_url_no_parameters_implicit_grant)
    {
        Service service = implicitGrantBuilder.build();
        ASSERT_EQ(
            "https://server.example.com/authorize?response_type=token&client_id=s6BhdRkqt3"
            "&redirect_uri=https%3A%2F%2Fclient.example.com%2Fcb&state=xyz",
            service.getAuthorizeUrl("xyz"));
    }

    TEST_F(ServiceTests2, sign_request)
    {
        Service service = implicitGrantBuilder.build();
        Token token("mF_9.B5f-4.1JqM");
        OAuth::HttpRequest httpRequest(OAuth::POST, "https://data.example.com/");
        service.signRequest(httpRequest, token);
        ASSERT_EQ("Bearer mF_9.B5f-4.1JqM", httpRequest.getHeaders().find("Authorization")->second);
    }
}
