#include <Signature.h>
#include <Service.h>
#include <HttpRequest.h>
#include <Utility.h>

namespace OAuthTesting
{
    class SignatureTests : public testing::Test
    {
    };

    TEST(SignatureTests, testPlainText)
    {
        OAuth::Signature signature(OAuth::PLAINTEXT);
        std::string signatureString = signature.get("", "client");
        ASSERT_STREQ("client?", signatureString.c_str());

        signatureString = signature.get("", "client", "token");
        ASSERT_STREQ("client?token", signatureString.c_str());

        signatureString = signature.get("POST&host&parameters", "client", "token");
        ASSERT_STREQ("client?token", signatureString.c_str());
    }

    TEST(SignatureTests, testHmacSha1Temporary)
    {
        // test signature on temporary credentials request
        OAuth::ParameterList oauthParameters;
        using OAuth::Service;
        oauthParameters.add(Service::OAUTH_VERSION, "1.0");
        oauthParameters.add(Service::OAUTH_NONCE, "b8a53456a4eccb8a61626ee17050ce30");
        oauthParameters.add(Service::OAUTH_TIMESTAMP, "1375453769");
        oauthParameters.add(Service::OAUTH_CONSUMER_KEY, "key");
        oauthParameters.add(Service::OAUTH_SIGNATURE_METHOD, "HMAC-SHA1");

        OAuth::HttpRequest request(OAuth::GET, "http://term.ie/oauth/example/request_token.php");
        std::string baseString = request.getRequestTypeAsString() + '&'
                + request.getBaseStringUri() + '&';
        baseString += OAuth::Utility::urlEncode(oauthParameters.asBaseString());

        OAuth::Signature signature;
        std::string signatureString = signature.get(baseString, "secret");
        ASSERT_STREQ("ks36RJj7xqsKaRKSQXXofEJ4FYI%3D", signatureString.c_str());
    }

    TEST(SignatureTests, testHmacSha1Access)
    {
        // test signature on access token request
        OAuth::ParameterList oauthParameters;
        using OAuth::Service;
        oauthParameters.add(Service::OAUTH_VERSION, "1.0");
        oauthParameters.add(Service::OAUTH_NONCE, "40f27d79d7f762ddd126be8f81b33298");
        oauthParameters.add(Service::OAUTH_TIMESTAMP, "1375453769");
        oauthParameters.add(Service::OAUTH_CONSUMER_KEY, "key");
        oauthParameters.add(Service::OAUTH_TOKEN, "requestkey");
        oauthParameters.add(Service::OAUTH_SIGNATURE_METHOD, "HMAC-SHA1");

        OAuth::HttpRequest request(OAuth::GET, "http://term.ie/oauth/example/access_token.php");
        std::string baseString = request.getRequestTypeAsString() + '&'
                + request.getBaseStringUri() + '&';
        baseString += OAuth::Utility::urlEncode(oauthParameters.asBaseString());

        OAuth::Signature signature;
        std::string signatureString = signature.get(baseString, "secret", "requestsecret");
        ASSERT_STREQ("YLz49ccRr9wbHKkguNEog5E2aec%3D", signatureString.c_str());
    }
}
