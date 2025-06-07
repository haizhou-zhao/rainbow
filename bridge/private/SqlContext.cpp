#include "SqlContext.h"
#include "Catalog.h"
#include <numeric>

std::shared_ptr<Catalog> SqlContext::currentCatalog() const {
  return catalogManager->catalog(currentCatalogName);
}

std::string SqlContext::currentDatabaseName() const {
  return std::accumulate(currentDatabaseNameParts.begin(),
                         currentDatabaseNameParts.end(), std::string{},
                         [](const std::string &a, const std::string &b) {
                           return a.empty() ? b : a + "." + b;
                         });
}
