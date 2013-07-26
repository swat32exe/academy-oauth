#ifndef __SERVICECONFIGURATION_H
#define __SERVICECONFIGURATION_H

#include <string>

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
    public:
        /**
         * Sets field values according to provided data.
         * @param tokenRequestUrl URL used to request temporary token
         * @param authorizeUrl URL to which user will be redirected to authorize access
         * @param tokenExchangeUrl URL used to exchange temporary token for permanent
         */
        ServiceConfiguration(const std::string &tokenRequestUrl
            ,const std::string &authorizeUrl
            ,const std::string &tokenExchangeUrl);

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
    };
}

#endif
