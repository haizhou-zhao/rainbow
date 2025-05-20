#pragma once
#include <memory>
#include <string>

class ResolvedIdentifier;

class Catalog : public std::enable_shared_from_this<Catalog> {
public:
  virtual void createTable(const std::string &database,
                           const std::string &table) = 0;

  virtual bool tableExists(const std::string &database,
                           const std::string &table) = 0;
};

class CatalogManager {
private:
  static std::shared_ptr<Catalog> CURRENT_CATALOG;

public:
  std::shared_ptr<Catalog> currentCatalog();

  std::shared_ptr<Catalog> catalog(std::string catalogName);
};
