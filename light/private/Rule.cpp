#include "Rule.h"

#include <algorithm>
#include "SqlPlan.h"
#include "TreeNode.h"

RuleExecResult ResolveCatalogs::apply(std::shared_ptr<TreeNode> plan) const
{
    std::shared_ptr<Identifier> identifier = std::dynamic_pointer_cast<Identifier>(plan);
    if (identifier) {
        std::shared_ptr<ResolvedIdentifier> resolved = std::dynamic_pointer_cast<ResolvedIdentifier>(plan);
        if (resolved) {
            return RuleExecResult(resolved, false);
        } else {
            size_t numParts = identifier->nameParts.size();
            if (numParts == 1) {
                resolved = std::make_shared<ResolvedIdentifier>();
                resolved->catalogName = "default";
                std::swap(resolved->nameParts, identifier->nameParts);
                return RuleExecResult(resolved, true);
            } else {
                // TODO: resolve other than default catalog
                return RuleExecResult(identifier, false);
            }
        }
    } else {
        return RuleExecResult(plan, false);
    }
}
