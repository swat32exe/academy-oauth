#include <oauth2/Service.h>

#include <string>
#include <stdexcept>
#include <functional>
#include <future>

#include <oauth2/Token.h>
#include <utility/Url.h>
#include <DefaultSendRequest.h>
#include <ParameterList.h>

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

    std::string Service::getAuthorizeUrl(const std::string &state) const
    {
        std::string authorizeUrl = configuration.getAuthEndpoint();

        if (authorizeUrl.find("?") == std::string::npos)
            authorizeUrl += "?";
        else
            authorizeUrl += "&";

        switch (configuration.getGrantType()) {
        case AUTH_CODE_GRANT:
        case IMPLICIT_GRANT:
            authorizeUrl += makeRedirectUrlParameters(state,  configuration.getResponseType());
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
        if (!configuration.getScope().empty())
            parameters += "&" + SCOPE + "=" + OAuth::Utility::urlEncode(configuration.getScope());
        if (!state.empty())
            parameters += "&" + STATE + "=" + OAuth::Utility::urlEncode(state);
        return parameters;
    }

    std::future<Token> Service::getAccessToken(const std::string &url) const
    {
        switch (configuration.getGrantType()) {
        case AUTH_CODE_GRANT:
            return getAccessTokenAuthCodeGrant(url);
        case IMPLICIT_GRANT:
            return getAccessTokenImplicitGrant(url);
        case OWNER_CREDENTIALS_GRANT:
            return getAccessTokenOwnerCredentialsGrant();
        case CLIENT_CREDENTIALS_GRANT:
            return getAccessTokenClientCredentialsGrant();
        default:
            throw std::logic_error("getAccessToken does not support specified grant type");
        }
    }

    std::future<Token> Service::getAccessTokenAuthCodeGrant(const std::string &url) const
    {
        //TODO: Implement
        return std::async([=] () {
            return Token(url);
        });
    }

    std::future<Token> Service::getAccessTokenImplicitGrant(const std::string &url) const
    {
        //TODO: Implement
        return std::async([=] () {
            return Token(url);
        });
    }

    std::future<Token> Service::getAccessTokenOwnerCredentialsGrant() const
    {
        //TODO: Implement
        return std::async([=] () {
            return Token("");
        });
    }

    std::future<Token> Service::getAccessTokenClientCredentialsGrant() const
    {
        //TODO: Implement
        return std::async([=] () {
            return Token("");
        });
    }

    void Service::signRequest(OAuth::HttpRequest &request, const Token &token) const
    {
        if (token.getTokenType() == Token::BEARER_TOKEN)
            request.addHeader("Authorization", "Bearer " + token.getAccessToken());
        else
            throw std::logic_error("Unsupported token type " + token.getTokenType());
    }
}
