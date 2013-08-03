#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "HttpRequestTests.h"
#include "UrlEncodeDecode.h"
#include "NormalizeUrl.h"
#include "HostResourceFromUrl.h"
#include "ParameterListTests.h"
#include "SendRequestTests.h"
#include "GetAuthorizeUrlTests.h"

GTEST_API_ int main(int argc, char **argv)
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
