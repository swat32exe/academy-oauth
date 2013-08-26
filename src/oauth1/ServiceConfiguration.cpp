#include <oauth1/ServiceConfiguration.h>

#include <cassert>

#include <utility/Url.h>

namespace OAuth1
{
    const std::string ServiceConfiguration::OUT_OF_BAND = "oob";

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

    const std::string &ServiceConfiguration::getConsumerKey() const
    {
        return consumerKey;
    }

    const std::string &ServiceConfiguration::getConsumerSecret() const
    {
        return consumerSecret;
    }

    SignatureMethod ServiceConfiguration::getSignatureMethod() const
    {
        return signatureMethod;
    }

    const std::string &ServiceConfiguration::getCallbackUrl() const
    {
        return callbackUrl;
    }

    const std::string &ServiceConfiguration::getRealm() const
    {
        return realm;
    }

    const std::string ServiceConfiguration::getSignatureMethodAsString() const
    {
        switch (signatureMethod) {
        case HMAC_SHA1:
            return "HMAC-SHA1";
        case RSA_SHA1:
            return "RSA-SHA1";
        case PLAINTEXT:
            return "PLAINTEXT";
        default:
            assert("Unknown method" && false);
            // Just to avoid warning.
            return "";
        }
    }

    ServiceConfiguration::ServiceConfiguration(const std::string &tokenRequestUrl
            ,const std::string &authorizeUrl
            ,const std::string &tokenExchangeUrl
            ,const std::string &consumerKey
            ,const std::string &consumerSecret
            ,const std::string &callbackUrl
            ,SignatureMethod signatureMethod
            ,const std::string &realm) :
        tokenRequestUrl(OAuth::Utility::normalizeUrl(tokenRequestUrl))
        ,authorizeUrl(OAuth::Utility::normalizeUrl(authorizeUrl))
        ,tokenExchangeUrl(OAuth::Utility::normalizeUrl(tokenExchangeUrl))
        ,consumerKey(consumerKey)
        ,consumerSecret(consumerSecret)
        ,callbackUrl(callbackUrl)
        ,realm(realm)
        ,signatureMethod(signatureMethod)
    {
    }
}
