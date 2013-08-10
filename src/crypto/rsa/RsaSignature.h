#ifndef RSASIGNATURE_H_
#define RSASIGNATURE_H_

#include <string>

namespace OAuth
{
    const std::string rsaSha1Signature(const std::string &baseString,
            const std::string &rsaKeyPath, const std::string &);
}
#endif
