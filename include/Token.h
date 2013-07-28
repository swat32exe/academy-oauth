#ifndef __TOKEN_H
#define __TOKEN_H

#include <string>

namespace OAuth
{
    class Token
    {
        std::string token;
        std::string secret;

    public:
        /**
         * Attempts to extract token data from string
         * @param data string to extract token from
         * @throws invalid_argument
         */
        Token(std::string data);
        /**
         * Creates token from specified data
         * @param token token identifier
         * @param secret token secret
         */
        Token(std::string token, std::string secret);
    };
}

#endif
