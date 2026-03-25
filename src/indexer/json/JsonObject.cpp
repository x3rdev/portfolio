//
// Created by nicol on 3/23/2026.
//

#include "JsonObject.h"

JsonObject::JsonObject(std::unordered_map<std::string, std::unique_ptr<JsonElement>>& elements) {
    for (auto& elem : elements) {
        elements_[elem.first] = std::unique_ptr<JsonElement>(elem.second.release());
    }
}