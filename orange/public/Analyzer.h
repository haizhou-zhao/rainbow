#pragma once
#include "RuleExecutor.h"
#include <vector>

class Analyzer {
private:
  std::vector<Batch> batches;

public:
  Analyzer();
  ~Analyzer();
};
