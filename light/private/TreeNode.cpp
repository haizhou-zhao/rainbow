#include "TreeNode.h"
#include "Rule.h"

bool TreeNode::isEffective(const Rule *rule) const {
  return ineffectiveRuleNames.find(rule->name()) == ineffectiveRuleNames.end();
}

void TreeNode::markIneffective(const Rule *rule) {
  ineffectiveRuleNames.insert(rule->name());
}

bool TreeNode::nodeEquals(const TreeNode &other) const {
  return this == &other;
}

bool TreeNode::operator==(const TreeNode &other) const {
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
    return nodeEquals(other);
  }
}

RuleExecResult TreeNode::resolveRulesDownWithPruning(
    std::function<bool(const TreeNode *)> shouldPrune, const Rule *rule) {
  bool changed = false;
  std::shared_ptr<TreeNode> currentNode = shared_from_this();
  std::shared_ptr<TreeNode> resolvedNode;
  if (!bAnalyzed && !shouldPrune(this) && isEffective(rule)) {
    auto result = rule->apply(currentNode);
    resolvedNode = result.afterRule;
    if (result.bModified) {
      resolvedNode->children = children;
    }
    changed = result.bModified;
    for (auto i = resolvedNode->children.begin();
         i != resolvedNode->children.end(); ++i) {
      auto childResult = (*i)->resolveRulesDownWithPruning(shouldPrune, rule);
      childResult.afterRule->parent = resolvedNode;
      (*i) = childResult.afterRule;
      if (!changed)
        changed = childResult.bModified;
    }
  } else {
    resolvedNode = currentNode;
  }
  if (!changed) {
    markIneffective(rule);
  }
  return RuleExecResult(resolvedNode, changed);
}
