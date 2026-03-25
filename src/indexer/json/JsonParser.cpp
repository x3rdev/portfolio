//
// Created by nicol on 3/24/2026.
//

#include "JsonParser.h"

std::unique_ptr<JsonElement> parseString(const std::string& str) {
    std::unique_ptr<JsonElement> result;
    int i = 0;
    char c = str[i];
    if (c == '[') {
        result = std::unique_ptr<JsonElement>(parseArray(str, i).release());
    }
    if (c == '{') {
        result = std::unique_ptr<JsonElement>(parseObject(str, i).release());
    }
    return result;
}

std::unique_ptr<JsonArray> parseArray(const std::string& str, int index) {

}

std::unique_ptr<JsonObject> parseObject(const std::string& str, int index) {

}

template<typename T>
std::unique_ptr<JsonPair<T>> parsePrimitive(const std::string& str, int index) {

}