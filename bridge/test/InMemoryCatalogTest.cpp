#include "InMemoryCatalog.h"
#include "DbEntities.h"
#include "gtest/gtest.h"
#include <stdexcept>

TEST(InMemoryCatalogTest, TableDoesNotExistInitially) {
  InMemoryCatalog catalog;
  EXPECT_FALSE(catalog.tableExists("default", "users"));
}
TEST(InMemoryCatalogTest, CreateAndCheckTableInNamedDatabase) {
  InMemoryCatalog catalog;
  Table newTable;
  newTable.name = "events";
  newTable.catalog = "default";
  newTable.database = {"analytics"};
  newTable.schema = {{"id", "INT"}, {"event_time", "TIMESTAMP"}};
  catalog.createTable(newTable);

  EXPECT_TRUE(catalog.tableExists("analytics", "events"));
  EXPECT_FALSE(catalog.tableExists("default", "events"));
}

TEST(InMemoryCatalogTest, TableDoesNotExist) {
  InMemoryCatalog catalog;
  EXPECT_FALSE(catalog.tableExists("my_db", "nonexistent"));
  EXPECT_FALSE(catalog.tableExists("sales", "orders"));
}

TEST(InMemoryCatalogTest, DuplicateCreateTableWillThrow) {
  InMemoryCatalog catalog;
  Table newTable;
  newTable.name = "events";
  newTable.catalog = "default";
  newTable.database = {"analytics"};
  newTable.schema = {{"id", "INT"}, {"event_time", "TIMESTAMP"}};
  catalog.createTable(newTable);
  EXPECT_THROW(catalog.createTable(newTable), std::runtime_error);
  // Attempting to create the same table again should throw an error
  EXPECT_TRUE(catalog.tableExists("analytics", "events"));
}

TEST(InMemoryCatalogTest, EmptyDatabaseNameThrowsInCreateTable) {
  InMemoryCatalog catalog;
  Table newTable;
  newTable.name = "events";
  newTable.catalog = "default";
  newTable.database = {""};
  newTable.schema = {{"id", "INT"}, {"event_time", "TIMESTAMP"}};
  EXPECT_THROW(catalog.createTable(newTable), std::runtime_error);
}

TEST(InMemoryCatalogTest, EmptyTableNameThrowsInCreateTable) {
  InMemoryCatalog catalog;
  Table newTable;
  newTable.name = "";
  newTable.catalog = "default";
  newTable.database = {"analytics"};
  newTable.schema = {{"id", "INT"}, {"event_time", "TIMESTAMP"}};
  EXPECT_THROW(catalog.createTable(newTable), std::runtime_error);
}

TEST(InMemoryCatalogTest, EmptyDatabaseNameThrowsInTableExists) {
  InMemoryCatalog catalog;
  EXPECT_THROW(catalog.tableExists("", "tbl"), std::runtime_error);
}

TEST(InMemoryCatalogTest, EmptyTableNameThrowsInTableExists) {
  InMemoryCatalog catalog;
  EXPECT_THROW(catalog.tableExists("db", ""), std::runtime_error);
}
