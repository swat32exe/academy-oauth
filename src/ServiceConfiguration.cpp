#include <ServiceConfiguration.h>

namespace OAuth
{
    const std::string &ServiceConfiguration::getAuthorizeUrl() const
    {
        return authorizeUrl;
    }

    const std::string &ServiceConfiguration::getTokenRequestUrl() const
    {
        return tokenRequestUrl;
    }

    const std::string &ServiceConfiguration::getTokenExchangeUrl() const
    {
        return tokenExchangeUrl;
    }

    ServiceConfiguration::ServiceConfiguration(const std::string &tokenRequestUrl,
            const std::string &authorizeUrl,
            const std::string &tokenExchangeUrl) :
        tokenRequestUrl(tokenRequestUrl)
        ,authorizeUrl(authorizeUrl)
        ,tokenExchangeUrl(tokenExchangeUrl)
    {
    }
}
