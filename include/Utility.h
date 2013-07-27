#ifndef __UTILITY_H
#define __UTILITY_H

#include <string>

namespace OAuth
{
    namespace Utility
    {
        std::string urlEncode(std::string data);
        std::string urlDecode(std::string data);
    }
}

#endif
