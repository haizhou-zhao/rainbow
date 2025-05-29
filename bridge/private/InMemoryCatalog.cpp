#include "InMemoryCatalog.h"
#include "SqlPlan.h"

std::string InMemoryCatalog::DEFAULT_DATABASE = "default";

void InMemoryCatalog::createTable(const std::string &database,
                                  const std::string &table) {
  if (database.empty()) {
    catalogMemory[DEFAULT_DATABASE].insert(table);
  } else {
    catalogMemory[database].insert(table);
  }
}

bool InMemoryCatalog::tableExists(const std::string &database,
                                  const std::string &table) {
  if (database.empty()) {
    return catalogMemory.find(DEFAULT_DATABASE) != catalogMemory.end() &&
           catalogMemory[DEFAULT_DATABASE].find(table) !=
               catalogMemory[DEFAULT_DATABASE].end();
  } else {
    return catalogMemory.find(database) != catalogMemory.end() &&
           catalogMemory[database].find(table) != catalogMemory[database].end();
  }
}
