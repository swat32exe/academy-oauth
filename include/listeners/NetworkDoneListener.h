#ifndef __NETWORKDONELISTENER_H
#define __NETWORKDONELISTENER_H

namespace OAuth
{
    /**
     * Interface for notifying about end of network operation
     */
    class NetworkDoneListener
    {
    public:
        /**
         *  Is called by NetworkWorker class when response received after sendRequest
         */
        virtual void done() = 0;
    };
}

#endif
