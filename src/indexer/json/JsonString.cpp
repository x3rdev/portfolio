//
// Created by nicol on 3/26/2026.
//

#include <string>
#include "JsonString.h"

#include <memory>

JsonString::JsonString(const std::string_view& cursor) {
    std::string str;
    int i = 0;
    while (i < cursor.length() && cursor[i] != '"') {
        i++;
    }
    if (i == cursor.length()) {
        value_ = nullptr;
        return;
    }
    i++;
    while (i < cursor.length() && cursor[i] != '"') {
        str.push_back(cursor[i]);
        i++;
    }
    if (i == cursor.length()) {
        value_ = nullptr;
        return;
    }

    value_ = std::make_unique<std::string>(str);
}
