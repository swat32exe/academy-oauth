#ifndef RSASIGNATUREWRAPPER_H_
#define RSASIGNATUREWRAPPER_H_

#include <string>
#include <vector>
#include <cstdio>

struct evp_pkey_st;
struct evp_pkey_ctx_st;
struct bio_st;

namespace OAuth1
{
    typedef unsigned char BYTE;

    class RsaSignatureWrapper
    {
    public:
        RsaSignatureWrapper(const std::string &rsaKey);
        std::string generateSignature(const std::string &baseString);
        virtual ~RsaSignatureWrapper();

    private:
        evp_pkey_st *signingKey;
        evp_pkey_ctx_st *cipherContext;
        std::vector<BYTE> rawSignature;
        bio_st *bioKeyBuffer;
    };
}
#endif
