#include "SqlPlan.h"
#include "Catalog.h"
#include "DbEntities.h"
#include "SqlContext.h"
#include <stdexcept>

bool Identifier::nodeEquals(const TreeNode &other) const {
  const Identifier *o = dynamic_cast<const Identifier *>(&other);
  if (o) {
    return nameParts == o->nameParts;
  } else {
    return false;
  }
}

bool ResolvedIdentifier::nodeEquals(const TreeNode &other) const {
  const ResolvedIdentifier *o =
      dynamic_cast<const ResolvedIdentifier *>(&other);
  if (o) {
    return nameParts == o->nameParts && catalogName == o->catalogName;
  } else {
    return false;
  }
}

bool CreateTable::nodeEquals(const TreeNode &other) const {
  const CreateTable *o = dynamic_cast<const CreateTable *>(&other);
  if (o) {
    return *(name()) == *(o->name()) &&
           // TODO: columns == o->columns &&
           bIfNotExist == o->bIfNotExist;
  } else {
    return false;
  }
}

void CreateTable::run(const SqlContext *sqlCtx) const {
  std::shared_ptr<ResolvedIdentifier> identifier =
      std::dynamic_pointer_cast<ResolvedIdentifier>(name());
  if (identifier) {
    if (!sqlCtx->catalogManager->catalog(identifier->catalogName)
             ->tableExists(identifier->databaseName(),
                           identifier->tableName())) {
      Table newTable;
      newTable.name = identifier->tableName();
      newTable.catalog = identifier->catalogName;
      newTable.database = {identifier->nameParts.begin(),
                           identifier->nameParts.end() - 1};
      newTable.schema = columns; // Assuming columns is a vector of Column
      sqlCtx->catalogManager->catalog(identifier->catalogName)
          ->createTable(newTable);
    } else if (!bIfNotExist) {
      throw std::runtime_error("Table already exists: " +
                               identifier->fullName());
    }
  } else {
    throw std::runtime_error(
        "Cannot run create table on unresolved table name.");
  }
}

std::shared_ptr<Identifier> CreateTable::name() const {
  return std::dynamic_pointer_cast<Identifier>(children[0]);
}

bool AddColumns::nodeEquals(const TreeNode &other) const {
  const AddColumns *o = dynamic_cast<const AddColumns *>(&other);
  if (o) {
    return *(tableName()) == *(o->tableName()) &&
           columnsToAdd == o->columnsToAdd;
  } else {
    return false;
  }
}

void AddColumns::run(const SqlContext *sqlCtx) const {
  std::shared_ptr<ResolvedIdentifier> identifier =
      std::dynamic_pointer_cast<ResolvedIdentifier>(tableName());
  if (identifier) {
    auto catalog = sqlCtx->catalogManager->catalog(identifier->catalogName);
    auto existingTable =
        catalog->getTable(identifier->databaseName(), identifier->tableName());
    auto existingSchema = existingTable->schema;
    existingSchema.insert(existingSchema.end(), columnsToAdd.begin(),
                          columnsToAdd.end());
    sqlCtx->catalogManager->catalog(identifier->catalogName)
        ->updateTable(
            identifier->databaseName(), identifier->tableName(),
            TableUpdate{TableUpdatePrerequisite{},
                        TableUpdateSetSchema{.schema = existingSchema}});
  } else {
    throw std::runtime_error(
        "Cannot run add columns on unresolved table name.");
  }
}

std::shared_ptr<Identifier> AddColumns::tableName() const {
  return std::dynamic_pointer_cast<Identifier>(children[0]);
}

bool Query::nodeEquals(const TreeNode &other) const {
  const Query *o = dynamic_cast<const Query *>(&other);
  if (o) {
    return queryName == o->queryName;
  } else {
    return false;
  }
}

bool InlineTable::nodeEquals(const TreeNode &other) const {
  const InlineTable *o = dynamic_cast<const InlineTable *>(&other);
  if (o) {
    // TODO: not pointer equality, but value equality
    return rows == o->rows;
  } else {
    return false;
  }
}

InsertInto::InsertInto() {
  children.resize(2);
  // The first child is the table name, the second child is the query
  // i.e. query could be a "VALUES" clause or a "SELECT" statement
  children[0] = std::make_shared<Identifier>();
  children[1] = std::make_shared<Query>();
}

bool InsertInto::nodeEquals(const TreeNode &other) const {
  const InsertInto *o = dynamic_cast<const InsertInto *>(&other);
  if (o) {
    // TODO: compare query with nodeEquals or equality operator?
    return *(tableName()) == *(o->tableName()) && *(query()) == *(o->query());
  } else {
    return false;
  }
}

void InsertInto::run(const SqlContext *sqlCtx) const {
  std::shared_ptr<ResolvedIdentifier> identifier =
      std::dynamic_pointer_cast<ResolvedIdentifier>(tableName());
  if (identifier) {
    if (sqlCtx->catalogManager->catalog(identifier->catalogName)
            ->tableExists(identifier->databaseName(),
                          identifier->tableName())) {
      // TODO: Implement the logic to insert data into the table
    } else {
      throw std::runtime_error("Table does not exist: " +
                               identifier->fullName());
    }
  } else {
    throw std::runtime_error(
        "Cannot run insert into on unresolved table name.");
  }
}

std::shared_ptr<Identifier> InsertInto::tableName() const {
  return std::dynamic_pointer_cast<Identifier>(children[0]);
}

void InsertInto::setTableName(std::shared_ptr<Identifier> tableName) {
  if (tableName) {
    children[0] = tableName;
  } else {
    throw std::invalid_argument("Table name cannot be null");
  }
}

std::shared_ptr<Query> InsertInto::query() const {
  return std::dynamic_pointer_cast<Query>(children[1]);
}

void InsertInto::setQuery(std::shared_ptr<Query> query) {
  if (query) {
    children[1] = query;
  } else {
    throw std::invalid_argument("Query cannot be null");
  }
}
