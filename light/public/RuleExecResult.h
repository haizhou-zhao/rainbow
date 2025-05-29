#pragma once
#include <memory>

class TreeNode;

struct RuleExecResult {
  std::shared_ptr<TreeNode> afterRule;
  bool bModified;

  RuleExecResult(std::shared_ptr<TreeNode> _afterRule, bool _bChanged)
      : afterRule(_afterRule), bModified(_bChanged) {}
};
