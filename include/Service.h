#ifndef __SERVICE_H
#define __SERVICE_H

#include <string>
#include <functional>
#include <future>

#include <ServiceConfiguration.h>

namespace OAuth
{
    class HttpRequest;
    class Token;

    typedef std::function<std::string(const HttpRequest&)> sendRequest_t;

    class Service
    {
        ServiceConfiguration configuration;
        sendRequest_t sendRequest;

        /**
         * Generates random string
         * @returns random string
         */
        std::string generateNonce();
    public:
        /**
         *  Creates service with specified configuration and networkWorker
         *  @param configuration initial service configuration
         *  @param sendRequest used to make requests over network.
         *  Must send provided request and return response. May throw exceptions.
         */
        Service(const ServiceConfiguration &configuration, const sendRequest_t &sendRequest);
        /**
         *  Request temporary credentials asynchronously
         *  @param realm string identifying protected resource
         *  @param callbackUrl user will be redirected to this url after authorizing access
         *  @returns std::future object, that will return token or throw exception
         */
        std::future<Token> requestToken(const std::string &realm, const std::string &callbackUrl);
    };
}
#endif
