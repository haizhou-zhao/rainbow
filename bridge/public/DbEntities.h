#pragma once
#include <numeric>
#include <string>
#include <vector>

struct Column {
  std::string name;
  std::string dataType;
  bool bNullable = true; // default is nullable, unless specified as NOT NULL
  std::string comment;
  std::string defaultExpr;
  std::size_t position;
  // std::string generationExpression;
  // IdentityColumnSpec identityColumnSpec;
  // Metadata metadata;

  bool operator==(const Column &other) const {
    return name == other.name && dataType == other.dataType &&
           bNullable == other.bNullable && comment == other.comment &&
           defaultExpr == other.defaultExpr && position == other.position;
  }
};

struct Table {
  std::string name;
  std::string catalog;
  std::vector<std::string> database;
  std::vector<Column> schema;
  std::string description;
  std::string tableType;
  bool isTemporary;

  Table() {}

  Table(const Table &other)
      : name(other.name), catalog(other.catalog), database(other.database),
        schema(other.schema), description(other.description),
        tableType(other.tableType), isTemporary(other.isTemporary) {}

  std::string databaseName() const {
    return std::accumulate(
        database.begin(), database.end(), std::string{},
        [](std::string accumulator, const std::string &current_level) {
          if (!accumulator.empty()) {
            accumulator += ".";
          }
          accumulator += current_level;
          return accumulator;
        });
  }
};

// TODO: Implement prerequisite checks
struct TableUpdatePrerequisite {};

struct TableUpdateSetSchema {
  std::vector<Column> schema;
};

struct TableUpdate {
  TableUpdatePrerequisite prerequisite;
  TableUpdateSetSchema setSchema;
};
