#include <Utility.h>

#include <gtest/gtest.h>
#include <string>

namespace OAuth
{
    class HostResourceFromUrlTests: public testing::Test
    {
    };

    TEST_F(HostResourceFromUrlTests, host_resource_from_url_test1)
    {
        std::string url = "http://www.example.com/resource";
        ASSERT_EQ("www.example.com", Utility::hostFromUrl(url));
        ASSERT_EQ("/resource", Utility::resourceFromUrl(url));
    }

    TEST_F(HostResourceFromUrlTests, host_resource_from_url_test2)
    {
        std::string url = "http://www.example.com/another/resource";
        ASSERT_EQ("www.example.com", Utility::hostFromUrl(url));
        ASSERT_EQ("/another/resource", Utility::resourceFromUrl(url));
    }

    TEST_F(HostResourceFromUrlTests, host_resource_from_url_test3)
    {
        std::string url = "http://www.example.com/";
        ASSERT_EQ("www.example.com", Utility::hostFromUrl(url));
        ASSERT_EQ("/", Utility::resourceFromUrl(url));
    }
}
