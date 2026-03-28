//
// Created by nicol on 3/26/2026.
//

#include <gtest/gtest.h>

#include "../src/indexer/json/JsonNumber.h"

TEST(JsonNumberTest, ParsesPositiveInteger) {
    JsonNumber number("42");
    EXPECT_DOUBLE_EQ(42.0, number.get_value());
}

TEST(JsonNumberTest, ParsesNegativeInteger) {
    JsonNumber number("-7");
    EXPECT_DOUBLE_EQ(-7.0, number.get_value());
}

TEST(JsonNumberTest, ParsesFloatingPoint) {
    JsonNumber number("19.95");
    EXPECT_DOUBLE_EQ(19.95, number.get_value());
}

TEST(JsonNumberTest, ParsesScientificNotation) {
    JsonNumber number("1.23e3");
    EXPECT_DOUBLE_EQ(1230.0, number.get_value());
}

TEST(JsonNumberTest, ParsesWithWhitespace) {
    JsonNumber number("    3.5   ");
    EXPECT_DOUBLE_EQ(3.5, number.get_value());
}
