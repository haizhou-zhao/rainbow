#pragma once

#include <string>
#include <vector>

struct Identifier
{
    std::vector<std::string> nameParts;
};

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

struct CreateTable
{
    Identifier name;
    std::vector<ColumnDef> columns;
    // std::vector<Transform> partitioning;
    // TableSpec tableSpec;
    bool bIfNotExist;
};
