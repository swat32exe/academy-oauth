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
        ServiceConfiguration(const std::string &tokenRequestUrl
            ,const std::string &authorizeUrl
            ,const std::string &tokenExchangeUrl);

        const std::string &getAuthorizeUrl() const;
        const std::string &getTokenRequestUrl() const;
        const std::string &getTokenExchangeUrl() const;
    };
}

#endif
