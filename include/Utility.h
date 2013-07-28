#ifndef __UTILITY_H
#define __UTILITY_H

#include <string>

namespace OAuth
{
    namespace Utility
    {
        /**
         *  Performs percent encoding of string
         *  @param data string to encode
         *  @returns encoded string
         */
        std::string urlEncode(std::string data);
        /**
         *  Decodes percent encoded string
         *  @param data string to decode
         *  @returns decoded string
         */
        std::string urlDecode(std::string data);
    }
}

#endif
