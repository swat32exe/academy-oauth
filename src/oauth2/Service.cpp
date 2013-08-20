#include <oauth2/Service.h>

#include <string>
#include <stdexcept>
#include <functional>
#include <future>
#include <sstream>

#include <oauth2/Token.h>
#include <oauth2/TokenException.h>
#include <utility/Url.h>
#include <utility/SingleLevelJson.h>
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
        const std::string parametersString = OAuth::Utility::extractQueryParameters(url);
        const OAuth::ParameterList parametersList(parametersString);
        OAuth::parameters_map_t parameters = parametersList.getParametersAsMap();

        if (parameters.find("error") != parameters.end()) {
            throw makeTokenError(parameters);
        } else {
            const std::string code = parameters.find("code")->second;

            OAuth::HttpRequest request(OAuth::HttpRequestType::POST,
                configuration.getTokenEndpoint());
            request.addHeader(OAuth::HEADER_CONTENT_TYPE, OAuth::FORM_URLENCODED);
            OAuth::ParameterList body;
            body.addRaw("grant_type", "authorization_code");
            body.addRaw("code", code);
            if (!configuration.getRedirectUri().empty())
                body.addRaw("redirect_uri", configuration.getRedirectUri());
            if (!configuration.getClientId().empty())
                body.addRaw("client_id", configuration.getClientId());
            request.setBody(body.asQueryString().substr(1));

            return std::async([=] () {
                return parseTokenResponse(Utility::parseSingleLevelJSON(sendRequest(request)));
            });
        }
    }

    std::future<Token> Service::getAccessTokenImplicitGrant(const std::string &url) const
    {
        const std::string parametersString = OAuth::Utility::extractQueryParameters(url);
        const OAuth::ParameterList parameters(parametersString);

        return std::async([=] () {
            return parseTokenResponse(parameters.getParametersAsMap());
        });
    }

    std::future<Token> Service::getAccessTokenOwnerCredentialsGrant() const
    {
        OAuth::HttpRequest request(OAuth::HttpRequestType::POST,
            configuration.getTokenEndpoint());
        request.addHeader(OAuth::HEADER_CONTENT_TYPE, OAuth::FORM_URLENCODED);
        OAuth::ParameterList body;
        body.addRaw("grant_type", "password");
        body.addRaw("username", configuration.getUsername());
        body.addRaw("password", configuration.getPassword());
        request.setBody(body.asQueryString().substr(1));

        return std::async([=] () {
            return parseTokenResponse(Utility::parseSingleLevelJSON(sendRequest(request)));
        });
    }

    std::future<Token> Service::getAccessTokenClientCredentialsGrant() const
    {
        OAuth::HttpRequest request(OAuth::HttpRequestType::POST,
            configuration.getTokenEndpoint());
        request.addHeader(OAuth::HEADER_CONTENT_TYPE, OAuth::FORM_URLENCODED);
        OAuth::ParameterList body;
        body.addRaw("grant_type", "client_credentials");
        request.setBody(body.asQueryString().substr(1));

        return std::async([=] () {
            return parseTokenResponse(Utility::parseSingleLevelJSON(sendRequest(request)));
        });
    }

    void Service::signRequest(OAuth::HttpRequest &request, const Token &token) const
    {
        if (token.getTokenType() == Token::BEARER_TOKEN)
            request.addHeader("Authorization", "Bearer " + token.getAccessToken());
        else
            throw std::logic_error("Unsupported token type " + token.getTokenType());
    }

    Token Service::parseTokenResponse(const OAuth::parameters_map_t &parameters) const
    {
        if (parameters.find("error") != parameters.end()) {
            throw makeTokenError(parameters);
        } else {
            auto accessTokenIterator = parameters.find("access_token");
            auto tokenTypeIterator = parameters.find("token_type");
            auto expiresInIterator = parameters.find("expires_in");
            auto refreshTokenIterator = parameters.find("refresh_token");

            if (accessTokenIterator == parameters.end() || tokenTypeIterator == parameters.end())
                throw std::invalid_argument("Token parsing failed. Required parameter not set");
            std::string accessToken = accessTokenIterator->second;
            std::string tokenType = tokenTypeIterator->second;

            int expiresIn = Token::EXPIRES_UNDEFINED;
            if (expiresInIterator != parameters.end()) {
                std::istringstream expiresInStream(expiresInIterator->second);
                expiresInStream>>expiresIn;
            }

            std::string refreshToken = Token::REFRESH_UNDEFINED;
            if (refreshTokenIterator != parameters.end())
                refreshToken = refreshTokenIterator->second;

            return Token(accessToken, expiresIn, refreshToken, tokenType);
        }
    }

    TokenException Service::makeTokenError(const OAuth::parameters_map_t &parameters) const
    {
        std::string error = parameters.find("error")->second;

        std::string description;
        auto descriptionIterator = parameters.find("error_description");
        if (descriptionIterator != parameters.end())
            description = descriptionIterator->second;

        std::string uri;
        auto uriIterator = parameters.find("error_uri");
        if (uriIterator != parameters.end())
            uri= uriIterator->second;

        return TokenException(error, description, uri);
    }
}
