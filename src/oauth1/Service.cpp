#include <oauth1/Service.h>

#include <ctime>
#include <string>
#include <cstdlib>

#include "HttpRequest.h"
#include "oauth1/Token.h"
#include "oauth1/Signature.h"
#include "utility/Url.h"
#include "utility/Extractor.h"
#include "DefaultSendRequest.h"

namespace OAuth1
{
    const std::string Service::OAUTH_CONSUMER_KEY = "oauth_consumer_key";
    const std::string Service::OAUTH_SIGNATURE_METHOD = "oauth_signature_method";
    const std::string Service::OAUTH_CALLBACK = "oauth_callback";
    const std::string Service::OAUTH_SIGNATURE = "oauth_signature";
    const std::string Service::OAUTH_TIMESTAMP = "oauth_timestamp";
    const std::string Service::OAUTH_NONCE = "oauth_nonce";
    const std::string Service::OAUTH_VERSION = "oauth_version";
    const std::string Service::OAUTH_TOKEN = "oauth_token";
    const std::string Service::OAUTH_VERIFIER = "oauth_verifier";
    const std::string Service::OAUTH_DEFAULT_VERSION = "1.0";

    Service::Service(const ServiceConfiguration &configuration, const sendRequest_t &sendRequest) :
        configuration(configuration)
        ,sendRequest(sendRequest)
    {
    }

    Service::Service(const ServiceConfiguration &configuration) :
        configuration(configuration)
        ,sendRequest(defaultSendRequest)
    {
    }

    std::future<Token> Service::getRequestToken()
    {
        OAuth::ParameterList additionalParameters;
        additionalParameters.addRaw(OAUTH_CALLBACK, configuration.getCallbackUrl());
        OAuth::HttpRequest request(OAuth::HttpRequestType::POST,
                configuration.getTokenRequestUrl());
        this->signRequest(request, Token("", ""), additionalParameters);

        return std::async([=] () {
            std::string response = sendRequest(request);
            return Token(response);
        });
    }

    std::string Service::getAuthorizeUrl(const Token &token) const
    {
        std::string authorizeUrl = configuration.getAuthorizeUrl();
        if(authorizeUrl.find("?") == std::string::npos)
            authorizeUrl += "?";
        else
            authorizeUrl += "&";
        authorizeUrl += "oauth_token=" + OAuth::Utility::urlEncode(token.getToken());
        return authorizeUrl;
    }

    std::future<Token> Service::exchangeToken(const Token &token, const std::string &verifier) const
    {
        OAuth::ParameterList additionalParameters;
        additionalParameters.addRaw(OAUTH_TOKEN, token.getToken());
        additionalParameters.addRaw(OAUTH_VERIFIER, verifier);
        OAuth::HttpRequest request(OAuth::HttpRequestType::POST,
                configuration.getTokenExchangeUrl());
        this->signRequest(request, token, additionalParameters);

        return std::async([=] () {
            std::string response = sendRequest(request);
            return Token(response);
        });
    }

    std::string Service::generateNonce() const
    {
        std::string nonce = OAuth::Utility::toString(std::time(NULL));

        clock_t clockTime = clock();
        if (clockTime > 0)
            nonce += OAuth::Utility::toString(clockTime);

        nonce += OAuth::Utility::toString(rand());

        return nonce;
    }

    void Service::signRequest(OAuth::HttpRequest &request, const Token &token,
                              const OAuth::ParameterList &additionalOAuthParameters) const
    {
        OAuth::ParameterList oauthParameters = this->generateOAuthParameters();
        oauthParameters.add(additionalOAuthParameters);
        std::string baseString = request.getRequestTypeAsString() + '&'
                + request.getBaseStringUri() + '&';

        OAuth::ParameterList allParameters;
        allParameters.add(oauthParameters);
        allParameters.add(request.getQueryParameters());
        allParameters.add(OAuth::Utility::extractBodyParameters(request));
        baseString += OAuth::Utility::extractBaseString(allParameters);

        Signature signature = Signature::create(configuration.getSignatureMethod());
        const std::string signatureString = signature(baseString,
                configuration.getConsumerSecret(), token.getSecret());
        oauthParameters.addRaw(OAUTH_SIGNATURE, signatureString);
        request.addHeader("Authorization",
                OAuth::Utility::extractAuthorizationHeader(oauthParameters));
    }

    void Service::signRequest(OAuth::HttpRequest &request, const Token &token)
    {
        OAuth::ParameterList additionalParameters;
        additionalParameters.addRaw(OAUTH_TOKEN, token.getToken());
        signRequest(request, token, additionalParameters);
    }

    OAuth::ParameterList Service::generateOAuthParameters() const
    {
        OAuth::ParameterList oauthParameters;
        oauthParameters.addRaw(OAUTH_CONSUMER_KEY, configuration.getConsumerKey());
        oauthParameters.addRaw(OAUTH_SIGNATURE_METHOD, configuration.getSignatureMethodAsString());
        oauthParameters.addRaw(OAUTH_TIMESTAMP, OAuth::Utility::toString(std::time(NULL)));
        oauthParameters.addRaw(OAUTH_NONCE, this->generateNonce());
        oauthParameters.addRaw(OAUTH_VERSION, OAUTH_DEFAULT_VERSION);
        return oauthParameters;
    }
}
