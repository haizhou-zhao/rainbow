#pragma once

#include "DbEntities.h"
#include "TreeNode.h"
#include <memory>
#include <numeric>
#include <string>
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
