//
// Created by nicol on 3/25/2026.
//

#ifndef PORTFOLIO_JSONBOOLEAN_H
#define PORTFOLIO_JSONBOOLEAN_H
#include <string>

#include "src/indexer/json/JsonElement.h"


class JsonBoolean : public JsonElement<bool> {
public:
    explicit JsonBoolean(const std::string_view& cursor);
};


#endif //PORTFOLIO_JSONBOOLEAN_H