#include "oauth/Signature.h"

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
        std::string rsaKey = "-----BEGIN PRIVATE KEY-----\r\n"
                "MIICdgIBADANBgkqhkiG9w0BAQEFAASCAmAwggJcAgEAAoGBALRiMLAh9iimur8V\r\n"
                "A7qVvdqxevEuUkW4K+2KdMXmnQbG9Aa7k7eBjK1S+0LYmVjPKlJGNXHDGuy5Fw/d\r\n"
                "7rjVJ0BLB+ubPK8iA/Tw3hLQgXMRRGRXXCn8ikfuQfjUS1uZSatdLB81mydBETlJ\r\n"
                "hI6GH4twrbDJCR2Bwy/XWXgqgGRzAgMBAAECgYBYWVtleUzavkbrPjy0T5FMou8H\r\n"
                "X9u2AC2ry8vD/l7cqedtwMPp9k7TubgNFo+NGvKsl2ynyprOZR1xjQ7WgrgVB+mm\r\n"
                "uScOM/5HVceFuGRDhYTCObE+y1kxRloNYXnx3ei1zbeYLPCHdhxRYW7T0qcynNmw\r\n"
                "rn05/KO2RLjgQNalsQJBANeA3Q4Nugqy4QBUCEC09SqylT2K9FrrItqL2QKc9v0Z\r\n"
                "zO2uwllCbg0dwpVuYPYXYvikNHHg+aCWF+VXsb9rpPsCQQDWR9TT4ORdzoj+Nccn\r\n"
                "qkMsDmzt0EfNaAOwHOmVJ2RVBspPcxt5iN4HI7HNeG6U5YsFBb+/GZbgfBT3kpNG\r\n"
                "WPTpAkBI+gFhjfJvRw38n3g/+UeAkwMI2TJQS4n8+hid0uus3/zOjDySH3XHCUno\r\n"
                "cn1xOJAyZODBo47E+67R4jV1/gzbAkEAklJaspRPXP877NssM5nAZMU0/O/NGCZ+\r\n"
                "3jPgDUno6WbJn5cqm8MqWhW1xGkImgRk+fkDBquiq4gPiT898jusgQJAd5Zrr6Q8\r\n"
                "AO/0isr/3aa6O6NLQxISLKcPDk2NOccAfS/xOtfOz4sJYM3+Bs4Io9+dZGSDCA54\r\n"
                "Lw03eHTNQghS0A==\r\n"
                "-----END PRIVATE KEY-----\r\n";
        std::string expectedSignature = "Bm1InqdcWox8Lbp1XfUCehe0Ft5NvPMdv+FQOcCmedb0k"
                "3HTSHwDd98T9cKWYxGXEaoizhKjkg5vPR3WFFjXA31GsfIBqSUaE9+8drqAB2hVfbaTLq"
                "6F07endt56ylyxHjNOV8sZ3sCO2YLj51dV6H89mJsB5gpqnfSWQGCwngQ=";
        std::string producedSignature = signature(baseString, rsaKey);
        ASSERT_STREQ(expectedSignature.c_str(), producedSignature.c_str());
    }
}
