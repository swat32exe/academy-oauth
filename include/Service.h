#ifndef __SERVICE_H
#define __SERVICE_H

#include <memory>

#include <ServiceConfiguration.h>
#include <NetworkWorker.h>
#include <listeners/TokenDoneListener.h>

namespace OAuth
{
    class ServiceConfiguration;
    class NetworkWorker;
    class TokenDoneListener;

    class Service
    {
        ServiceConfiguration configuration;
        std::shared_ptr<NetworkWorker> networkWorker;

        /**
         * Generates random string
         * @returns random string
         */
        std::string generateNonce();
    public:
        /**
         *  @param configuration initial service configuration
         *  @param networkWorker used to make requests over network
         */
        Service(const ServiceConfiguration &configuration, std::shared_ptr<NetworkWorker> &networkWorker);
        /**
         *  Request temporary credentials asynchronously
         *  @param realm string identifying protected resource
         *  @param callbackUrl user will be redirected to this url after authorizing access
         *  @param requestDone TokenDoneListener invoked when request done
         */
        void requestToken(const std::string &realm, const std::string &callbackUrl, std::shared_ptr<TokenDoneListener> requestDone);
    };
}
#endif
