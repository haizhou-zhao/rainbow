#pragma once
#include <string>
#include <vector>
#include "Rule.h"
#include "TreeNode.h"

struct Strategy
{
    int maxIterations;
    bool bErrorOnExceed;
};


struct Batch
{
    std::string name;
    Strategy strategy;
    std::vector<Rule*> rule;
};
