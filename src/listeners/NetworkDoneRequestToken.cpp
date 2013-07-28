#include <listeners/NetworkDoneRequestToken.h>

namespace OAuth
{
    NetworkDoneRequestToken::NetworkDoneRequestToken(std::shared_ptr<NetworkWorker> networkWorker
            ,std::shared_ptr<TokenDoneListener> tokenDone) :
        networkWorker(networkWorker)
        ,tokenDone(tokenDone)
    {
    }

    void NetworkDoneRequestToken::done()
    {
        std::string response = networkWorker->getResponse();
        tokenDone->done(Token(response));
    }
}
