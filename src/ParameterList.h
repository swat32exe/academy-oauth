#ifndef PARAMETERLIST_H_
#define PARAMETERLIST_H_

#include <vector>
#include <string>

namespace OAuth
{
    typedef std::vector<std::pair<std::string, std::string> > parameters_t;

    /**
     *  Class for working with POST/GET parameters
     */
    class ParameterList
    {
    public:
        static const char QUERY_SEPARATOR;
        static const char PARAMETER_SEPARATOR;
        static const char PAIR_SEPARATOR;

    public:
        ParameterList();
        /**
         *  Creates parameter list from query string
         *  @param queryString Query string
         */
        ParameterList(const std::string& queryString);

        /**
         *  Adds parameter to list
         *  @param name Name part of "name=value" pair
         *  @param value Value part of "name=value" pair
         */
        void add(std::string name, std::string value);

        /**
         * Adds parameters to list from query string
         * @param queryString Query string
         */
        void addQueryString(const std::string &queryString);

        /**
         * Constructs query string from parameter list
         * @returns Query string
         */
        const std::string asQueryString() const;

        /**
         * Constructs OAuth Base string
         * @returns OAuth Base string
         */
        const std::string asBaseString() const;

    private:
        parameters_t parameters;
    };

}
#endif
