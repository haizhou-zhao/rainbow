#include "SqlPlan.h"
#include "Catalog.h"
#include "InMemoryCatalog.h"
#include "SqlContext.h"
#include <gtest/gtest.h>

TEST(IdentifierTest, NodeEquals_SameParts) {
  Identifier id1;
  id1.nameParts = {"db", "table"};

  Identifier id2;
  id2.nameParts = {"db", "table"};

  EXPECT_TRUE(id1.nodeEquals(id2));
}

TEST(IdentifierTest, NodeEquals_DifferentParts) {
  Identifier id1;
  id1.nameParts = {"db", "table1"};

  Identifier id2;
  id2.nameParts = {"db", "table2"};

  EXPECT_FALSE(id1.nodeEquals(id2));
}

TEST(IdentifierTest, NodeEquals_DifferentType) {
  struct DummyNode : public TreeNode {};

  Identifier id;
  id.nameParts = {"table"};

  DummyNode dummy;

  EXPECT_FALSE(id.nodeEquals(dummy));
}

TEST(ResolvedIdentifierTest, EqualsSameValues) {
  ResolvedIdentifier a;
  a.nameParts = {"db", "table"};
  a.catalogName = "default";

  ResolvedIdentifier b;
  b.nameParts = {"db", "table"};
  b.catalogName = "default";

  EXPECT_TRUE(a.nodeEquals(b));
}

TEST(ResolvedIdentifierTest, NotEqualsDifferentNameParts) {
  ResolvedIdentifier a;
  a.nameParts = {"db", "table1"};
  a.catalogName = "default";

  ResolvedIdentifier b;
  b.nameParts = {"db", "table2"};
  b.catalogName = "default";

  EXPECT_FALSE(a.nodeEquals(b));
}

TEST(ResolvedIdentifierTest, NotEqualsDifferentCatalogName) {
  ResolvedIdentifier a;
  a.nameParts = {"db", "table"};
  a.catalogName = "catalog1";

  ResolvedIdentifier b;
  b.nameParts = {"db", "table"};
  b.catalogName = "catalog2";

  EXPECT_FALSE(a.nodeEquals(b));
}

TEST(ResolvedIdentifierTest, NotEqualsDifferentType) {
  struct DummyNode : public TreeNode {};

  ResolvedIdentifier a;
  a.nameParts = {"db", "table"};
  a.catalogName = "default";

  DummyNode dummy;

  EXPECT_FALSE(a.nodeEquals(dummy));
}

TEST(CreateTableTest, EqualsWithSameFields) {
  CreateTable ct1;
  ct1.name()->nameParts = {"db", "table"};
  ct1.bIfNotExist = true;

  CreateTable ct2;
  ct2.name()->nameParts = {"db", "table"};
  ct2.bIfNotExist = true;

  EXPECT_TRUE(ct1.nodeEquals(ct2));
}

TEST(CreateTableTest, NotEqualsDifferentName) {
  CreateTable ct1;
  ct1.name()->nameParts = {"db", "table1"};
  ct1.bIfNotExist = true;

  CreateTable ct2;
  ct2.name()->nameParts = {"db", "table2"};
  ct2.bIfNotExist = true;

  EXPECT_FALSE(ct1.nodeEquals(ct2));
}

TEST(CreateTableTest, NotEqualsDifferentIfNotExistFlag) {
  CreateTable ct1;
  ct1.name()->nameParts = {"db", "table"};
  ct1.bIfNotExist = true;

  CreateTable ct2;
  ct2.name()->nameParts = {"db", "table"};
  ct2.bIfNotExist = false;

  EXPECT_FALSE(ct1.nodeEquals(ct2));
}

TEST(CreateTableTest, NotEqualsDifferentType) {
  struct DummyNode : public TreeNode {};
  DummyNode dummy;

  CreateTable ct;
  ct.name()->nameParts = {"db", "table"};
  ct.bIfNotExist = false;

  EXPECT_FALSE(ct.nodeEquals(dummy));
}

TEST(CreateTableTest, NameReturnsFirstChildAsIdentifier) {
  CreateTable createTable;
  std::static_pointer_cast<Identifier>(createTable.children[0])->nameParts = {
      "my_table"};

  std::shared_ptr<Identifier> result = createTable.name();

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->nameParts.size(), 1);
  EXPECT_EQ(result->nameParts[0], "my_table");
}

TEST(CreateTableTest, NameFailsIfChildIsNotIdentifier) {
  struct DummyNode : public TreeNode {};
  auto dummy = std::make_shared<DummyNode>();

  CreateTable createTable;
  createTable.children[0] = dummy;

  std::shared_ptr<Identifier> result = createTable.name();

  ASSERT_EQ(result, nullptr);
}

TEST(CreateTableTest, RunCreatesTableWithResolvedIdentifier) {
  auto createTable = std::make_shared<CreateTable>();
  auto identifier = std::make_shared<ResolvedIdentifier>();
  createTable->children[0] = identifier;
  identifier->nameParts = {"test_db", "users"};
  identifier->catalogName = "catalog1";
  createTable->bIfNotExist = false;
  createTable->columns = {
      {"col1", {"INT"}, true, "comment1", "defaultExpr1", 0},
      {"col2", {"STRING"}, true, "comment2", "defaultExpr2", 1}};

  SqlContext sqlCtx;
  CatalogManager catalogManager;
  sqlCtx.currentCatalogName = "defaultCatalog";
  sqlCtx.currentDatabaseName = {"defaultDatabase"};
  catalogManager.addCatalog("defaultCatalog",
                            std::make_shared<InMemoryCatalog>());
  catalogManager.addCatalog("catalog1", std::make_shared<InMemoryCatalog>());
  sqlCtx.catalogManager = &catalogManager;

  createTable->run(&sqlCtx);

  ASSERT_TRUE(sqlCtx.catalogManager->catalog("catalog1")
                  ->tableExists("test_db", "users"));
}

TEST(CreateTableTest, RunCreatesTableWithUnresolvedIdentifier) {
  auto createTable = std::make_shared<CreateTable>();
  createTable->name()->nameParts = {"test_db", "users"};
  createTable->bIfNotExist = false;
  createTable->columns = {
      {"col1", {"INT"}, true, "comment1", "defaultExpr1", 0},
      {"col2", {"STRING"}, true, "comment2", "defaultExpr2", 1}};

  SqlContext sqlCtx;
  CatalogManager catalogManager;
  sqlCtx.currentCatalogName = "defaultCatalog";
  sqlCtx.currentDatabaseName = {"defaultDatabase"};
  catalogManager.addCatalog("defaultCatalog",
                            std::make_shared<InMemoryCatalog>());
  catalogManager.addCatalog("catalog1", std::make_shared<InMemoryCatalog>());
  sqlCtx.catalogManager = &catalogManager;

  createTable->run(&sqlCtx);

  ASSERT_FALSE(sqlCtx.catalogManager->catalog("catalog1")
                   ->tableExists("test_db", "users"));
}

TEST(CreateTableTest, RunCreatesTableWithAlreadyExistingTable) {
  auto createTable = std::make_shared<CreateTable>();
  auto identifier = std::make_shared<ResolvedIdentifier>();
  createTable->children[0] = identifier;
  identifier->nameParts = {"test_db", "users"};
  identifier->catalogName = "catalog1";
  createTable->bIfNotExist = false;
  createTable->columns = {
      {"col1", {"INT"}, true, "comment1", "defaultExpr1", 0},
      {"col2", {"STRING"}, true, "comment2", "defaultExpr2", 1}};

  SqlContext sqlCtx;
  CatalogManager catalogManager;
  sqlCtx.currentCatalogName = "defaultCatalog";
  sqlCtx.currentDatabaseName = {"defaultDatabase"};
  catalogManager.addCatalog("defaultCatalog",
                            std::make_shared<InMemoryCatalog>());
  catalogManager.addCatalog("catalog1", std::make_shared<InMemoryCatalog>());
  sqlCtx.catalogManager = &catalogManager;
  catalogManager.catalog("catalog1")
      ->createTable("test_db", "users"); // Pre-create the table

  ASSERT_THROW(createTable->run(&sqlCtx), std::runtime_error);
}

TEST(CreateTableTest, RunCreatesTableWithAlreadyExistingTableIfNotExist) {
  auto createTable = std::make_shared<CreateTable>();
  auto identifier = std::make_shared<ResolvedIdentifier>();
  createTable->children[0] = identifier;
  identifier->nameParts = {"test_db", "users"};
  identifier->catalogName = "catalog1";
  createTable->bIfNotExist = true;
  createTable->columns = {
      {"col1", {"INT"}, true, "comment1", "defaultExpr1", 0},
      {"col2", {"STRING"}, true, "comment2", "defaultExpr2", 1}};

  SqlContext sqlCtx;
  CatalogManager catalogManager;
  sqlCtx.currentCatalogName = "defaultCatalog";
  sqlCtx.currentDatabaseName = {"defaultDatabase"};
  catalogManager.addCatalog("defaultCatalog",
                            std::make_shared<InMemoryCatalog>());
  catalogManager.addCatalog("catalog1", std::make_shared<InMemoryCatalog>());
  sqlCtx.catalogManager = &catalogManager;
  catalogManager.catalog("catalog1")
      ->createTable("test_db", "users"); // Pre-create the table

  createTable->run(&sqlCtx);
}

TEST(AddColumnsTest, EqualsWithSameFields) {
  AddColumns ac1;
  ac1.tableName()->nameParts = {"db", "table"};
  ac1.columnsToAdd = {
      {"col1", {"INT"}, true, "comment1", "defaultExpr1", 0},
      {"col2", {"STRING"}, true, "comment2", "defaultExpr2", 1}};

  AddColumns ac2;
  ac2.tableName()->nameParts = {"db", "table"};
  ac2.columnsToAdd = {
      {"col1", {"INT"}, true, "comment1", "defaultExpr1", 0},
      {"col2", {"STRING"}, true, "comment2", "defaultExpr2", 1}};

  EXPECT_TRUE(ac1.nodeEquals(ac2));
}

TEST(AddColumnsTest, NotEqualsDifferentName) {
  AddColumns ac1;
  ac1.tableName()->nameParts = {"db", "table1"};
  ac1.columnsToAdd = {
      {"col1", {"INT"}, true, "comment1", "defaultExpr1", 0},
      {"col2", {"STRING"}, true, "comment2", "defaultExpr2", 1}};

  AddColumns ac2;
  ac2.tableName()->nameParts = {"db", "table2"};
  ac2.columnsToAdd = {
      {"col1", {"INT"}, true, "comment1", "defaultExpr1", 0},
      {"col2", {"STRING"}, true, "comment2", "defaultExpr2", 1}};

  EXPECT_FALSE(ac1.nodeEquals(ac2));
}

TEST(AddColumnsTest, NotEqualsDifferentIfNotExistFlag) {
  AddColumns ac1;
  ac1.tableName()->nameParts = {"db", "table"};
  ac1.columnsToAdd = {
      {"col1", {"INT"}, true, "comment1", "defaultExpr1", 0},
      {"col2", {"STRING"}, true, "comment2", "defaultExpr2", 1}};

  AddColumns ac2;
  ac2.tableName()->nameParts = {"db", "table"};
  ac2.columnsToAdd = {{"col1", {"INT"}, true, "comment1", "defaultExpr1", 0},
                      {"col2", {"LONG"}, true, "comment2", "defaultExpr2", 1}};

  EXPECT_FALSE(ac1.nodeEquals(ac2));
}

TEST(AddColumnsTest, NotEqualsDifferentType) {
  struct DummyNode : public TreeNode {};
  DummyNode dummy;

  AddColumns ac;
  ac.tableName()->nameParts = {"db", "table"};
  ac.columnsToAdd = {{"col1", {"INT"}, true, "comment1", "defaultExpr1", 0},
                     {"col2", {"STRING"}, true, "comment2", "defaultExpr2", 1}};

  EXPECT_FALSE(ac.nodeEquals(dummy));
}

TEST(AddColumnsTest, NameReturnsFirstChildAsIdentifier) {
  AddColumns ac;
  std::static_pointer_cast<Identifier>(ac.children[0])->nameParts = {
      "my_table"};

  std::shared_ptr<Identifier> result = ac.tableName();

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->nameParts.size(), 1);
  EXPECT_EQ(result->nameParts[0], "my_table");
}

TEST(AddColumnsTest, NameFailsIfChildIsNotIdentifier) {
  struct DummyNode : public TreeNode {};
  auto dummy = std::make_shared<DummyNode>();

  AddColumns ac;
  ac.children[0] = dummy;

  std::shared_ptr<Identifier> result = ac.tableName();

  ASSERT_EQ(result, nullptr);
}
