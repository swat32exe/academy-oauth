#ifndef __NETWORKDONEREQUESTTOKEN_H
#define __NETWORKDONEREQUESTTOKEN_H

#include <memory>

#include <NetworkWorker.h>
#include <listeners/NetworkDoneListener.h>
#include <listeners/TokenDoneListener.h>

namespace OAuth
{
    class Service;
    class Token;
    class TokenDoneListener;
    class NetworkWorker;

    /**
     *  This class is used by Service to finish requestToken
     */
    class NetworkDoneRequestToken : public NetworkDoneListener
    {
        std::shared_ptr<NetworkWorker> networkWorker;
        std::shared_ptr<TokenDoneListener> tokenDone;
    public:
        /**
         * Saves networkWorker and tokenDone for later use
         */
        NetworkDoneRequestToken(std::shared_ptr<NetworkWorker> networkWorker, std::shared_ptr<TokenDoneListener> tokenDone);
        /**
         * Invokes tokenDone using token, received in response
         */
        virtual void done();
    };
}

#endif
