//
// Created by nicol on 3/23/2026.
//

#ifndef PORTFOLIO_JSONELEMENT_H
#define PORTFOLIO_JSONELEMENT_H

#include <memory>

template <typename T>
class JsonElement {
public:
    JsonElement& operator=(JsonElement& other) = delete;
    virtual ~JsonElement() = default;

    virtual bool has_value() const {
        return value_ != nullptr;
    }

    virtual T get_value() const {
        return *value_;
    }

protected:
    std::unique_ptr<T> value_;
};


#endif //PORTFOLIO_JSONELEMENT_H