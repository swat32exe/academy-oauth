#ifndef RSASIGNATURE_H_
#define RSASIGNATURE_H_

#include <string>

namespace OAuth1
{
    const std::string rsaSha1Signature(const std::string &baseString,
            const std::string &rsaKey, const std::string &);
}
#endif
