//
// Created by nicol on 3/26/2026.
//

#include "JsonNumber.h"


JsonNumber::JsonNumber(const std::string_view& cursor) {
    const auto str = std::string(cursor);
    value_ = std::make_unique<double>(std::stod(str));
}
