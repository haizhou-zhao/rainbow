#pragma once
#include "Rule.h"
#include "TreeNode.h"
#include <string>
#include <vector>

struct Strategy {
  int maxIterations;
  bool bErrorOnExceed;
};

struct Batch {
  std::string name;
  Strategy strategy;
  std::vector<Rule *> rule;
};
