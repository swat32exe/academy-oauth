#include <Service.h>

#include <ctime>
#include <string>
#include <cstdlib>

#include <Utility.h>
#include <HttpRequest.h>
#include <Token.h>

#include "Signature.h"

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
    const std::string Service::OAUTH_DEFAULT_VERSION = "1.0";

    Service::Service(const ServiceConfiguration &configuration, const sendRequest_t &sendRequest) :
        configuration(configuration)
        ,sendRequest(sendRequest)
    {
    }

    std::future<Token> Service::getRequestToken()
    {
        HttpRequest request(HttpRequestType::POST, configuration.getTokenRequestUrl());
        this->signRequest(request, Token(""));

        return std::async([=] () {
            std::string response = sendRequest(request);
            return Token(response);
        });
    }

    std::string Service::generateNonce()
    {
        std::string nonce = Utility::toString(std::time(NULL));

        clock_t clockTime = clock();
        if (clockTime > 0)
            nonce += Utility::toString(clockTime);

        nonce += Utility::toString(rand());

        return nonce;
    }

    void Service::signRequest(HttpRequest &request, const Token &token)
    {
        ParameterList oauthParameters = this->generateOAuthParameters();
        std::string baseString = request.getRequestTypeAsString() + '&'
                + request.getBaseStringUri() + '&';

        ParameterList allParameters;
        allParameters.add(oauthParameters);
        allParameters.add(request.getQueryParameters());
        allParameters.add(request.getBodyParameters());
        baseString += Utility::urlEncode(allParameters.asBaseString());

        Signature signature = Signature::create(configuration.getSignatureMethod());
        const std::string signatureString = signature(baseString,
                configuration.getConsumerSecret(), token.getSecret());
        oauthParameters.add(OAUTH_SIGNATURE, signatureString);
        request.addHeader("Authorization", oauthParameters.asAuthorizationHeader());
    }

    ParameterList Service::generateOAuthParameters()
    {
        ParameterList oauthParameters;
        oauthParameters.add(OAUTH_CONSUMER_KEY, configuration.getConsumerKey());
        oauthParameters.add(OAUTH_SIGNATURE_METHOD, configuration.getSignatureMethodAsString());
        oauthParameters.add(OAUTH_CALLBACK, configuration.getCallbackUrl());
        oauthParameters.add(OAUTH_TIMESTAMP, Utility::toString(std::time(NULL)));
        oauthParameters.add(OAUTH_NONCE, this->generateNonce());
        oauthParameters.add(OAUTH_VERSION, OAUTH_DEFAULT_VERSION);
        return oauthParameters;
    }
}
