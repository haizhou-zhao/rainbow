#include "Catalog.h"
#include "InMemoryCatalog.h"

std::shared_ptr<Catalog> CatalogManager::CURRENT_CATALOG = nullptr;

std::shared_ptr<Catalog> CatalogManager::currentCatalog() {
  if (CURRENT_CATALOG == nullptr) {
    CURRENT_CATALOG = std::make_shared<InMemoryCatalog>();
  }
  return CURRENT_CATALOG;
}

std::shared_ptr<Catalog> CatalogManager::catalog(std::string catalogName) {
  // Only manage 1 catalog
  return currentCatalog();
}
