//
// Created by nicol on 3/23/2026.
//

#ifndef PORTFOLIO_JSONPRIMITIVE_H
#define PORTFOLIO_JSONPRIMITIVE_H
#include <memory>
#include <string>

#include "JsonElement.h"

template <typename T>
class JsonPair : public JsonElement {
public:
    explicit JsonPair(const std::string& input_str);
private:
    std::string name_;
    std::unique_ptr<T> value_;
};


#endif //PORTFOLIO_JSONPRIMITIVE_H