#ifndef SINGLE_LEVEL_JSON_H_
#define SINGLE_LEVEL_JSON_H_

#include <map>
#include <string>

namespace Utility
{
    typedef std::map<std::string, std::string> singleLevelJSON_t;

    /**
     *  Parse single level JSON to map<string,string>
     *  @param data JSON string. No arrays, no nested objects.
     *  @returns map<string,string>, representing object.
     *  e.g. {"name":"value"} will produce map where map["name"] == "value";
     */
    singleLevelJSON_t parseSingleLevelJSON(std::string data);
}

#endif
