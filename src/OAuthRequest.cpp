#include "OAuthRequest.h"

namespace OAuth
{
    const std::string OAuthRequest::DEFAULT_CONTENT_TYPE = "x-www-form-urlencoded";
    const std::string OAuthRequest::OAUTH_PREFIX = "oauth_";

    OAuthRequest::OAuthRequest(HttpRequestType httpRequestType, const std::string &url,
            TransmissionType type) :
                    HttpRequest(httpRequestType, url),
                    transmissionType(type)
    {
        this->addHeader("Content-Type", DEFAULT_CONTENT_TYPE);
    }

    void OAuthRequest::addOAuthParameter(const std::string &name, const std::string &value)
    {
        if (name.find(OAUTH_PREFIX) != 0) {
            throw std::invalid_argument("Name must start with \"" + OAUTH_PREFIX);
        }

        oauthParameters.add(name, value);
    }

    const ParameterList &OAuthRequest::getOAuthParameters() const
    {
        return oauthParameters;
    }
}
