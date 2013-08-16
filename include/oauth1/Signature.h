#ifndef SIGNATURE_H_
#define SIGNATURE_H_

#include <string>
#include <functional>

namespace OAuth1
{
    enum SignatureMethod {HMAC_SHA1, RSA_SHA1, PLAINTEXT};
    typedef std::function<std::string(const std::string&, const std::string&,
            const std::string&)> SignatureFunction;

    /**
     * Signs HTTP request returning the OAuth signature
     */
    class Signature
    {
    public:
        /**
         * Use Signature.create() method to create
         * Signature class with predefined signing method
         * @param name Name of signature method
         * @param function Custom signature function
         */
        Signature(const std::string &name, SignatureFunction function);

        /**
         * Create Signature class with one of predefined signing methods
         * @param method Predefined signing method
         */
        static Signature create(SignatureMethod method);

        /**
         * Generate and return OAuth signature
         * @param baseString Full OAuth base string
         * @param clientSecret Consumer secret
         * @param tokenSecret Token secret. Leave empty when requesting temporary credentials
         * @returns OAuth signature
         */
        std::string operator()(const std::string &baseString, const std::string &clientSecret,
                    const std::string &tokenSecret = "");

    private:
        std::string name;
        SignatureFunction function;
    };
}
#endif
