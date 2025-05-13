#pragma once

#include <memory>
#include <string>
#include <vector>
#include "TreeNode.h"

struct DataType
{
    std::string typeName;
};

struct ColumnDef
{
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
struct Identifier : public TreeNode
{
    std::vector<std::string> nameParts;

    bool nodeEquals(const TreeNode& other) const override;
};

struct ResolvedIdentifier : public Identifier
{
    std::string catalogName;

    bool nodeEquals(const TreeNode& other) const override;
};

struct CreateTable : public TreeNode
{
    std::shared_ptr<Identifier> name;
    std::vector<ColumnDef> columns;
    // std::vector<Transform> partitioning;
    // TableSpec tableSpec;
    bool bIfNotExist;

    CreateTable() : name(new Identifier()) {
        children.push_back(name);
    }

    bool nodeEquals(const TreeNode& other) const override;
};
