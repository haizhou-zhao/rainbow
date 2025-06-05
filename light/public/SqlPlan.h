#pragma once

#include "TreeNode.h"
#include <memory>
#include <numeric>
#include <string>
#include <vector>

struct SqlContext; // Forward declaration

struct DataType {
  std::string typeName;
};

struct ColumnDef {
  std::string name;
  DataType dataType;
  bool bNullable = true; // default is nullable, unless specified as NOT NULL
  std::string comment;
  std::string defaultExpr;
  std::size_t position;
  // std::string generationExpression;
  // IdentityColumnSpec identityColumnSpec;
  // Metadata metadata;

  bool operator==(const ColumnDef &other) const {
    return name == other.name && dataType.typeName == other.dataType.typeName &&
           bNullable == other.bNullable && comment == other.comment &&
           defaultExpr == other.defaultExpr && position == other.position;
  }
};

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
  std::vector<ColumnDef> columns;
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
  std::vector<ColumnDef> columnsToAdd;

  AddColumns() { children.push_back(std::make_shared<Identifier>()); }
  bool nodeEquals(const TreeNode &other) const override;
  void run() const;
  std::shared_ptr<Identifier> tableName() const;
};
