#include "Extractor.h"
#include "Url.h"

#include <set>

namespace OAuth
{
    namespace Utility
    {
        std::string extractBaseString(const ParameterList &list)
        {
            const parameters_t &parameters = list.getParameters();
            std::set<StringPair> parametersSet;
            for (parameters_t::const_iterator pair = parameters.begin();
                    pair != parameters.end(); ++pair) {
                parametersSet.insert(urlEncodedPair(pair->first, pair->second));
            }

            ParameterList sortedParameters;
            for (std::set<StringPair>::const_iterator pair = parametersSet.begin();
                    pair != parametersSet.end(); ++pair) {
                sortedParameters.add(pair->first, pair->second);
            }
            std::string baseString = sortedParameters.asQueryString().substr(1);
            return urlEncode(baseString);
        }

        std::string extractAuthorizationHeader(const ParameterList &list)
        {
            const std::string HEADER_SEPARATOR = ",\r\n";
            const parameters_t &parameters = list.getParameters();
            std::string authorizationHeader = "OAuth ";
            for(std::vector<StringPair>::const_iterator pair = parameters.begin();
                    pair != parameters.end(); ++pair) {
                authorizationHeader += pair->first + "=\""
                        + pair->second + '"' + HEADER_SEPARATOR;
            }
            authorizationHeader = authorizationHeader.substr(0,
                    authorizationHeader.find_last_of(HEADER_SEPARATOR));
            return authorizationHeader;
        }

        StringPair urlEncodedPair(const std::string &name,
                const std::string &value)
        {
            std::string encodedName = urlEncode(name);
            std::string encodedValue = urlEncode(value);
            return std::make_pair(encodedName, encodedValue);
        }
    }
}
