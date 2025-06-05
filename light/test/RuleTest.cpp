#include "Rule.h"
#include "Catalog.h"
#include "InMemoryCatalog.h"
#include "SqlContext.h"
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

TEST(ResolveCatalogsTest, OneNamePartIdentifierGetsCurrentCatalogAndDatabase) {
  SqlContext sqlCtx;
  sqlCtx.currentCatalogName = "defaultCatalog";
  sqlCtx.currentDatabaseName = {"defaultDatabase"};
  ResolveCatalogs resolver;
  resolver.init(&sqlCtx);
  std::shared_ptr<Identifier> id = std::make_shared<Identifier>();
  id->nameParts = {"table1"};
  RuleExecResult result = resolver.apply(id);

  auto resolved =
      std::dynamic_pointer_cast<ResolvedIdentifier>(result.afterRule);
  ASSERT_NE(resolved, nullptr);
  EXPECT_EQ(resolved->catalogName, "defaultCatalog");
  EXPECT_EQ(resolved->fullName(), "defaultCatalog.defaultDatabase.table1");
  EXPECT_EQ(resolved->databaseName(), "defaultDatabase");
  EXPECT_EQ(resolved->tableName(), "table1");
  EXPECT_TRUE(result.bModified);
}

TEST(ResolveCatalogsTest, TwoNamePartIdentifierGetsCurrentCatalog) {
  SqlContext sqlCtx;
  sqlCtx.currentCatalogName = "defaultCatalog";
  sqlCtx.currentDatabaseName = {"defaultDatabase"};
  ResolveCatalogs resolver;
  resolver.init(&sqlCtx);
  std::shared_ptr<Identifier> id = std::make_shared<Identifier>();
  id->nameParts = {"database1", "table1"};
  RuleExecResult result = resolver.apply(id);

  auto resolved =
      std::dynamic_pointer_cast<ResolvedIdentifier>(result.afterRule);
  ASSERT_NE(resolved, nullptr);
  EXPECT_EQ(resolved->catalogName, "defaultCatalog");
  EXPECT_EQ(resolved->fullName(), "defaultCatalog.database1.table1");
  EXPECT_EQ(resolved->databaseName(), "database1");
  EXPECT_EQ(resolved->tableName(), "table1");
  EXPECT_TRUE(result.bModified);
}

TEST(ResolveCatalogsTest, MultiNamePartIdentifierWithValidCatalogProvided) {
  SqlContext sqlCtx;
  CatalogManager catalogManager;
  sqlCtx.currentCatalogName = "defaultCatalog";
  sqlCtx.currentDatabaseName = {"defaultDatabase"};
  catalogManager.addCatalog("defaultCatalog",
                            std::make_shared<InMemoryCatalog>());
  catalogManager.addCatalog("catalog1", std::make_shared<InMemoryCatalog>());
  sqlCtx.catalogManager = &catalogManager;
  ResolveCatalogs resolver;
  resolver.init(&sqlCtx);
  std::shared_ptr<Identifier> id = std::make_shared<Identifier>();
  id->nameParts = {"catalog1", "my_org", "my_team", "table1"};
  RuleExecResult result = resolver.apply(id);

  auto resolved =
      std::dynamic_pointer_cast<ResolvedIdentifier>(result.afterRule);
  ASSERT_NE(resolved, nullptr);
  EXPECT_EQ(resolved->catalogName, "catalog1");
  EXPECT_EQ(resolved->fullName(), "catalog1.my_org.my_team.table1");
  EXPECT_EQ(resolved->databaseName(), "my_org.my_team");
  EXPECT_EQ(resolved->tableName(), "table1");
  EXPECT_TRUE(result.bModified);
}

TEST(ResolveCatalogsTest, MultiNamePartIdentifierWithNoCatalogProvided) {
  SqlContext sqlCtx;
  CatalogManager catalogManager;
  sqlCtx.currentCatalogName = "defaultCatalog";
  sqlCtx.currentDatabaseName = {"defaultDatabase"};
  catalogManager.addCatalog("defaultCatalog",
                            std::make_shared<InMemoryCatalog>());
  catalogManager.addCatalog("catalog1", std::make_shared<InMemoryCatalog>());
  sqlCtx.catalogManager = &catalogManager;
  ResolveCatalogs resolver;
  resolver.init(&sqlCtx);
  std::shared_ptr<Identifier> id = std::make_shared<Identifier>();
  id->nameParts = {"my_firm", "my_org", "my_team", "table1"};
  RuleExecResult result = resolver.apply(id);

  auto resolved =
      std::dynamic_pointer_cast<ResolvedIdentifier>(result.afterRule);
  ASSERT_NE(resolved, nullptr);
  EXPECT_EQ(resolved->catalogName, "defaultCatalog");
  EXPECT_EQ(resolved->fullName(),
            "defaultCatalog.my_firm.my_org.my_team.table1");
  EXPECT_EQ(resolved->databaseName(), "my_firm.my_org.my_team");
  EXPECT_EQ(resolved->tableName(), "table1");
  EXPECT_TRUE(result.bModified);
}
