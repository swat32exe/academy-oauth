#include <Token.h>

#include <exception>

namespace OAuth
{
    Token::Token(std::string data)
    {
        (void)data;
        // TODO:Implement Token
    }

    Token::Token(std::string token, std::string secret) :
        token(token)
        ,secret(secret)
    {
    	// TODO:Implement Token
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
