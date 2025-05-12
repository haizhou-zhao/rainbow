#include "TreeNode.h"
#include "Rule.h"

bool TreeNode::isEffective(const Rule* rule) const {
    return ineffectiveRuleNames.find(rule->name()) == ineffectiveRuleNames.end();
}

void TreeNode::markIneffective(const Rule* rule) {
    ineffectiveRuleNames.insert(rule->name());
}

bool TreeNode::operator==(const TreeNode& other) const {
    if (children.empty() && other.children.empty()) {
        return nodeEquals(other);
    } else if (children.size() != other.children.size()) {
        return false;
    } else {
        for (int i = 0; i < children.size(); ++i) {
            if (children[i] != other.children[i]) {
                return false;
            }
        }
        return true;
    }
}

bool TreeNode::resolveRulesDownWithPruning(
    std::function<bool(const TreeNode*)> shouldPrune,
    const Rule* rule)
{
    bool changed = false;
    if (!bAnalyzed && !shouldPrune(this) && isEffective(rule)) {
        changed = rule->apply(this);
        std::for_each(children.begin(), children.end(), [&](std::shared_ptr<TreeNode> child) {
            bool childChanged = child->resolveRulesDownWithPruning(shouldPrune, rule);
            if (!changed) changed = childChanged;
        });
    }
    if (!changed) {
        markIneffective(rule);
    }
    return changed;
}
