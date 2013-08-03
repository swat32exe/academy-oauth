#ifndef SIGNATURE_H_
#define SIGNATURE_H_

#include <string>

namespace OAuth
{
    enum SignatureMethod {HMAC_SHA1, RSA_SHA1, PLAINTEXT};

    /**
     * Signs HTTP request returning the OAuth signature
     */
    class Signature
    {
    public:
        Signature(SignatureMethod method = HMAC_SHA1);

        /**
         * Generate and return OAuth signature
         * @param baseString Full OAuth base string
         * @param clientSecret Consumer secret
         * @param tokenSecret Token secret. Leave empty when requesting temporary credentials
         * @returns OAuth signature
         */
        const std::string get(const std::string &baseString,
                const std::string &clientSecret, const std::string &tokenSecret = "");

    private:
        const std::string hmacSha1Signature();
        const std::string rsaSha1Signature();
        const std::string plainTextSignature();

    private:
        std::string baseString;
        std::string clientSecret;
        std::string tokenSecret;
        SignatureMethod method;
    };
}
#endif
