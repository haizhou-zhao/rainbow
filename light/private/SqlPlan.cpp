#include "SqlPlan.h"
#include "Catalog.h"
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
      sqlCtx->catalogManager->catalog(identifier->catalogName)
          ->createTable(identifier->databaseName(), identifier->tableName());
    } else if (!bIfNotExist) {
      throw std::runtime_error("Table already exists: " +
                               identifier->fullName());
    }
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

void AddColumns::run() const {}

std::shared_ptr<Identifier> AddColumns::tableName() const {
  return std::dynamic_pointer_cast<Identifier>(children[0]);
}
