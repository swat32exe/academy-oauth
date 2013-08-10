#include "RsaSignatureWrapper.h"

#include <stdexcept>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#ifdef __WIN32__
extern "C" {
    #include <openssl/applink.c>
}
#endif

#include "crypto/rsa/sha1.h"
#include "crypto/base64.h"

namespace OAuth
{
    RsaSignatureWrapper::RsaSignatureWrapper(const std::string &rsaKey)
    {
        void *keyBuffer = const_cast<void*>(
                reinterpret_cast<const void*>(rsaKey.c_str()));
        bioKeyBuffer = BIO_new_mem_buf(keyBuffer, rsaKey.length());
        signingKey = PEM_read_bio_PrivateKey(bioKeyBuffer, NULL, NULL, NULL);
        if (!signingKey) {
            throw std::invalid_argument("Invalid RSA key");
        }
        cipherContext = EVP_PKEY_CTX_new(signingKey, NULL);
        if (!cipherContext) {
            throw std::runtime_error("Error while creating cipher context");
        }
    }

    std::string RsaSignatureWrapper::generateSignature(const std::string &baseString)
    {
        const size_t DIGEST_SIZE = 20;
        BYTE messageDigest[DIGEST_SIZE];
        sha1::calc(baseString.c_str(), baseString.length(), messageDigest);

        if (EVP_PKEY_sign_init(cipherContext) <= 0) {
            throw std::runtime_error("Error while context initialization");
        }
        if (EVP_PKEY_CTX_set_rsa_padding(cipherContext, RSA_PKCS1_PADDING) <= 0) {
            throw std::runtime_error("Error while setting PKCS1 padding");
        }
        if (EVP_PKEY_CTX_set_signature_md(cipherContext, EVP_sha1()) <= 0) {
            throw std::runtime_error("Error while setting sha1");
        }

        size_t signatureSize = EVP_PKEY_size(signingKey);
        rawSignature.reserve(signatureSize);
        if (EVP_PKEY_sign(cipherContext, rawSignature.data(), &signatureSize,
                messageDigest, DIGEST_SIZE) <= 0) {
            throw std::runtime_error("Error while signing base string");
        }

        std::string signature = base64_encode(rawSignature.data(), signatureSize);
        return signature;
    }

    RsaSignatureWrapper::~RsaSignatureWrapper()
    {
        if(bioKeyBuffer) {
            BIO_vfree(bioKeyBuffer);
        }
        if (signingKey) {
            EVP_PKEY_free(signingKey);
        }
        if (cipherContext) {
            EVP_PKEY_CTX_free(cipherContext);
        }
    }
}
