#include "SqlPlan.h"

bool UnresolvedIdentifier::nodeEquals(const TreeNode& other) const {
    const UnresolvedIdentifier* o = dynamic_cast<const UnresolvedIdentifier*>(&other);
    if (o) {
        return nameParts == o->nameParts;
    } else {
        return false;
    }
}

bool CreateTable::nodeEquals(const TreeNode& other) const {
    const CreateTable* o = dynamic_cast<const CreateTable*>(&other);
    if (o) {
        return *name == *(o->name) &&
            // TODO: columns == o->columns &&
            bIfNotExist == o->bIfNotExist;

    } else {
        return false;
    }
}
