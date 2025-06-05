#pragma once
#include "RuleExecResult.h"
#include <memory>
#include <string>

class TreeNode;
class SqlContext;

class Rule {
protected:
  std::string ruleName;

  Rule(std::string name) : ruleName(name) {}

public:
  /// @brief Apply the rule to the given plan. The plan may be modified in
  /// place.
  /// @param plan
  /// @return RuleExecResult containing the modified plan and a boolean
  /// indicating whether the plan was modified. The rule may return a new plan
  /// if it cannot modify the original plan in place. If the rule does not
  /// apply, it should return the original plan with bModified set to false.
  virtual RuleExecResult apply(std::shared_ptr<TreeNode> plan) const = 0;

  virtual void init(SqlContext *sqlCtx) = 0;

  std::string name() const { return ruleName; }
};

class ResolveCatalogs : public Rule {
private:
  SqlContext *_sqlCtx = nullptr;

public:
  ResolveCatalogs() : Rule("ResolveCatalogs") {}

  void init(SqlContext *sqlCtx) override;

  RuleExecResult apply(std::shared_ptr<TreeNode> plan) const override;
};
