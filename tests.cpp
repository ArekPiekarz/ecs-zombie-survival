#include "setup/logger-setup.hpp"
#include <gtest/gtest.h>

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    setupLogger();
    return RUN_ALL_TESTS();
}

TEST(FooTest, DoesXyz)
{
    ASSERT_EQ(true, !false);
    // ASan test
    // int* foo = new int(8);
    // delete foo;
    // std::cout << *foo;

    // UBSan test
    // int foo = std::numeric_limits<int>::max();
    // foo += 1;
}
