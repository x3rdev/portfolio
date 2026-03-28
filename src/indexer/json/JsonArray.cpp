//
// Created by nicol on 3/28/2026.
//

#include "JsonArray.h"

#include <algorithm>

JsonArray::JsonArray(const std::string_view& cursor) {
    auto input_str = std::string(cursor);
    input_str.erase(std::remove_if(input_str.begin(), input_str.end(), isspace), input_str.end());

    if (input_str.front() == '[' && input_str.back() == ']') {
        int i = 0;
        while (i < input_str.length()) {

        }
    } else {
        value_ = nullptr;
    }
}
