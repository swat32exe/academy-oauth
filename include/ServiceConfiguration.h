#ifndef __SERVICECONFIGURATION_H
#define __SERVICECONFIGURATION_H

#include <string>

#include "Signature.h"

namespace OAuth
{
    /**
     *  Contains data, required for initial service configuration
     */
    class ServiceConfiguration
    {
        /**
         *  URL used to request temporary token
         */
        std::string tokenRequestUrl;
        /**
         *  URL to which user will be redirected to authorize access
         */
        std::string authorizeUrl;
        /**
         *  URL used to exchange temporary token for permanent
         */
        std::string tokenExchangeUrl;
        /**
         * OAuth consumer key
         */
        std::string consumerKey;
        /**
         * OAuth consumer secret
         */
        std::string consumerSecret;
        /**
         * Method used to sign request
         */
        std::string callbackUrl;
        /**
         * Protection realm
         */
        std::string realm;
        SignatureMethod signatureMethod;

    public:
        static const std::string OUT_OF_BAND;

        /**
         * Sets field values according to provided data.
         * @param tokenRequestUrl URL used to request temporary token
         * @param authorizeUrl URL to which user will be redirected to authorize access
         * @param tokenExchangeUrl URL used to exchange temporary token for permanent
         * @param consumerKey OAuth consumer key
         * @param consumerSecret OAuth consumer secret
         * @param callbackUrl user will be redirected to this url after authorizing access
         * @param signatureMethod method used to sign request
         * @param realm protection realm
         */
        ServiceConfiguration(const std::string &tokenRequestUrl
            ,const std::string &authorizeUrl
            ,const std::string &tokenExchangeUrl
            ,const std::string &consumerKey
            ,const std::string &consumerSecret
            ,const std::string &callbackUrl = OUT_OF_BAND
            ,SignatureMethod signatureMethod = HMAC_SHA1
            ,const std::string &realm = ""
            );

        /**
         *  Returns URL used to request temporary token.
         */
        const std::string &getAuthorizeUrl() const;
        /**
         *  Returns URL to which user will be redirected to authorize access.
         */
        const std::string &getTokenRequestUrl() const;
        /**
         *  Returns URL used to exchange temporary token for permanent.
         */
        const std::string &getTokenExchangeUrl() const;
        /**
         * Returns OAuth consumer key
         */
        const std::string &getConsumerKey() const;
        /**
         * Returns OAuth consumer secret
         */
        const std::string &getConsumerSecret() const;

        /**
         * Returns url to which a user will be redirected
         */
        const std::string &getCallbackUrl() const;
        /**
         * Returns protection realm
         */
        const std::string &getRealm() const;
        /**
         * Returns method used to sign request
         */
        SignatureMethod getSignatureMethod() const;
        /**
         * Returns method used to sign request represented as string
         */
        const std::string getSignatureMethodAsString() const;
    };
}

#endif
