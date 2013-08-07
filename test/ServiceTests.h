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

    TEST_F(ServiceTests, credentials_exchange_hmac_sha1)
    {
        OAuth::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php"
            ,"http://example.com/auth"
            ,"http://term.ie/oauth/example/access_token.php"
            ,"key"
            ,"secret"
            ,"http://example.com/callback"
            ,HMAC_SHA1);
        OAuth::Service service(configuration, sendRequest);
        std::future<Token> futureToken = service.exchangeToken(Token("requestkey", "requestsecret"), "verifier");
        Token token = futureToken.get();
        ASSERT_EQ("accesskey", token.getToken());
        ASSERT_EQ("accesssecret", token.getSecret());
    }

    TEST_F(ServiceTests, sign_request_get_hmac_sha1)
    {
        OAuth::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php"
            ,"http://example.com/auth"
            ,"http://term.ie/oauth/example/access_token.php"
            ,"key"
            ,"secret"
            ,"http://example.com/callback"
            ,HMAC_SHA1);
        OAuth::Service service(configuration, sendRequest);

        HttpRequest request(GET, "http://term.ie/oauth/example/echo_api.php");
        request.addHeader("Some-Wierd-Header", "some_data");
        request.addQueryParameter("testParameter","value");
        request.addQueryParameter("anotherParameter","anotherValue");
        service.signRequest(request, Token("accesskey", "accesssecret"));
        std::string response = sendRequest(request);
        ASSERT_EQ("testParameter=value&anotherParameter=anotherValue", response);
    }

    TEST_F(ServiceTests, sign_request_post_hmac_sha1_form_body)
    {
        OAuth::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php"
            ,"http://example.com/auth"
            ,"http://term.ie/oauth/example/access_token.php"
            ,"key"
            ,"secret"
            ,"http://example.com/callback"
            ,HMAC_SHA1);
        OAuth::Service service(configuration, sendRequest);

        HttpRequest request(POST, "http://term.ie/oauth/example/echo_api.php");
        request.addHeader("Some-Wierd-Header", "some_data");
        request.setBody("testParameter=value&anotherParameter=anotherValue");
        service.signRequest(request, Token("accesskey", "accesssecret"));
        std::string response = sendRequest(request);
        ASSERT_EQ("testParameter=value&anotherParameter=anotherValue", response);
    }

    TEST_F(ServiceTests, sign_request_post_hmac_sha1_arbitraty_body)
    {
        OAuth::ServiceConfiguration configuration("http://term.ie/oauth/example/request_token.php"
            ,"http://example.com/auth"
            ,"http://term.ie/oauth/example/access_token.php"
            ,"key"
            ,"secret"
            ,"http://example.com/callback"
            ,HMAC_SHA1);
        OAuth::Service service(configuration, sendRequest);

        HttpRequest request(POST, "http://term.ie/oauth/example/echo_api.php");
        request.addHeader(HttpRequest::HEADER_CONTENT_TYPE, "text/plain");
        request.addHeader("Some-Wierd-Header", "some_data");
        request.setBody("Some not urlencoded body");
        service.signRequest(request, Token("accesskey", "accesssecret"));
        std::string response = sendRequest(request);
        // Term.ie won't echo arbitrary body, it'l return empty body. However, it'l check the signature.
        ASSERT_EQ("", response);
    }
}
