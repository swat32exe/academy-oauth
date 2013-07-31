#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "HttpRequestTests.h"
#include "Utility/UrlEncodeDecode.h"
#include "Utility/NormalizeUrl.h"
#include "Utility/HostResourceFromUrl.h"
#include "ParameterListTests.h"

GTEST_API_ int main(int argc, char **argv)
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
