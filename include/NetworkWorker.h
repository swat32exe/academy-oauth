#ifndef __NETWORKWORKER_H
#define __NETWORKWORKER_H

#include <memory>

#include <listeners/NetworkDoneListener.h>
#include <HttpRequest.h>

namespace OAuth
{
    /**
     * Class used to provide acces to network
     */
    class NetworkWorker
    {
    public:
        /**
         * Sends request and invokes listener when done
         * @param request request to make
         * @listener listener.done() will be invoked when response received
         */
        virtual void sendRequest(const HttpRequest &request, std::shared_ptr<NetworkDoneListener> listener) = 0;
        /**
         *  Gets last response.
         *  @returns last received response
         */
        virtual std::string getResponse() = 0;
    };
}

#endif
