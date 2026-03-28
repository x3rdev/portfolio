//
// Created by nicol on 3/26/2026.
//

#ifndef PORTFOLIO_JSONSTRING_H
#define PORTFOLIO_JSONSTRING_H
#include <memory>
#include <optional>

#include "src/indexer/json/JsonElement.h"


class JsonString : public JsonElement<std::string> {
public:
    explicit JsonString(const std::string_view& cursor);
};


#endif //PORTFOLIO_JSONSTRING_H