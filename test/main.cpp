#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "HttpRequestTests.h"

GTEST_API_ int main(int argc, char **argv)
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
