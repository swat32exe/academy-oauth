#include "Signature.h"

#include <string>

namespace OAuthTesting
{
    class RsaSignatureTests : public testing::Test
    {
    };

    TEST(RsaSignatureTests, testRsaSignature)
    {
        std::string baseString = "GET&http%3A%2F%2Fterm.ie%2Foauth%2Fexample%2Frequest_token.php"
                "&oauth_consumer_key%3Dkey%26oauth_nonce%3Da813435c088711445c44adc2aebcc7d2"
                "%26oauth_signature_method%3DRSA-SHA1"
                "%26oauth_timestamp%3D1375967156%26oauth_version%3D1.0";
        OAuth::Signature signature = OAuth::Signature::create(OAuth::RSA_SHA1);
        std::string expectedSignature = "Bm1InqdcWox8Lbp1XfUCehe0Ft5NvPMdv+FQOcCmedb0k"
                "3HTSHwDd98T9cKWYxGXEaoizhKjkg5vPR3WFFjXA31GsfIBqSUaE9+8drqAB2hVfbaTLq"
                "6F07endt56ylyxHjNOV8sZ3sCO2YLj51dV6H89mJsB5gpqnfSWQGCwngQ=";
        std::string producedSignature = signature(baseString, "test/rsaKey.pem");
        ASSERT_STREQ(expectedSignature.c_str(), producedSignature.c_str());
    }
}
