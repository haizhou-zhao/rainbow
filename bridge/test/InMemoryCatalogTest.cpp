#include "InMemoryCatalog.h" // Include your actual header
#include "gtest/gtest.h"

TEST(InMemoryCatalogTest, TableDoesNotExistInitially) {
  InMemoryCatalog catalog;
  EXPECT_FALSE(catalog.tableExists("default", "users"));
}

TEST(InMemoryCatalogTest, CreateAndCheckTableInDefaultDatabase) {
  InMemoryCatalog catalog;
  catalog.createTable("", "users");

  EXPECT_TRUE(catalog.tableExists("", "users"));
  EXPECT_TRUE(catalog.tableExists("default", "users"));
}

TEST(InMemoryCatalogTest, CreateAndCheckTableInNamedDatabase) {
  InMemoryCatalog catalog;
  catalog.createTable("analytics", "events");

  EXPECT_TRUE(catalog.tableExists("analytics", "events"));
  EXPECT_FALSE(catalog.tableExists("", "events"));
  EXPECT_FALSE(catalog.tableExists("default", "events"));
}

TEST(InMemoryCatalogTest, TableDoesNotExist) {
  InMemoryCatalog catalog;
  EXPECT_FALSE(catalog.tableExists("", "nonexistent"));
  EXPECT_FALSE(catalog.tableExists("sales", "orders"));
}

TEST(InMemoryCatalogTest, DuplicateCreateTableHasNoEffect) {
  InMemoryCatalog catalog;
  catalog.createTable("default", "users");
  catalog.createTable("default", "users"); // Duplicate

  EXPECT_TRUE(catalog.tableExists("default", "users"));
}
