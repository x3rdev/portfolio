//
// Created by nicol on 3/28/2026.
//

#include <gtest/gtest.h>

#include "../src/indexer/json/JsonString.h"

TEST(JsonStringTest, ParsesSimpleString) {
    auto input_str = "\"hello\"";
    auto parsed = JsonString(input_str);
    ASSERT_TRUE(parsed.has_value());
    EXPECT_EQ(parsed.get_value(), "hello");
}

TEST(JsonStringTest, ParsesEmptyString) {
    auto input_str = "\"\"";
    auto parsed = JsonString(input_str);
    ASSERT_TRUE(parsed.has_value());
    EXPECT_EQ(parsed.get_value(), "");
}

TEST(JsonStringTest, RejectsUnquotedValue) {
    auto input_str = "hello";
    auto parsed = JsonString(input_str);
    EXPECT_FALSE(parsed.has_value());
}
