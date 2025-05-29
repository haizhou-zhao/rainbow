#include "SqlPlan.h"

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

void CreateTable::run() const {}

std::shared_ptr<Identifier> CreateTable::name() const {
  return std::dynamic_pointer_cast<Identifier>(children[0]);
}
