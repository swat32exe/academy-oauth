#ifndef __UTILITY_H
#define __UTILITY_H

#include <string>
#include <sstream>

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

        /**
         * Extracts host from url
         * @param url url, something like www.example.com/test
         * @returns host, something like www.example.com
         */
        std::string hostFromUrl(std::string url);
        /**
         * Extracts host from url
         * @param url url, something like www.example.com/test
         * @returns host, something like /test
         */
        std::string resourceFromUrl(std::string url);
        /**
         * Converts long long to string. Needed because of gcc bug:
         * Bug 52015 - std::to_string does not work under MinGW
         */
        template<typename T> std::string toString(T x)
        {
            std::stringstream stringStream;
            stringStream<<x;
            return stringStream.str();
        }
    }
}

#endif