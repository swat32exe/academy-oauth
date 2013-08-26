#include <oauth2/ServiceBuilder.h>

namespace OAuthTesting
{
    class ServiceBuilderTests : public testing::Test
    {
    };

    TEST(ServiceBuilderTests, testCreation)
    {
        OAuth2::Service service = OAuth2::ServiceBuilder()
            .setGrantType(OAuth2::AUTH_CODE_GRANT)
            .setAuthEndpoint("http://example.com/auth_code")
            .setTokenEndpoint("http://example.com/token")
            .setRedirectUri("http://site.com/redirect")
            .setClientId("1")
            .build();
        ASSERT_STREQ("http://example.com/auth_code?response_type=code"
                "&client_id=1&redirect_uri=http%3A%2F%2Fsite.com%2Fredirect",
                service.getAuthorizeUrl().c_str());
    }

    TEST(ServiceBuilderTests, testExceptions)
    {
        // missing authEndpoint
        OAuth2::ServiceBuilder builder = OAuth2::ServiceBuilder()
            .setGrantType(OAuth2::AUTH_CODE_GRANT)
            .setTokenEndpoint("http://example.com/token")
            .setRedirectUri("http://site.com/redirect")
            .setClientId("1");
        ASSERT_THROW(builder.build(), std::invalid_argument);

        // missing password
        builder = OAuth2::ServiceBuilder()
            .setGrantType(OAuth2::OWNER_CREDENTIALS_GRANT)
            .setTokenEndpoint("http://example.com/token")
            .setUsername("john")
            .setClientId("1");
        ASSERT_THROW(builder.build(), std::invalid_argument);

        // missing clientId
        builder = OAuth2::ServiceBuilder()
            .setGrantType(OAuth2::IMPLICIT_GRANT)
            .setTokenEndpoint("http://example.com/token");
        ASSERT_THROW(builder.build(), std::invalid_argument);
    }
}
