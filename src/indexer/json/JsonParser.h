//
// Created by nicol on 3/24/2026.
//

#ifndef PORTFOLIO_JSONREADER_H
#define PORTFOLIO_JSONREADER_H
#include <string>

#include "JsonArray.h"
#include "JsonObject.h"
#include "JsonPair.h"

std::unique_ptr<JsonElement> parseString(const std::string& str);

std::unique_ptr<JsonArray> parseArray(const std::string& str, int index);

std::unique_ptr<JsonObject> parseObject(const std::string& str, int index);

template<typename T>
std::unique_ptr<JsonPair<T>> parsePrimitive(const std::string& str, int index);



#endif //PORTFOLIO_JSONREADER_H