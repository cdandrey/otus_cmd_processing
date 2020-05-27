
#include "../lib/cmd_processing.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <array>

TEST(test_cmd_processing,hello)
{
    EXPECT_EQ(true,true);
}
//----------------------------------------------------------------------------------


int main (int argc,char *argv[])
{
    ::testing::InitGoogleTest(&argc,argv);

    return RUN_ALL_TESTS();
}
