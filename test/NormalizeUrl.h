#include <Utility.h>

#include <gtest/gtest.h>
#include <string>

namespace OAuth
{
    class NormalizeUrlTests: public testing::Test
    {
    };

    TEST_F(NormalizeUrlTests, normalize_url_test_1)
    {
        ASSERT_EQ("http://www.example.com/", Utility::normalizeUrl("http://www.example.com"));
        ASSERT_EQ("http://www.example.com/", Utility::normalizeUrl("www.example.com/"));
        ASSERT_EQ("http://www.example.com/", Utility::normalizeUrl("www.example.com"));
        ASSERT_EQ("http://www.example.com/", Utility::normalizeUrl("http://www.example.com/"));
    }

    TEST_F(NormalizeUrlTests, normalize_url_test_2)
    {
        ASSERT_EQ("http://www.example.com/resource", Utility::normalizeUrl("www.example.com/resource"));
        ASSERT_EQ("http://www.example.com/resource", Utility::normalizeUrl("http://www.example.com/resource"));
    }
}
