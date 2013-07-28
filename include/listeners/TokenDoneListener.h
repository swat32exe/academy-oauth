#ifndef __TOKENDONELISTENER_H
#define __TOKENDONELISTENER_H

#include <Token.h>

namespace OAuth
{
    /**
     * Class used to asynchronously return token
     */
    class TokenDoneListener
    {
    public:
        /**
         *  Is called when token received.
         *  @param token token, that has been received
         */
        virtual void done(const Token &token) = 0;
    };
}

#endif
