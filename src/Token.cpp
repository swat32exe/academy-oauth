#include <Token.h>

#include <exception>

#include "ParameterList.h"
#include "utility/Url.h"

namespace OAuth
{
    Token::Token()
    {
    }

    Token::Token(const std::string &data)
    {
        ParameterList parameterList(data);
        const parameters_t &parameters = parameterList.getParameters();
        bool tokenInitialized = false;
        bool secretInitialized = false;
        for(const StringPair &pair : parameters) {
            if (pair.first == "oauth_token") {
                token = pair.second;
                tokenInitialized = true;
            } else if (pair.first == "oauth_token_secret") {
                secret = pair.second;
                secretInitialized = true;
            }
        }
        if (!tokenInitialized || !secretInitialized)
            throw std::invalid_argument("parsing failed");
    }

    Token::Token(const std::string &token, const std::string &secret) :
        token(token)
        ,secret(secret)
    {
    }

    const std::string &Token::getToken() const
    {
        return token;
    }

    const std::string &Token::getSecret() const
    {
        return secret;
    }
}
