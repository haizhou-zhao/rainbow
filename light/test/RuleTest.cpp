#include "Rule.h"
#include "SqlPlan.h"
#include <gtest/gtest.h>

TEST(ResolveCatalogsTest, NullPlanReturnsOriginal) {
  ResolveCatalogs resolver;
  std::shared_ptr<TreeNode> node = std::make_shared<TreeNode>();
  RuleExecResult result = resolver.apply(node);
  EXPECT_EQ(result.afterRule, node);
  EXPECT_FALSE(result.bModified);
}

TEST(ResolveCatalogsTest, AlreadyResolvedIdentifier) {
  ResolveCatalogs resolver;
  std::shared_ptr<ResolvedIdentifier> resolved =
      std::make_shared<ResolvedIdentifier>();
  resolved->nameParts = {"table1"};
  RuleExecResult result = resolver.apply(resolved);
  EXPECT_EQ(result.afterRule, resolved);
  EXPECT_FALSE(result.bModified);
}

TEST(ResolveCatalogsTest, SingleNamePartIdentifierGetsDefaultCatalog) {
  ResolveCatalogs resolver;
  std::shared_ptr<Identifier> id = std::make_shared<Identifier>();
  id->nameParts = {"table1"};
  RuleExecResult result = resolver.apply(id);

  auto resolved =
      std::dynamic_pointer_cast<ResolvedIdentifier>(result.afterRule);
  ASSERT_NE(resolved, nullptr);
  EXPECT_EQ(resolved->catalogName, "default");
  EXPECT_EQ(resolved->nameParts.size(), 1);
  EXPECT_EQ(resolved->nameParts[0], "table1");
  EXPECT_TRUE(result.bModified);
}

TEST(ResolveCatalogsTest, MultiNamePartIdentifierReturnsUnmodified) {
  ResolveCatalogs resolver;
  std::shared_ptr<Identifier> id = std::make_shared<Identifier>();
  id->nameParts = {"catalog1", "table1"};
  RuleExecResult result = resolver.apply(id);

  EXPECT_EQ(result.afterRule, id);
  EXPECT_FALSE(result.bModified);
}
