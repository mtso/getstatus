#include <gtest/gtest.h>

#include "commit.h"
#include "util.h"

#include <vector>

TEST(GetStatusTests, CommitAppendTest) {
    std::vector<getstatus::Commit> target;
    std::vector<getstatus::Commit> source;

    getstatus::Commit c("", "", "", "", "");
    source.push_back(c);

    ASSERT_EQ(target.size(), 0);
    ASSERT_EQ(source.size(), 1);

    target += source;

    ASSERT_EQ(target.size(), 1);
    ASSERT_EQ(source.size(), 1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
