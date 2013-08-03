#include <Token.h>

#include <exception>

namespace OAuth
{
    Token::Token(const std::string &data)
    {
        (void)data;
        // TODO:Implement Token
    }

    Token::Token(const std::string &token, const std::string &secret) :
        token(token)
        ,secret(secret)
    {
    	// TODO:Implement Token
    }

    const std::string &Token::getSecret() const
    {
        return secret;
    }
}
