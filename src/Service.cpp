#include <Service.h>

#include <ctime>
#include <string>
#include <cstdlib>

#include <Utility.h>
#include <listeners/NetworkDoneRequestToken.h>

namespace OAuth
{
    Service::Service(const ServiceConfiguration &configuration, std::shared_ptr<NetworkWorker> &networkWorker) :
        configuration(configuration)
        ,networkWorker(networkWorker)
    {
    }

    void Service::requestToken(const std::string &realm, const std::string &callbackUrl, std::shared_ptr<TokenDoneListener> requestDone)
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

        HttpRequest request(HttpRequestType::POST, resource, headers, "");

        // TODO: Sign request.

        std::shared_ptr<NetworkDoneRequestToken> networkDoneRequestToken (
            new NetworkDoneRequestToken(networkWorker, requestDone));
        networkWorker->sendRequest(request, networkDoneRequestToken);
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
}
