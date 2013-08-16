#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "HttpRequestTests.h"
#include "UrlEncodeDecode.h"
#include "NormalizeUrl.h"
#include "HostResourceFromUrl.h"
#include "ParameterListTests.h"
#include "DefaultSendRequestTests.h"
#include "SignatureTests.h"
#include "RsaSignatureTests.h"
#include "ExtractorTests.h"
#include "TokenTests.h"
#include "ServiceTests.h"
#include "SingleLevelJSONTests.h"

GTEST_API_ int main(int argc, char **argv)
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
