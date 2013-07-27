#include <sstream>
#include <set>

#include "ParameterList.h"

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

    void ParameterList::add(std::string name, std::string value)
    {
        parameters.push_back(std::make_pair(name, value));
    }

    void ParameterList::addQueryString(const std::string &queryString)
    {
        std::string query = queryString;
        if(queryString.find(QUERY_SEPARATOR) == 0) {
            query = queryString.substr(1);
        }

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
        for(parameters_t::const_iterator pair = parameters.begin();
                pair != parameters.end(); ++pair) {
            queryString += pair->first + PAIR_SEPARATOR + pair->second;
            queryString += PARAMETER_SEPARATOR;
        }
        return queryString.substr(0, queryString.length() - 1);
    }

    const std::string ParameterList::asBaseString() const
    {
        typedef std::set<std::pair <std::string, std::string> > StringPairSet;
        StringPairSet parametersSet;
        for(parameters_t::const_iterator pair = parameters.begin();
                pair != parameters.end(); ++pair) {
            // TODO: urlencode parameters here
            std::string name = pair->first;
            std::string value = pair->second;
            parametersSet.insert(std::make_pair(name, value));
        }

        ParameterList sortedParameters;
        for(StringPairSet::const_iterator pair = parametersSet.begin();
                pair != parametersSet.end(); ++pair) {
            sortedParameters.add(pair->first, pair->second);
        }
        return sortedParameters.asQueryString().substr(1);
    }
}
