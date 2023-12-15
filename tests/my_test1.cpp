#include <gtest/gtest.h>

namespace {
int GetMeaningOfLife() { return 42; }
}  // namespace

TEST(TestTopic1, TrivialEquality){
    EXPECT_EQ(GetMeaningOfLife(),42);
}


TEST(TestTopic2, ChekcingAgain){
    EXPECT_EQ(GetMeaningOfLife(),40);
}
