#include "RsaSignature.h"

#include "RsaSignatureWrapper.h"

namespace OAuth
{
    const std::string rsaSha1Signature(const std::string &baseString,
        const std::string &rsaKey, const std::string &)
    {
        RsaSignatureWrapper rsaWrapper(rsaKey);
        return rsaWrapper.generateSignature(baseString);
    }
}
