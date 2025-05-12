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

struct UnresolvedIdentifier : public TreeNode
{
    std::vector<std::string> nameParts;

    bool nodeEquals(const TreeNode& other) const override;
};

struct CreateTable : public TreeNode
{
    std::shared_ptr<UnresolvedIdentifier> name;
    std::vector<ColumnDef> columns;
    // std::vector<Transform> partitioning;
    // TableSpec tableSpec;
    bool bIfNotExist;

    CreateTable() : name(new UnresolvedIdentifier()) {
        children.push_back(name);
    }

    bool nodeEquals(const TreeNode& other) const override;
};
