#include <gtest/gtest.h>
#include "../../src/units/dimension.h"

TEST(Dimension, ParameterizedConstructor) {
    auto *dimension = new Dimension(2.0, 4.0, 8.0);
    EXPECT_EQ(dimension->get_length(), 2.0);
    EXPECT_EQ(dimension->get_height(), 4.0);
    EXPECT_EQ(dimension->get_depth(), 8.0);
}

TEST(Dimension, BasicConstructor) {
    auto *dimension = new Dimension();
    EXPECT_EQ(dimension->get_length(), 0);
    EXPECT_EQ(dimension->get_height(), 0);
    EXPECT_EQ(dimension->get_depth(), 0);
}

TEST(Dimension, MaxValue) {
    auto *dimension = new Dimension(2.0, 4.0, 8.0);
    EXPECT_EQ(dimension->GetMaxValue(), 8.0);
}