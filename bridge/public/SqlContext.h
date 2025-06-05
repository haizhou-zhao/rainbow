#pragma once
#include <memory>
#include <string>
#include <vector>

class Catalog;
class CatalogManager;

struct SqlContext {
  CatalogManager *catalogManager;
  std::string currentCatalogName = "default";
  std::vector<std::string> currentDatabaseName = {"default"};

  std::shared_ptr<Catalog> currentCatalog() const;
};
