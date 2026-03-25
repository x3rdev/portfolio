//
// Created by nicol on 3/23/2026.
//

#ifndef PORTFOLIO_JSONOBJECT_H
#define PORTFOLIO_JSONOBJECT_H
#include <memory>
#include <string>
#include <unordered_map>

#include "JsonElement.h"


class JsonObject : public JsonElement {
public:
    explicit JsonObject(std::unordered_map<std::string, std::unique_ptr<JsonElement>>& elements);

private:
    std::unordered_map<std::string, std::unique_ptr<JsonElement>> elements_;
};


#endif //PORTFOLIO_JSONOBJECT_H