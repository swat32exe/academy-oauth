#include <ServiceConfiguration.h>

#include <cassert>

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

    const std::string OAuth::ServiceConfiguration::getSignatureMethodAsString() const
    {
        switch (signatureMethod) {
        case SignatureMethod::HMAC_SHA1:
            return "HMAC-SHA1";
        case SignatureMethod::RSA_SHA1:
            return "RSA-SHA1";
        case SignatureMethod::PLAINTEXT:
            return "PLAINTEXT";
        default:
            assert("Unknown method" && false);
        }
    }

    ServiceConfiguration::ServiceConfiguration(const std::string &tokenRequestUrl
            ,const std::string &authorizeUrl
            ,const std::string &tokenExchangeUrl
            ,const std::string &consumerKey
            ,const std::string &consumerSecret
            ,SignatureMethod signatureMethod) :
        tokenRequestUrl(tokenRequestUrl)
        ,authorizeUrl(authorizeUrl)
        ,tokenExchangeUrl(tokenExchangeUrl)
        ,consumerKey(consumerKey)
        ,consumerSecret(consumerSecret)
        ,signatureMethod(signatureMethod)
    {
    }
}