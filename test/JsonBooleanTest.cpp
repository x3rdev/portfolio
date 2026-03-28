//
// Created by nicol on 3/25/2026.
//

#include <gtest/gtest.h>

#include "../src/indexer/json/JsonBoolean.h"

TEST(JsonBooleanTest, ParsesTruePair) {
    auto input_str = "true";
    auto parsed = JsonBoolean(input_str);
    ASSERT_TRUE(parsed.has_value());
    EXPECT_TRUE(parsed.get_value());
}

TEST(JsonBooleanTest, ParsesFalsePair) {
    auto input_str = "false";
    auto parsed = JsonBoolean(input_str);
    ASSERT_TRUE(parsed.has_value());
    EXPECT_FALSE(parsed.get_value());
}

TEST(JsonBooleanTest, RejectsNonBooleanValue) {
    auto input_str = "42";
    auto parsed = JsonBoolean(input_str);
    EXPECT_FALSE(parsed.has_value());
}