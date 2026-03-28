//
// Created by nicol on 3/25/2026.
//

#include "JsonBoolean.h"

#include <memory>

JsonBoolean::JsonBoolean(const std::string_view& cursor) {
    std::string str;
    for (int i = 0; i < cursor.length(); i++) {
        char c = cursor[i];
        if (isspace(c) == 0) {
            str.push_back(c);
        }
    }
    if (str == "true") {
        value_ = std::make_unique<bool>(true);
    }
    else if (str == "false") {
        value_ = std::make_unique<bool>(false);
    }
    else {
        value_ = nullptr;
    }
}

