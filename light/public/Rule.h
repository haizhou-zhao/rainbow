#pragma once
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
    virtual bool apply(TreeNode* plan) const = 0;

    std::string name() const { return ruleName; }
};

class ResolveCatalogs : public Rule {
public:
    ResolveCatalogs() : Rule("ResolveCatalogs") {}

    bool apply(TreeNode* plan) const override;
};
