#include <gtest/gtest.h>
#include "../../../src/units/position_vector.h"


TEST(PositionVector, ParameterizedConstructor) {
    auto *position_vector = new PositionVector(2.0, 4.0, 8.0);
    EXPECT_EQ(position_vector->get_x(), 2.0);
    EXPECT_EQ(position_vector->get_y(), 4.0);
    EXPECT_EQ(position_vector->get_z(), 8.0);
}

TEST(PositionVector, BasicConstructor) {
    auto *position_vector = new PositionVector();
    EXPECT_EQ(position_vector->get_x(), 0);
    EXPECT_EQ(position_vector->get_y(), 0);
    EXPECT_EQ(position_vector->get_z(), 0);
}

TEST(PositionVector, MaxValue) {
    auto *position_vector = new PositionVector(2.0, 4.0, 8.0);
    EXPECT_EQ(position_vector->GetMaxAbsoluteValue(), 8.0);
}

TEST(PositionVector, PlusOperator) {
    auto pv1 = PositionVector(2.0, 4.0, 8.0);
    auto pv2 = PositionVector(2.0, 4.0, 8.0);
    auto pv3 = pv1 + pv2;
    EXPECT_EQ(pv3.get_x(), 4.0);
    EXPECT_EQ(pv3.get_y(), 8.0);
    EXPECT_EQ(pv3.get_z(), 16.0);
}

TEST(PositionVector, PlusEqualsOperator) {
    auto pv1 = PositionVector(2.0, 4.0, 8.0);
    auto pv2 = PositionVector(2.0, 4.0, 8.0);
    pv1 += pv2;
    EXPECT_EQ(pv1.get_x(), 4.0);
    EXPECT_EQ(pv1.get_y(), 8.0);
    EXPECT_EQ(pv1.get_z(), 16.0);
}

TEST(PositionVector, MinusOperator) {
    auto pv1 = PositionVector(4.0, 8.0, 16.0);
    auto pv2 = PositionVector(2.0, 4.0, 8.0);
    auto pv3 = pv1 - pv2;
    EXPECT_EQ(pv3.get_x(), 2.0);
    EXPECT_EQ(pv3.get_y(), 4.0);
    EXPECT_EQ(pv3.get_z(), 8.0);
}

TEST(PositionVector, MultiplicationOperator) {
    auto pv1 = PositionVector(2.0, 4.0, 8.0);
    auto pv3 = pv1 * 2;
    EXPECT_EQ(pv3.get_x(), 4.0);
    EXPECT_EQ(pv3.get_y(), 8.0);
    EXPECT_EQ(pv3.get_z(), 16.0);
}

TEST(PositionVector, DivisionOperator) {
    auto pv1 = PositionVector(4.0, 8.0, 16.0);
    auto pv3 = pv1 / 2;
    EXPECT_EQ(pv3.get_x(), 2.0);
    EXPECT_EQ(pv3.get_y(), 4.0);
    EXPECT_EQ(pv3.get_z(), 8.0);
}
