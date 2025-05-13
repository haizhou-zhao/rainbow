#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "Catalog.h"

class InMemoryCatalog : public Catalog {
private:
    std::unordered_map<std::string, std::unordered_set<std::string>> catalogMemory;
    static std::string DEFAULT_DATABASE;

public:
    virtual void createTable(std::shared_ptr<ResolvedIdentifier> identifier) override;

};

std::string InMemoryCatalog::DEFAULT_DATABASE = "default";
