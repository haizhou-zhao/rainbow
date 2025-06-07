#pragma once
#include "Catalog.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

class InMemoryCatalog : public Catalog {
private:
  std::unordered_map<std::string,
                     std::unordered_map<std::string, std::shared_ptr<Table>>>
      catalogMemory;

public:
  virtual std::shared_ptr<Table> createTable(const Table &table) override;

  virtual bool tableExists(const std::string &database,
                           const std::string &table) override;

  virtual std::shared_ptr<Table> getTable(const std::string &database,
                                          const std::string &table) override;

  virtual std::shared_ptr<Table>
  updateTable(const std::string &database, const std::string &table,
              const TableUpdate &update) override;
};
