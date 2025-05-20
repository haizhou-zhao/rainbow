#pragma once
#include <memory>

class TreeNode;

struct RuleExecResult {
  std::shared_ptr<TreeNode> afterRule;
  bool bChanged;

  RuleExecResult(std::shared_ptr<TreeNode> _afterRule, bool _bChanged)
      : afterRule(_afterRule), bChanged(_bChanged) {}
};
