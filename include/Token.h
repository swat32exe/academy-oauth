#ifndef __TOKEN_H
#define __TOKEN_H

#include <string>

namespace OAuth
{
    /**
     *  Represents token credentials
     *  Stores parameters named as oauth_token and oauth_token_secret in RFC 5849
     */
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
        /**
         *  Returns token identifier, aka oauth_token
         *  @returns token identifier
         */
        const std::string &getToken() const;
        /**
         *  Returns token secret, aka oauth_token_secret
         *  @returns token secret
         */
        const std::string &getSecret() const;
    };
}

#endif
