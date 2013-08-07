#ifndef EXTRACTOR_H_
#define EXTRACTOR_H_

#include <string>

#include "ParameterList.h"

namespace OAuth
{
    class HttpRequest;

    namespace Utility
    {
        /**
         * Encode parameters and return them as std::pair
         * @param name Name of a parameter
         * @param value Value of a parameter
         * @returns Encoded pair
         */
        StringPair urlEncodedPair(const std::string &name,
                const std::string &value);
        /**
         * Extract OAuth Base string from parameters
         * @param list List of parameters
         * @returns OAuth Base string
         */
        std::string extractBaseString(const OAuth::ParameterList &list);

        /**
         * Extract value for Authorization header from parameters
         * @param list List of parameters
         * @returns OAuth Authorization header
         */
        std::string extractAuthorizationHeader(const OAuth::ParameterList &list);

        /**
         *  Extract body parameters from HttpRequest
         *  @param request Request to extract from
         *  @returns Extracted parameters
         */
        ParameterList extractBodyParameters(const HttpRequest &request);
    }
}
#endif
