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
}
