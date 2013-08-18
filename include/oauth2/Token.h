#include <string>

namespace OAuth2
{
    class Token
    {
    public:
        static const std::string BEARER_TOKEN;

        Token(const std::string &accessToken,
                int expiresIn = -1,
                const std::string &refreshToken = "",
                const std::string &tokenType = BEARER_TOKEN);

        const std::string &getTokenType() const;
        const std::string &getRefreshToken() const;
        const std::string &getAccessToken() const;

    private:
        std::string accessToken;
        std::string refreshToken;
        std::string tokenType;
        int expiresIn;
    };
}
