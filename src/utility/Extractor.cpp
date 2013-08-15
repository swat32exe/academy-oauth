#include "Extractor.h"
#include "Url.h"

#include <set>

#include <oauth/HttpRequest.h>

namespace OAuth
{
    namespace Utility
    {
        std::string extractBaseString(const ParameterList &list)
        {
            const parameters_t &parameters = list.getParameters();
            std::set<StringPair> parametersSet;
            for (auto pair : parameters) {
                parametersSet.insert(urlEncodedPair(pair.first, pair.second));
            }

            ParameterList sortedParameters;
            for (auto pair : parametersSet) {
                sortedParameters.add(pair.first, pair.second);
            }
            std::string baseString = sortedParameters.asQueryString().substr(1);
            return urlEncode(baseString);
        }

        std::string extractAuthorizationHeader(const ParameterList &list)
        {
            const std::string HEADER_SEPARATOR = ",\r\n";
            const parameters_t &parameters = list.getParameters();
            std::string authorizationHeader = "OAuth";
            for(auto pair : parameters) {
                authorizationHeader += " " + urlEncode(pair.first) + "=\""
                        + urlEncode(pair.second) + '"' + HEADER_SEPARATOR;
            }
            authorizationHeader = authorizationHeader.substr(0,
                    authorizationHeader.find_last_of(","));
            return authorizationHeader;
        }

        StringPair urlEncodedPair(const std::string &name,
                const std::string &value)
        {
            std::string encodedName = urlEncode(name);
            std::string encodedValue = urlEncode(value);
            return std::make_pair(encodedName, encodedValue);
        }

        ParameterList extractBodyParameters(const HttpRequest &request)
        {
            const header_t &headers = request.getHeaders();
            const auto contentType = headers.find(HEADER_CONTENT_TYPE);
            if (contentType != headers.end() && contentType->second == FORM_URLENCODED)
                return ParameterList(request.getBody());
            return ParameterList();
        }
    }
}
