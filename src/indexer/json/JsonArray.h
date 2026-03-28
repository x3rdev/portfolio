//
// Created by nicol on 3/28/2026.
//

#ifndef PORTFOLIO_JSONARRAY_H
#define PORTFOLIO_JSONARRAY_H
#include <string>
#include <vector>

#include "JsonElement.h"


class JsonArray : public JsonElement<std::pmr::vector<std::string>> {
public:
    explicit JsonArray(const std::string_view& cursor);
};


#endif //PORTFOLIO_JSONARRAY_H