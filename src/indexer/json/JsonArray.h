//
// Created by nicol on 3/23/2026.
//

#ifndef PORTFOLIO_JSONARRAY_H
#define PORTFOLIO_JSONARRAY_H
#include <memory>
#include <vector>

#include "JsonElement.h"


class JsonArray : public JsonElement {
public:
    explicit JsonArray(std::vector<std::unique_ptr<JsonElement>>& elements);

private:
    std::vector<std::unique_ptr<JsonElement>> elements_;
};


#endif //PORTFOLIO_JSONARRAY_H