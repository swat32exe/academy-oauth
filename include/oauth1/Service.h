#ifndef __SERVICE_H
#define __SERVICE_H

#include <string>
#include <functional>
#include <future>

#include "ServiceConfiguration.h"
#include "ParameterList.h"

namespace OAuth {
    class HttpRequest;
}

namespace OAuth1
{
    class Token;

    typedef std::function<std::string(const OAuth::HttpRequest&)> sendRequest_t;

    class Service
    {
    public:
        static const std::string OAUTH_CONSUMER_KEY;
        static const std::string OAUTH_SIGNATURE_METHOD;
        static const std::string OAUTH_CALLBACK;
        static const std::string OAUTH_SIGNATURE;
        static const std::string OAUTH_TIMESTAMP;
        static const std::string OAUTH_NONCE;
        static const std::string OAUTH_VERSION;
        static const std::string OAUTH_TOKEN;
        static const std::string OAUTH_VERIFIER;
        static const std::string OAUTH_DEFAULT_VERSION;

    private:
        ServiceConfiguration configuration;
        sendRequest_t sendRequest;

        /**
         * Generates random string
         * @returns random string
         */
        std::string generateNonce() const;
        void signRequest(OAuth::HttpRequest &request, const Token &token,
                         const OAuth::ParameterList &additionalOAuthParameters) const;

    public:

        /**
         *  Creates service with specified configuration and networkWorker
         *  @param configuration initial service configuration
         *  @param sendRequest used to make requests over network.
         *  Must send provided request and return response. May throw exceptions.
         */
        Service(const ServiceConfiguration &configuration, const sendRequest_t &sendRequest);

        /**
         *  Creates service with specified configuration.
         *  Uses cURL as default for work with network.
         *  @param configuration initial service configuration
         */
#ifdef USE_CURL
        Service(const ServiceConfiguration &configuration);
#endif

        /**
         *  Request temporary credentials asynchronously
         *  @returns std::future object, that will return token or throw exception
         */
        std::future<Token> getRequestToken();
        /*
         *  Sign HttpRequest using token
         *  @param request request to sign
         *  @param token token, used to sign request
         */
        void signRequest(OAuth::HttpRequest &request, const Token &token);
        /**
         *  Generates url to which user should be redirected
         *  @param token temporary credentials
         *  @returns url to which user should be redirected
         */
        std::string getAuthorizeUrl(const Token &token) const;
        /**
         *  Exchanges temporary credentials for token
         *  @param token temporary credentials
         *  @param verifier verifier, that was got, when user was redirected to callback url
         */
        std::future<Token> exchangeToken(const Token &token, const std::string &verifier) const;

    private:
        OAuth::ParameterList generateOAuthParameters() const;
    };
}
#endif
