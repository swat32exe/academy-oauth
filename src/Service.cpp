#include <Service.h>

#include <ctime>
#include <string>
#include <cstdlib>

#include <Utility.h>
#include <HttpRequest.h>
#include <Token.h>

#include "ParameterList.h"

namespace OAuth
{
    Service::Service(const ServiceConfiguration &configuration, const sendRequest_t &sendRequest) :
        configuration(configuration)
        ,sendRequest(sendRequest)
    {
    }

    std::future<Token> Service::requestToken(const std::string &realm, const std::string &callbackUrl)
    {
        std::string timeStamp = Utility::toString(std::time(NULL));
        std::string callback = Utility::urlEncode(callbackUrl);

        header_t headers;
        headers["Authorization"] = "OAuth realm=\"" + realm + "\",\r\n"
                " oauth_consumer_key=\"" + configuration.getConsumerKey() + "\",\r\n"
                " oauth_signature_method=\"" + configuration.getSignatureMethodAsString() + "\",\r\n"
                " oauth_timestamp=\"" + timeStamp + "\",\r\n"
                " oauth_nonce=\"" + generateNonce() + "\",\r\n"
                " oauth_callback=\"" + callback + "\"";

        headers["Host"] = Utility::hostFromUrl(configuration.getTokenRequestUrl());
        std::string resource = Utility::resourceFromUrl(configuration.getTokenRequestUrl());

        HttpRequest request(HttpRequestType::POST, configuration.getTokenRequestUrl());

        // TODO: Sign request.

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

    std::string Service::getAuthorizeUrl(Token token) const
    {
        std::string authorizeUrl = configuration.getAuthorizeUrl();
        if(authorizeUrl.find("?") == std::string::npos)
            authorizeUrl += "?";
        else
            authorizeUrl += "&";
        authorizeUrl += "oauth_token=" + Utility::urlEncode(token.getToken());
        return authorizeUrl;
    }
}
