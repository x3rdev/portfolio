//
// Created by nicol on 3/23/2026.
//

#include "JsonArray.h"

JsonArray::JsonArray(std::vector<std::unique_ptr<JsonElement>>& elements) {
    for (auto& elem : elements) {
        elements_.push_back(std::unique_ptr<JsonElement>(elem.release()));
    }

}