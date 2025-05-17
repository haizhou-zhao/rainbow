#pragma once
#include <memory>

class ResolvedIdentifier;

class Catalog {
public:
    virtual void createTable(std::shared_ptr<ResolvedIdentifier> identifier) = 0;
};
