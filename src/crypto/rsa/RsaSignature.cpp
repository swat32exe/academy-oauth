#include "RsaSignature.h"

#include "RsaSignatureWrapper.h"

namespace OAuth1
{
    const std::string rsaSha1Signature(const std::string &baseString,
        const std::string &rsaKey, const std::string &)
    {
        RsaSignatureWrapper rsaWrapper(rsaKey);
        return rsaWrapper.generateSignature(baseString);
    }
}
