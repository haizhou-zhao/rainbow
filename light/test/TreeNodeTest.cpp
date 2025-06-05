#include "TreeNode.h"
#include "Rule.h"
#include "RuleExecResult.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class MockRule : public Rule {
public:
  // Constructor must forward name to base class
  explicit MockRule(const std::string &name = "MockRule") : Rule(name) {}

  // Mock the pure virtual method
  MOCK_METHOD(void, init, (SqlContext * sqlCtx), (override));
  MOCK_METHOD(RuleExecResult, apply, (std::shared_ptr<TreeNode> plan),
              (const, override));
};

TEST(TreeNodeTest, ResolveRulesDownWithNoPruning_ModifiesSelfAndChildren) {
  MockRule rule;
  auto root = std::make_shared<TreeNode>();
  auto child = std::make_shared<TreeNode>();
  root->children.push_back(child);
  child->parent = root;
  auto newRoot = std::make_shared<TreeNode>();
  auto newChild = std::make_shared<TreeNode>();

  // Setup expectation
  EXPECT_CALL(rule, apply(root))
      .WillOnce(::testing::Return(RuleExecResult(newRoot, true)));
  EXPECT_CALL(rule, apply(child))
      .WillOnce(::testing::Return(RuleExecResult(newChild, true)));

  auto result = root->resolveRulesDownWithPruning(
      [](const TreeNode *) { return false; }, // no pruning
      &rule);

  EXPECT_TRUE(result.bModified);
  EXPECT_EQ(result.afterRule, newRoot);
  EXPECT_EQ(newRoot->children.size(), 1);
  EXPECT_EQ(newRoot->children[0], newChild);
  EXPECT_EQ(newChild->parent, newRoot);
}

TEST(TreeNodeTest, ResolveRulesDownWithPruning_NoEffectOnChildren) {
  auto root = std::make_shared<TreeNode>();
  auto child = std::make_shared<TreeNode>();
  root->children.push_back(child);
  child->parent = root;
  auto newRoot = std::make_shared<TreeNode>();

  // The rule is effective on the root but not on the child
  MockRule rule;
  EXPECT_CALL(rule, apply(root))
      .WillOnce(::testing::Return(RuleExecResult(newRoot, true)));
  EXPECT_CALL(rule, apply(child))
      .WillOnce(::testing::Return(RuleExecResult(child, false)));

  auto result = root->resolveRulesDownWithPruning(
      [](const TreeNode *) { return false; }, // no pruning
      &rule);

  EXPECT_TRUE(result.bModified);
  EXPECT_EQ(result.afterRule, newRoot);
  EXPECT_EQ(newRoot->children.size(), 1);
  EXPECT_EQ(newRoot->children[0], child);
  EXPECT_EQ(child->parent, newRoot);
}

TEST(TreeNodeTest, ResolveRulesDownWithPruning_NoEffectOnParent) {
  auto root = std::make_shared<TreeNode>();
  auto child = std::make_shared<TreeNode>();
  root->children.push_back(child);
  child->parent = root;
  auto newChild = std::make_shared<TreeNode>();

  // The rule is effective on the root but not on the child
  MockRule rule;
  EXPECT_CALL(rule, apply(root))
      .WillOnce(::testing::Return(RuleExecResult(root, false)));
  EXPECT_CALL(rule, apply(child))
      .WillOnce(::testing::Return(RuleExecResult(newChild, true)));

  auto result = root->resolveRulesDownWithPruning(
      [](const TreeNode *) { return false; }, // no pruning
      &rule);

  EXPECT_TRUE(result.bModified);
  EXPECT_EQ(result.afterRule, root);
  EXPECT_EQ(root->children.size(), 1);
  EXPECT_EQ(root->children[0], newChild);
  EXPECT_EQ(newChild->parent, root);
}

TEST(TreeNodeTest, ResolveRulesDown_Ineffective) {
  auto root = std::make_shared<TreeNode>();
  auto child = std::make_shared<TreeNode>();
  root->children.push_back(child);
  child->parent = root;

  MockRule rule;
  EXPECT_CALL(rule, apply(root))
      .WillOnce(::testing::Return(RuleExecResult(root, false)));
  EXPECT_CALL(rule, apply(child))
      .WillOnce(::testing::Return(RuleExecResult(child, false)));
  auto result = root->resolveRulesDownWithPruning(
      [](const TreeNode *) { return false; }, &rule);

  EXPECT_FALSE(result.bModified);
  EXPECT_EQ(result.afterRule, root);
  EXPECT_EQ(root->children.size(), 1);
  EXPECT_EQ(root->children[0], child);
  EXPECT_EQ(child->parent, root);
}
