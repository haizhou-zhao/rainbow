#pragma once
#include "RuleExecResult.h"
#include <functional>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

class Rule;

class TreeNode : public std::enable_shared_from_this<TreeNode> {
private:
  bool bAnalyzed = false;
  std::unordered_set<std::string> ineffectiveRuleNames;

  bool isEffective(const Rule *rule) const;

  void markIneffective(const Rule *rule);

public:
  std::shared_ptr<TreeNode> parent;
  std::vector<std::shared_ptr<TreeNode>> children;

  virtual bool nodeEquals(const TreeNode &other) const = 0;

  bool operator==(const TreeNode &other) const;

  // return whether the tree rooted at the current node is changed
  RuleExecResult
  resolveRulesDownWithPruning(std::function<bool(const TreeNode *)> shouldPrune,
                              const Rule *rule);
};
