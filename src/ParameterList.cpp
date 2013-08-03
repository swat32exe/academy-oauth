#include <sstream>
#include <set>

#include "ParameterList.h"
#include "Utility.h"

namespace OAuth
{
    const char ParameterList::QUERY_SEPARATOR = '?';
    const char ParameterList::PARAMETER_SEPARATOR = '&';
    const char ParameterList::PAIR_SEPARATOR = '=';

    ParameterList::ParameterList()
    {
    }

    ParameterList::ParameterList(const std::string& queryString)
    {
        this->addQueryString(queryString);
    }

    void ParameterList::add(const std::string &name, const std::string &value)
    {
        std::string decodedName = Utility::urlDecode(name);
        std::string decodedValue = Utility::urlDecode(value);
        parameters.push_back(std::make_pair(decodedName, decodedValue));
    }

    void ParameterList::add(const ParameterList &other)
    {
        this->addQueryString(other.asQueryString());
    }

    void ParameterList::addQueryString(const std::string &queryString)
    {
        if(queryString.empty()) {
            return;
        }
        std::string query = (queryString[0] == QUERY_SEPARATOR)
                ? queryString.substr(1) : queryString;
        std::stringstream queryStream(query);
        std::string pairString;
        while (std::getline(queryStream, pairString, PARAMETER_SEPARATOR)) {
            std::stringstream pairStream(pairString);
            std::string name;
            std::string value;
            std::getline(pairStream, name, PAIR_SEPARATOR);
            std::getline(pairStream, value, PAIR_SEPARATOR);
            this->add(name, value);
        }
    }

    const std::string ParameterList::asQueryString() const
    {
        std::string queryString(1, QUERY_SEPARATOR);
        if(parameters.empty()) {
            return queryString;
        }

        for(parameters_t::const_iterator pair = parameters.begin();
                pair != parameters.end(); ++pair) {
            StringPair encodedPair = this->getUrlEncodedPair(pair->first,pair->second);
            queryString += encodedPair.first + PAIR_SEPARATOR + encodedPair.second;
            queryString += PARAMETER_SEPARATOR;
        }
        return queryString.substr(0, queryString.length() - 1);
    }

    const std::string ParameterList::asBaseString() const
    {
        std::set<StringPair> parametersSet;
        for (parameters_t::const_iterator pair = parameters.begin();
                pair != parameters.end(); ++pair) {
            parametersSet.insert(this->getUrlEncodedPair(pair->first, pair->second));
        }

        ParameterList sortedParameters;
        for (std::set<StringPair>::const_iterator pair = parametersSet.begin();
                pair != parametersSet.end(); ++pair) {
            sortedParameters.add(pair->first, pair->second);
        }
        return sortedParameters.asQueryString().substr(1);
    }

    const ParameterMap ParameterList::asMap() const
    {
        ParameterMap parameterMap;
        for (std::vector<StringPair>::const_iterator pair = parameters.begin();
                pair != parameters.end(); ++pair) {
            parameterMap[pair->first] = pair->second;
        }
        return parameterMap;
    }

    StringPair ParameterList::getUrlEncodedPair(const std::string &name,
            const std::string &value) const
    {
        std::string encodedName = Utility::urlEncode(name);
        std::string encodedValue = Utility::urlEncode(value);
        return std::make_pair(encodedName, encodedValue);
    }
}
