#include <stdexcept>

#include "crypto/HMAC_SHA1.h"
#include "crypto/base64.h"

#include "Signature.h"
#ifdef USE_OPENSSL
#include "crypto/rsa/RsaSignature.h"
#endif
#include "ParameterList.h"
#include "utility/Url.h"

namespace OAuth
{
    const std::string hmacSha1Signature(const std::string &baseString,
            const std::string &clientSecret, const std::string &tokenSecret);
    const std::string plainTextSignature(const std::string &baseString,
            const std::string &clientSecret, const std::string &tokenSecret);

    Signature::Signature(const std::string &name, SignatureFunction function) :
            name(name),
            function(function)
    {

    }
    Signature Signature::create(SignatureMethod method)
    {
        switch (method) {
#if USE_OPENSSL
        case RSA_SHA1:
            return Signature("RSA-SHA1", rsaSha1Signature);
#endif
        case PLAINTEXT:
            return Signature("PLAINTEXT", plainTextSignature);
        case HMAC_SHA1:
            return Signature("HMAC-SHA1", hmacSha1Signature);
        default:
            throw std::logic_error("Unsupported signature method.");
        }
    }

    std::string Signature::operator()(const std::string &baseString,
            const std::string &clientSecret, const std::string &tokenSecret)
    {
        return function(baseString, clientSecret, tokenSecret);
    }

    const std::string hmacSha1Signature(const std::string &baseString,
            const std::string &clientSecret, const std::string &tokenSecret)
    {
        const size_t DIGEST_SIZE = 20;
        const std::string key = clientSecret + '&' + tokenSecret;
        BYTE *byteKey = const_cast<BYTE*>(reinterpret_cast<const BYTE*> (key.c_str()));
        BYTE *byteBaseString = const_cast<BYTE*>
                (reinterpret_cast<const BYTE*> (baseString.c_str()));

        BYTE digest[DIGEST_SIZE];
        CHMAC_SHA1 HMAC_SHA1;
        HMAC_SHA1.HMAC_SHA1(byteBaseString, baseString.length(),
                byteKey, key.length(), digest);

        std::string stringDigest = base64_encode(digest, DIGEST_SIZE);
        return stringDigest;
    }

    const std::string plainTextSignature(const std::string&,
            const std::string &clientSecret, const std::string &tokenSecret)
    {
        return clientSecret + '&' + tokenSecret;
    }
}
