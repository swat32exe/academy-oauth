#include <Service.h>

#include <ctime>
#include <string>
#include <cstdlib>

#include "HttpRequest.h"
#include "Token.h"
#include "Signature.h"
#include "utility/Url.h"
#include "utility/Extractor.h"
#include "DefaultSendRequest.h"

namespace OAuth
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
        ParameterList additionalParameters;
        additionalParameters.addRaw(OAUTH_CALLBACK, configuration.getCallbackUrl());
        HttpRequest request(HttpRequestType::POST, configuration.getTokenRequestUrl());
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
        authorizeUrl += "oauth_token=" + Utility::urlEncode(token.getToken());
        return authorizeUrl;
    }

    std::future<Token> Service::exchangeToken(const Token &token, const std::string &verifier) const
    {
        ParameterList additionalParameters;
        additionalParameters.addRaw(OAUTH_TOKEN, token.getToken());
        additionalParameters.addRaw(OAUTH_VERIFIER, verifier);
        HttpRequest request(HttpRequestType::POST, configuration.getTokenExchangeUrl());
        this->signRequest(request, token, additionalParameters);

        return std::async([=] () {
            std::string response = sendRequest(request);
            return Token(response);
        });
    }

    std::string Service::generateNonce() const
    {
        std::string nonce = Utility::toString(std::time(NULL));

        clock_t clockTime = clock();
        if (clockTime > 0)
            nonce += Utility::toString(clockTime);

        nonce += Utility::toString(rand());

        return nonce;
    }

    void Service::signRequest(HttpRequest &request, const Token &token,
                              const ParameterList &additionalOAuthParameters) const
    {
        ParameterList oauthParameters = this->generateOAuthParameters();
        oauthParameters.add(additionalOAuthParameters);
        std::string baseString = request.getRequestTypeAsString() + '&'
                + request.getBaseStringUri() + '&';

        ParameterList allParameters;
        allParameters.add(oauthParameters);
        allParameters.add(request.getQueryParameters());
        allParameters.add(Utility::extractBodyParameters(request));
        baseString += Utility::extractBaseString(allParameters);

        Signature signature = Signature::create(configuration.getSignatureMethod());
        const std::string signatureString = signature(baseString,
                configuration.getConsumerSecret(), token.getSecret());
        oauthParameters.addRaw(OAUTH_SIGNATURE, signatureString);
        request.addHeader("Authorization", Utility::extractAuthorizationHeader(oauthParameters));
    }

    void Service::signRequest(HttpRequest &request, const Token &token)
    {
        ParameterList additionalParameters;
        additionalParameters.addRaw(OAUTH_TOKEN, token.getToken());
        signRequest(request, token, additionalParameters);
    }

    ParameterList Service::generateOAuthParameters() const
    {
        ParameterList oauthParameters;
        oauthParameters.addRaw(OAUTH_CONSUMER_KEY, configuration.getConsumerKey());
        oauthParameters.addRaw(OAUTH_SIGNATURE_METHOD, configuration.getSignatureMethodAsString());
        oauthParameters.addRaw(OAUTH_TIMESTAMP, Utility::toString(std::time(NULL)));
        oauthParameters.addRaw(OAUTH_NONCE, this->generateNonce());
        oauthParameters.addRaw(OAUTH_VERSION, OAUTH_DEFAULT_VERSION);
        return oauthParameters;
    }
}
