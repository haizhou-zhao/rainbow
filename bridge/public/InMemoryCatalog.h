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
    virtual void createTable(const std::string& database, const std::string& table) override;

    virtual bool tableExists(const std::string& database, const std::string& table) override;

};
