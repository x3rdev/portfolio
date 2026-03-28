//
// Created by nicol on 3/26/2026.
//

#ifndef PORTFOLIO_JSONNUMBER_H
#define PORTFOLIO_JSONNUMBER_H
#include <memory>
#include <string>

#include "src/indexer/json/JsonElement.h"


class JsonNumber : public JsonElement<double> {
public:
    explicit JsonNumber(const std::string_view& cursor);

};


#endif //PORTFOLIO_JSONNUMBER_H