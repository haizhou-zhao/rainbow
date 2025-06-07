#include "InMemoryCatalog.h"
#include "DbEntities.h"
#include <stdexcept>

std::shared_ptr<Table> InMemoryCatalog::createTable(const Table &table) {
  if (table.database.empty()) {
    throw std::runtime_error("Database name cannot be empty");
  }
  if (table.name.empty()) {
    throw std::runtime_error("Table name cannot be empty");
  }
  if (tableExists(table.databaseName(), table.name)) {
    throw std::runtime_error("Table already exists: " + table.databaseName() +
                             "." + table.name);
  }
  catalogMemory[table.databaseName()][table.name] =
      std::make_shared<Table>(table);
  return catalogMemory[table.databaseName()][table.name];
}

bool InMemoryCatalog::tableExists(const std::string &database,
                                  const std::string &table) {
  if (database.empty()) {
    throw std::runtime_error("Database name cannot be empty");
  }
  if (table.empty()) {
    throw std::runtime_error("Table name cannot be empty");
  }

  return catalogMemory.find(database) != catalogMemory.end() &&
         catalogMemory[database].find(table) != catalogMemory[database].end();
}

std::shared_ptr<Table> InMemoryCatalog::getTable(const std::string &database,
                                                 const std::string &table) {
  if (catalogMemory.find(database) == catalogMemory.end()) {
    throw std::runtime_error("Database does not exist: " + database);
  }
  if (catalogMemory[database].find(table) == catalogMemory[database].end()) {
    throw std::runtime_error("Table does not exist: " + table);
  }
  return catalogMemory[database][table];
}

std::shared_ptr<Table> InMemoryCatalog::updateTable(const std::string &database,
                                                    const std::string &table,
                                                    const TableUpdate &update) {
  auto existingTable = getTable(database, table);
  // TODO: Implement prerequisite checks
  existingTable->schema = update.setSchema.schema;
  return existingTable;
}
