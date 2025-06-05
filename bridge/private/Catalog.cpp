#include "Catalog.h"
#include "InMemoryCatalog.h"
#include <stdexcept>

void CatalogManager::addCatalog(std::string catalogName,
                                std::shared_ptr<Catalog> catalog) {
  if (catalogs.find(catalogName) != catalogs.end()) {
    throw std::runtime_error("Catalog with name '" + catalogName +
                             "' already exists.");
  }
  catalogs[catalogName] = catalog;
}

std::shared_ptr<Catalog> CatalogManager::catalog(std::string catalogName) {
  if (catalogs.find(catalogName) != catalogs.end()) {
    return catalogs[catalogName];
  }
  return nullptr;
}
