#include "RsaSignature.h"

#include <stdexcept>
#include <cstdio>

#include <openssl/rsa.h>
#include <openssl/pem.h>

#include "crypto/rsa/sha1.h"
#include "crypto/base64.h"

#ifdef __WIN32__
extern "C" {
    #include <openssl/applink.c>
}
#endif

namespace OAuth
{
    typedef unsigned char BYTE;

    void freeResources(EVP_PKEY_CTX *ctx, BYTE *signature = NULL);

    const std::string rsaSha1Signature(const std::string &baseString,
        const std::string &rsaKeyPath, const std::string &)
    {
        const size_t DIGEST_SIZE = 20;
        BYTE messageDigest[DIGEST_SIZE];
        sha1::calc(baseString.c_str(), baseString.length(), messageDigest);

        EVP_PKEY *signingKey = NULL;
        FILE *keyFile = fopen(rsaKeyPath.c_str(), "r");
        signingKey = PEM_read_PrivateKey(keyFile, NULL, NULL, NULL);
        fclose(keyFile);
        if(!signingKey) {
            throw std::invalid_argument("Invalid path or signing key");
        }

        EVP_PKEY_CTX *ctx;
        ctx = EVP_PKEY_CTX_new(signingKey, NULL);
        if (!ctx) {
            throw std::runtime_error("Error while creating ctx");
        }
        if (EVP_PKEY_sign_init(ctx) <= 0) {
            freeResources(ctx);
            throw std::runtime_error("Error while ctx initialization");
        }
        if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING) <= 0) {
            freeResources(ctx);
            throw std::runtime_error("Error while setting PKCS1 padding");
        }
        if (EVP_PKEY_CTX_set_signature_md(ctx, EVP_sha1()) <= 0) {
            freeResources(ctx);
            throw std::runtime_error("Error while setting sha1");
        }

        size_t signatureSize = EVP_PKEY_size(signingKey);
        BYTE *rawSignature = new BYTE[signatureSize];
        if (EVP_PKEY_sign(ctx, rawSignature, &signatureSize, messageDigest,
                DIGEST_SIZE) <= 0) {
            freeResources(ctx, rawSignature);
            throw std::runtime_error("Error while signing base string");
        }

        std::string signature = base64_encode(rawSignature, signatureSize);
        freeResources(ctx, rawSignature);
        return signature;
    }

    void freeResources(EVP_PKEY_CTX *ctx, BYTE *signature)
    {
        if(ctx) {
            EVP_PKEY_CTX_free(ctx);
        }
        if(signature) {
            delete[] signature;
        }
    }
}
