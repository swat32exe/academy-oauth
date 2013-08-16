#include <gtest/gtest.h>

#include <exception>

#include <utility/SingleLevelJSON.h>

namespace Utility
{
    std::string trimBracesIfExist(const std::string &data);
}

namespace OAuthTesting
{
    class SingleLevelJSONTests : public testing::Test
    {
    };

    TEST(SingleLevelJSONTests, trim_braces_correct)
    {
        ASSERT_EQ("data", Utility::trimBracesIfExist("  {data}\r\n"));
        ASSERT_EQ("data", Utility::trimBracesIfExist("{data}"));
        ASSERT_EQ("\"data\":\"{value}\"", Utility::trimBracesIfExist("{\"data\":\"{value}\"}"));
        ASSERT_EQ("\"data\":\"}value{\"", Utility::trimBracesIfExist("{\"data\":\"}value{\"}"));
        ASSERT_EQ("", Utility::trimBracesIfExist("  {}\r\n"));
    }

    TEST(SingleLevelJSONTests, trim_braces_no_braces)
    {
        ASSERT_EQ("\"data\":\"{value}\"", Utility::trimBracesIfExist("\"data\":\"{value}\""));
        ASSERT_EQ("\"data\":\"}value{\"", Utility::trimBracesIfExist("\"data\":\"}value{\""));
        ASSERT_EQ("  data\r\n", Utility::trimBracesIfExist("  data\r\n"));
        ASSERT_EQ("  ", Utility::trimBracesIfExist("  "));
        ASSERT_EQ("", Utility::trimBracesIfExist(""));
    }

    TEST(SingleLevelJSONTests, trim_braces_incorrect)
    {
        ASSERT_THROW(Utility::trimBracesIfExist("  {data\r\n"), std::invalid_argument);
        ASSERT_THROW(Utility::trimBracesIfExist("  data}\r\n"), std::invalid_argument);
    }

    TEST(SingleLevelJSONTests, parse_1)
    {
        Utility::string_pair_t parsed = Utility::parseSingleLevelJSON(
        "{\r\n"
        "   \"access_token\":\"2YotnFZFEjr1zCsicMWpAA\",\r\n"
        "   \"token_type\":\"example\",\r\n"
        "   \"expires_in\":3600,"
        "   \"refresh_token\":\"tGzv3JOkF0XG5Qx2TlKWIA\",\r\n"
        "   \"example_parameter\":\"example_value\",\r\n"
        "   \"escape_test\":\"\\\"\\\\\\/\\b\\f\\n\\r\\t\\u0041\"\r\n"
        "}\r\n");

        ASSERT_EQ("2YotnFZFEjr1zCsicMWpAA", parsed["access_token"]);
        ASSERT_EQ("example", parsed["token_type"]);
        ASSERT_EQ("3600", parsed["expires_in"]);
        ASSERT_EQ("tGzv3JOkF0XG5Qx2TlKWIA", parsed["refresh_token"]);
        ASSERT_EQ("example_value", parsed["example_parameter"]);
        ASSERT_EQ("\"\\/\b\f\n\r\tA", parsed["escape_test"]);
    }
}
