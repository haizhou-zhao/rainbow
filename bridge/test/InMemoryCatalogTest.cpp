#include "InMemoryCatalog.h" // Include your actual header
#include "gtest/gtest.h"
#include <stdexcept>

TEST(InMemoryCatalogTest, TableDoesNotExistInitially) {
  InMemoryCatalog catalog;
  EXPECT_FALSE(catalog.tableExists("default", "users"));
}

TEST(InMemoryCatalogTest, CreateAndCheckTableInDefaultDatabase) {
  InMemoryCatalog catalog;
  catalog.createTable("default", "users");

  EXPECT_TRUE(catalog.tableExists("default", "users"));
}

TEST(InMemoryCatalogTest, CreateAndCheckTableInNamedDatabase) {
  InMemoryCatalog catalog;
  catalog.createTable("analytics", "events");

  EXPECT_TRUE(catalog.tableExists("analytics", "events"));
  EXPECT_FALSE(catalog.tableExists("default", "events"));
}

TEST(InMemoryCatalogTest, TableDoesNotExist) {
  InMemoryCatalog catalog;
  EXPECT_FALSE(catalog.tableExists("my_db", "nonexistent"));
  EXPECT_FALSE(catalog.tableExists("sales", "orders"));
}

TEST(InMemoryCatalogTest, DuplicateCreateTableHasNoEffect) {
  InMemoryCatalog catalog;
  catalog.createTable("default", "users");
  catalog.createTable("default", "users"); // Duplicate

  EXPECT_TRUE(catalog.tableExists("default", "users"));
}

TEST(InMemoryCatalogTest, EmptyDatabaseNameThrowsInCreateTable) {
  InMemoryCatalog catalog;
  EXPECT_THROW(catalog.createTable("", "users"), std::runtime_error);
}

TEST(InMemoryCatalogTest, EmptyDatabaseNameThrowsInTableExists) {
  InMemoryCatalog catalog;
  EXPECT_THROW(catalog.tableExists("", "users"), std::runtime_error);
}
