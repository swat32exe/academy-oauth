#include <gtest/gtest.h>

#include <fstream>

#include <oauth1/Service.h>
#include <oauth1/ServiceConfiguration.h>
#include <DefaultSendRequest.h>


namespace OAuthTesting
{
    class ServiceTests: public testing::Test
    {
    public:
        ServiceTests()
        {
            std::ifstream rsaKeyFile("test/rsaKey.pem");
            rsaKey = std::string((std::istreambuf_iterator<char>(rsaKeyFile)),
                    std::istreambuf_iterator<char>());
        }
        std::string rsaKey;
    };

    TEST_F(ServiceTests, request_temporary_credentials_hmac_sha1)
    {
        OAuth1::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php"
            ,"http://example.com/auth"
            ,"http://term.ie/oauth/example/access_token.php"
            ,"key"
            ,"secret"
            ,"http://example.com/callback"
            ,OAuth1::HMAC_SHA1);
        OAuth1::Service service(configuration, defaultSendRequest);
        std::future<OAuth1::Token> futureToken = service.getRequestToken();
        OAuth1::Token token = futureToken.get();
        ASSERT_EQ("requestkey", token.getToken());
        ASSERT_EQ("requestsecret", token.getSecret());
    }

    TEST_F(ServiceTests, get_authorize_url_no_parameters)
    {
        OAuth1::Token token("tokenkey","tokensecret");
        OAuth1::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php"
            ,"http://example.com/auth"
            ,"http://term.ie/oauth/example/access_token.php"
            ,"key"
            ,"secret"
            ,"http://example.com/callback"
            ,OAuth1::HMAC_SHA1);
        OAuth1::Service service(configuration);
        ASSERT_EQ("http://example.com/auth?oauth_token=tokenkey", service.getAuthorizeUrl(token));
    }

    TEST_F(ServiceTests, get_authorize_url_has_parameters)
    {
        OAuth1::Token token("tokenkey","tokensecret");
        OAuth1::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php"
            ,"http://example.com/auth?some=parameter"
            ,"http://term.ie/oauth/example/access_token.php"
            ,"key"
            ,"secret"
            ,"http://example.com/callback"
            ,OAuth1::HMAC_SHA1);
        OAuth1::Service service(configuration);
        ASSERT_EQ("http://example.com/auth?some=parameter&oauth_token=tokenkey", service.getAuthorizeUrl(token));
    }

    TEST_F(ServiceTests, credentials_exchange_hmac_sha1)
    {
        OAuth1::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php"
            ,"http://example.com/auth"
            ,"http://term.ie/oauth/example/access_token.php"
            ,"key"
            ,"secret"
            ,"http://example.com/callback"
            ,OAuth1::HMAC_SHA1);
        OAuth1::Service service(configuration);
        std::future<OAuth1::Token> futureToken = service.exchangeToken(
                OAuth1::Token("requestkey", "requestsecret"), "verifier");
        OAuth1::Token token = futureToken.get();
        ASSERT_EQ("accesskey", token.getToken());
        ASSERT_EQ("accesssecret", token.getSecret());
    }

    TEST_F(ServiceTests, sign_request_get_hmac_sha1)
    {
        OAuth1::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php"
            ,"http://example.com/auth"
            ,"http://term.ie/oauth/example/access_token.php"
            ,"key"
            ,"secret"
            ,"http://example.com/callback"
            ,OAuth1::HMAC_SHA1);
        OAuth1::Service service(configuration);

        OAuth::HttpRequest request(OAuth::GET, "http://term.ie/oauth/example/echo_api.php");
        request.addHeader("Some-Wierd-Header", "some_data");
        request.addQueryParameter("testParameter","value");
        request.addQueryParameter("anotherParameter","anotherValue");
        service.signRequest(request, OAuth1::Token("accesskey", "accesssecret"));
        std::string response = defaultSendRequest(request);
        ASSERT_EQ("testParameter=value&anotherParameter=anotherValue", response);
    }

    TEST_F(ServiceTests, sign_request_post_hmac_sha1_form_body)
    {
        OAuth1::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php"
            ,"http://example.com/auth"
            ,"http://term.ie/oauth/example/access_token.php"
            ,"key"
            ,"secret"
            ,"http://example.com/callback"
            ,OAuth1::HMAC_SHA1);
        OAuth1::Service service(configuration);

        OAuth::HttpRequest request(OAuth::POST, "http://term.ie/oauth/example/echo_api.php");
        request.addHeader("Some-Wierd-Header", "some_data");
        request.addHeader(OAuth::HEADER_CONTENT_TYPE, OAuth::FORM_URLENCODED);
        request.setBody("testParameter=value&anotherParameter=anotherValue");
        service.signRequest(request, OAuth1::Token("accesskey", "accesssecret"));
        std::string response = defaultSendRequest(request);
        ASSERT_EQ("testParameter=value&anotherParameter=anotherValue", response);
    }

    TEST_F(ServiceTests, sign_request_post_hmac_sha1_arbitrary_body)
    {
        OAuth1::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php"
            ,"http://example.com/auth"
            ,"http://term.ie/oauth/example/access_token.php"
            ,"key"
            ,"secret"
            ,"http://example.com/callback"
            ,OAuth1::HMAC_SHA1);
        OAuth1::Service service(configuration);

        OAuth::HttpRequest request(OAuth::POST, "http://term.ie/oauth/example/echo_api.php");
        request.addHeader(OAuth::HEADER_CONTENT_TYPE, "text/plain");
        request.addHeader("Some-Wierd-Header", "some_data");
        request.setBody("Some not urlencoded body");
        service.signRequest(request, OAuth1::Token("accesskey", "accesssecret"));
        std::string response = defaultSendRequest(request);
        // Term.ie won't echo arbitrary body, it'l return empty body. However, it'l check the signature.
        ASSERT_EQ("", response);
    }

    TEST_F(ServiceTests, obtainRequestTokenRsaSha1)
    {
        OAuth1::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php",
                "" ,"http://term.ie/oauth/example/access_token.php" ,"key",
                this->rsaKey, "oob", OAuth1::RSA_SHA1);
        OAuth1::Service service(configuration);
        OAuth1::Token requestToken = service.getRequestToken().get();
        ASSERT_EQ("requestkey", requestToken.getToken());
        ASSERT_EQ("requestsecret", requestToken.getSecret());
    }

    TEST_F(ServiceTests, tokenExchangeRsaSha1)
    {
        OAuth1::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php",
                "" ,"http://term.ie/oauth/example/access_token.php" ,"key",
                this->rsaKey, "oob", OAuth1::RSA_SHA1);
        OAuth1::Service service(configuration);
        OAuth1::Token accessToken = service.exchangeToken(
                OAuth1::Token("requestkey", "requestsecret"), "verifier").get();
        ASSERT_EQ("accesskey", accessToken.getToken());
        ASSERT_EQ("accesssecret", accessToken.getSecret());
    }

    TEST_F(ServiceTests, signRequestGetRsaSha1)
    {
        OAuth1::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php",
                "", "http://term.ie/oauth/example/access_token.php", "key",
                this->rsaKey, "oob", OAuth1::RSA_SHA1);
        OAuth1::Service service(configuration);

        OAuth::HttpRequest request(OAuth::GET, "http://term.ie/oauth/example/echo_api.php");
        request.addHeader("Some-Wierd-Header", "some_data");
        request.addQueryParameter("testParameter","value");
        request.addQueryParameter("anotherParameter","anotherValue");
        service.signRequest(request, OAuth1::Token("accesskey", "accesssecret"));
        std::string response = defaultSendRequest(request);
        ASSERT_EQ("testParameter=value&anotherParameter=anotherValue", response);
    }

    TEST_F(ServiceTests, signRequestPostRsaSha1FormBody)
    {
        OAuth1::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php",
                "" ,"http://term.ie/oauth/example/access_token.php", "key",
                this->rsaKey ,"http://example.com/callback", OAuth1::RSA_SHA1);
        OAuth1::Service service(configuration);

        OAuth::HttpRequest request(OAuth::POST, "http://term.ie/oauth/example/echo_api.php");
        request.addHeader("Some-Wierd-Header", "some_data");
        request.addHeader(OAuth::HEADER_CONTENT_TYPE, OAuth::FORM_URLENCODED);
        request.setBody("testParameter=value&anotherParameter=anotherValue");
        service.signRequest(request, OAuth1::Token("accesskey", "accesssecret"));
        std::string response = defaultSendRequest(request);
        ASSERT_EQ("testParameter=value&anotherParameter=anotherValue", response);
    }

    TEST_F(ServiceTests, signRequestRsaSha1ArbitraryBody)
    {
        OAuth1::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php",
                "", "http://term.ie/oauth/example/access_token.php", "key",
                this->rsaKey, "http://example.com/callback", OAuth1::RSA_SHA1);
        OAuth1::Service service(configuration);

        OAuth::HttpRequest request(OAuth::POST, "http://term.ie/oauth/example/echo_api.php");
        request.addHeader(OAuth::HEADER_CONTENT_TYPE, "text/plain");
        request.addHeader("Some-Wierd-Header", "some_data");
        request.setBody("Some not urlencoded body");
        service.signRequest(request, OAuth1::Token("accesskey", "accesssecret"));
        std::string response = defaultSendRequest(request);
        ASSERT_EQ("", response);
    }
}
