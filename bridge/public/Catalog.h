#pragma once
#include <memory>
#include <string>
#include <unordered_map>

struct Table;
struct TableUpdate;

class Catalog : public std::enable_shared_from_this<Catalog> {
public:
  virtual std::shared_ptr<Table> createTable(const Table &table) = 0;

  virtual bool tableExists(const std::string &database,
                           const std::string &table) = 0;

  virtual std::shared_ptr<Table> getTable(const std::string &database,
                                          const std::string &table) = 0;

  virtual std::shared_ptr<Table> updateTable(const std::string &database,
                                             const std::string &table,
                                             const TableUpdate &update) = 0;
};

class CatalogManager {
private:
  std::unordered_map<std::string, std::shared_ptr<Catalog>> catalogs;

public:
  void addCatalog(std::string catalogName, std::shared_ptr<Catalog> catalog);

  std::shared_ptr<Catalog> catalog(std::string catalogName);
};
