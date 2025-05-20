#pragma once

#include "TreeNode.h"
#include <memory>
#include <string>
#include <vector>

struct DataType {
  std::string typeName;
};

struct ColumnDef {
  std::string name;
  DataType dataType;
  bool bNullable;
  std::string comment;
  // DefaultValueExpression defaultValue;
  // std::string generationExpression;
  // IdentityColumnSpec identityColumnSpec;
  // Metadata metadata;
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
};

struct CreateTable : public TreeNode {
  std::vector<ColumnDef> columns;
  // std::vector<Transform> partitioning;
  // TableSpec tableSpec;
  bool bIfNotExist;

  CreateTable() { children.push_back(std::make_shared<Identifier>()); }

  bool nodeEquals(const TreeNode &other) const override;

  void run() const;

  std::shared_ptr<Identifier> name() const;
};
