#include "SqlContext.h"
#include "Catalog.h"

std::shared_ptr<Catalog> SqlContext::currentCatalog() const {
  return catalogManager->catalog(currentCatalogName);
}
