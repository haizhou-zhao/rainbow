#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <unordered_set>

class Rule;

class TreeNode
{
private:
    bool bAnalyzed;
    std::unordered_set<std::string> ineffectiveRuleNames;

    bool isEffective(const Rule* rule) const;

    void markIneffective(const Rule* rule);

public:
    std::shared_ptr<TreeNode> parent;
    std::vector<std::shared_ptr<TreeNode>> children;
    
    virtual bool nodeEquals(const TreeNode& other) const = 0;

    bool operator==(const TreeNode& other) const;

    // return whether the tree rooted at the current node is changed
    bool resolveRulesDownWithPruning(
        std::function<bool(const TreeNode*)> shouldPrune,
        const Rule* rule);
};
