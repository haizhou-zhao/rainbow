#pragma once
#include "RuleExecResult.h"
#include <memory>
#include <string>

class TreeNode;

class Rule {
protected:
  std::string ruleName;

  Rule(std::string name) : ruleName(name) {}

public:
  // return whether the plan is changed
  // does not change parent or children
  virtual RuleExecResult apply(std::shared_ptr<TreeNode> plan) const = 0;

  std::string name() const { return ruleName; }
};

class ResolveCatalogs : public Rule {
public:
  ResolveCatalogs() : Rule("ResolveCatalogs") {}

  RuleExecResult apply(std::shared_ptr<TreeNode> plan) const override;
};
