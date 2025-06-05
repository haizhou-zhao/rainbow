#include "InMemoryCatalog.h"
#include <stdexcept>

void InMemoryCatalog::createTable(const std::string &database,
                                  const std::string &table) {
  if (database.empty()) {
    throw std::runtime_error("Database name cannot be empty");
  } else {
    catalogMemory[database].insert(table);
  }
}

bool InMemoryCatalog::tableExists(const std::string &database,
                                  const std::string &table) {
  if (database.empty()) {
    throw std::runtime_error("Database name cannot be empty");
  } else {
    return catalogMemory.find(database) != catalogMemory.end() &&
           catalogMemory[database].find(table) != catalogMemory[database].end();
  }
}
