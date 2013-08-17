#include <oauth2/Service.h>

#include <string>
#include <stdexcept>

#include <utility/Url.h>
#include <DefaultSendRequest.h>

namespace OAuth2
{
    const std::string Service::RESPONSE_TYPE = "response_type";
    const std::string Service::CLIENT_ID = "client_id";
    const std::string Service::REDIRECT_URI = "redirect_uri";
    const std::string Service::SCOPE = "scope";
    const std::string Service::STATE = "state";

    Service::Service(const ServiceConfiguration &configuration, const send_request_t &sendRequest) :
        configuration(configuration)
        ,sendRequest(sendRequest)
    {
    }

    Service::Service(const ServiceConfiguration &configuration) :
        configuration(configuration)
        ,sendRequest(defaultSendRequest)
    {
    }

    std::string Service::getAuthorizeUrl(const std::string &state) const
    {
        std::string authorizeUrl = configuration.getAuthEndpoint();

        if(authorizeUrl.find("?") == std::string::npos)
            authorizeUrl += "?";
        else
            authorizeUrl += "&";

        switch (configuration.getGrantType()) {
        case AUTH_CODE_GRANT:
            authorizeUrl += makeRedirectUrlParameters(state,  "code");
            break;
        case IMPLICIT_GRANT:
            authorizeUrl += makeRedirectUrlParameters(state,  "token");
            break;
        default:
            throw std::logic_error("getAuthorizeUrl does not support specified grant type");
        }

        return authorizeUrl;
    }

    std::string Service::makeRedirectUrlParameters(const std::string &state,
            const std::string &responseType) const
    {
        std::string parameters =
            RESPONSE_TYPE + "=" + OAuth::Utility::urlEncode(responseType)
            + "&" + CLIENT_ID + "=" + OAuth::Utility::urlEncode(configuration.getClientId())
            + "&" + REDIRECT_URI + "=" + OAuth::Utility::urlEncode(configuration.getRedirectUri());
        if(!configuration.getScope().empty())
            parameters += "&" + SCOPE + "=" + OAuth::Utility::urlEncode(configuration.getScope());
        if(!state.empty())
            parameters += "&" + STATE + "=" + OAuth::Utility::urlEncode(state);
        return parameters;
    }
}
