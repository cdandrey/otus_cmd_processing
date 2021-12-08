
#include <gtest/gtest.h>

TEST(test_CommandProcessing, hello)
{
    EXPECT_EQ(true, true);
}
//----------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
