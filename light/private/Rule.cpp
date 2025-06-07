#include "Rule.h"
#include "Catalog.h"
#include "SqlContext.h"
#include "SqlPlan.h"
#include "TreeNode.h"
#include <algorithm>
#include <stdexcept>

void ResolveCatalogs::init(SqlContext *sqlCtx) {
  if (sqlCtx) {
    this->_sqlCtx = sqlCtx;
  } else {
    throw std::runtime_error("SqlContext must be provided to ResolveCatalogs");
  }
}

// start with writing test for this rule
RuleExecResult ResolveCatalogs::apply(std::shared_ptr<TreeNode> plan) const {
  std::shared_ptr<Identifier> identifier =
      std::dynamic_pointer_cast<Identifier>(plan);
  if (identifier) {
    std::shared_ptr<ResolvedIdentifier> resolved =
        std::dynamic_pointer_cast<ResolvedIdentifier>(plan);
    if (resolved) {
      return RuleExecResult(resolved, false);
    } else {
      resolved = std::make_shared<ResolvedIdentifier>();
      switch (identifier->nameParts.size()) {
      case 0:
        throw std::runtime_error(
            "ResolveCatalogs cannot resolve an empty identifier");
        break;
      case 1:
        resolved->catalogName = _sqlCtx->currentCatalogName;
        resolved->nameParts = _sqlCtx->currentDatabaseNameParts;
        resolved->nameParts.push_back(identifier->nameParts[0]);
        break;
      case 2:
        resolved->catalogName = _sqlCtx->currentCatalogName;
        resolved->nameParts = identifier->nameParts;
        break;
      default:
        if (_sqlCtx->catalogManager->catalog(identifier->nameParts.front()) ==
            nullptr) {
          resolved->catalogName = _sqlCtx->currentCatalogName;
          resolved->nameParts = identifier->nameParts;
        } else {
          resolved->catalogName = identifier->nameParts.front();
          resolved->nameParts.insert(resolved->nameParts.end(),
                                     identifier->nameParts.begin() + 1,
                                     identifier->nameParts.end());
        }
        break;
      }
      return RuleExecResult(resolved, true);
    }
  } else {
    return RuleExecResult(plan, false);
  }
}
