#pragma once

#include "DbEntities.h"
#include "TreeNode.h"
#include <ctime>
#include <memory>
#include <numeric>
#include <string>
#include <variant>
#include <vector>

struct SqlContext; // Forward declaration

/**
 * Represents an (unresolved) identifier, but derivable
 */
struct Identifier : public TreeNode {
  std::vector<std::string> nameParts;

  bool nodeEquals(const TreeNode &other) const override;
};

struct ResolvedIdentifier : public Identifier {
  std::string catalogName;

  bool nodeEquals(const TreeNode &other) const override;

  std::string fullName() const {
    return std::accumulate(nameParts.begin(), nameParts.end(), catalogName,
                           [](const std::string &a, const std::string &b) {
                             return a.empty() ? b : a + "." + b;
                           });
  }

  std::string databaseName() const {
    std::string db;
    if (nameParts.size() > 1) {
      db = std::accumulate(nameParts.begin(), nameParts.end() - 1, db,
                           [](const std::string &a, const std::string &b) {
                             return a.empty() ? b : a + "." + b;
                           });
    }
    return db;
  }

  std::string tableName() const {
    if (nameParts.size() > 0) {
      return nameParts.back();
    }
    return "";
  }
};

/**
 * CREATE TABLE ...
 */
struct CreateTable : public TreeNode {
  std::vector<Column> columns;
  // std::vector<Transform> partitioning;
  // TableSpec tableSpec;
  bool bIfNotExist;

  CreateTable() { children.push_back(std::make_shared<Identifier>()); }

  bool nodeEquals(const TreeNode &other) const override;

  void run(const SqlContext *sqlCtx) const;

  std::shared_ptr<Identifier> name() const;
};

/**
 * ALTER TABLE ... ADD COLUMNS
 */
struct AddColumns : public TreeNode {
  std::vector<Column> columnsToAdd;

  AddColumns() { children.push_back(std::make_shared<Identifier>()); }
  bool nodeEquals(const TreeNode &other) const override;
  void run(const SqlContext *sqlCtx) const;
  std::shared_ptr<Identifier> tableName() const;
};

struct Query : public TreeNode {
  std::string queryName;

  // This is a placeholder for a query plan, which can be a SELECT, INSERT, etc.
  // In a real implementation, this would contain more details about the query.
  Query() {}
  Query(const std::string &name) : queryName(name) {}

  bool nodeEquals(const TreeNode &other) const;
};

struct Row {
  std::vector<std::variant<int, long long, std::string, std::time_t>> values;
};

struct InlineTable : public Query {
  std::vector<std::shared_ptr<Row>> rows;

  InlineTable() : Query("InlineTable") {}

  bool nodeEquals(const TreeNode &other) const override;
};

struct FunctionCall {
  std::string functionName;

  FunctionCall(const std::string &name) : functionName(name) {}
};

struct InsertInto : public TreeNode {
  InsertInto();

  bool nodeEquals(const TreeNode &other) const override;
  void run(const SqlContext *sqlCtx) const;
  std::shared_ptr<Identifier> tableName() const;
  void setTableName(std::shared_ptr<Identifier> tableName);
  std::shared_ptr<Query> query() const;
  void setQuery(std::shared_ptr<Query> query);
};
