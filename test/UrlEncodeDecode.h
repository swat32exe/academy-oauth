#include <Utility.h>

#include <string>

namespace OAuth
{
    class UrlEncodeDecodeTests: public testing::Test
    {
    };

    TEST_F(UrlEncodeDecodeTests, url_encode_test_1)
    {
        std::string data = "do_not_ENCODE-_.~";
        ASSERT_EQ(data, Utility::urlEncode(data));
    }

    TEST_F(UrlEncodeDecodeTests, url_encode_test_2)
    {
        std::string data = "http://www.cplusplus.com/forum/general/84221/";
        ASSERT_EQ("http%3A%2F%2Fwww.cplusplus.com%2Fforum%2Fgeneral%2F84221%2F", Utility::urlEncode(data));
    }

    TEST_F(UrlEncodeDecodeTests, url_decode_test_1)
    {
        std::string data = "do_not_DECODE-_.~";
        ASSERT_EQ(data, Utility::urlDecode(data));
    }

    TEST_F(UrlEncodeDecodeTests, url_decode_test_2)
    {
        std::string data = "http%3A%2F%2Fwww.cplusplus.com%2Fforum%2Fgeneral%2F84221%2F";
        ASSERT_EQ("http://www.cplusplus.com/forum/general/84221/", Utility::urlDecode(data));

        // "+" character must be decoded as whitespace
        std::string withPlus = "2+q";
        ASSERT_STREQ("2 q", Utility::urlDecode(withPlus).c_str());
    }
}
