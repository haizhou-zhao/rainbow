#include "Rule.h"
#include "SqlPlan.h"
#include "TreeNode.h"

bool ResolveCatalogs::apply(TreeNode* plan) const
{
    CreateTable* createTablePlan = dynamic_cast<CreateTable*>(plan);
    // TODO: this is dummy resolver
    if (createTablePlan) {
        return true;
    } else {
        return false;
    }
}
