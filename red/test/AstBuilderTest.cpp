#include "AstBuilder.h"
#include "SqlBaseLexer.h"
#include "SqlBaseParser.h"
#include <ctime>
#include <gtest/gtest.h>

using namespace sqlgrammar;
using namespace antlr4;

TEST(AstBuilderTest, CreateTableStatement) {
  ANTLRInputStream input("CREATE TABLE my_tbl1 (id INT, data STRING)");
  SqlBaseLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  SqlBaseParser parser(&tokens);
  auto parsed = parser.compoundOrSingleStatement();
  std::shared_ptr<CreateTable> plan =
      std::any_cast<std::shared_ptr<CreateTable>>(
          AstBuilder().visitCompoundOrSingleStatement(parsed));

  ASSERT_EQ(plan->name()->nameParts.size(), 1);
  ASSERT_EQ(plan->name()->nameParts[0], "my_tbl1");
  ASSERT_EQ(plan->columns.size(), 2);
  ASSERT_EQ(plan->columns[0].name, "id");
  ASSERT_EQ(plan->columns[0].dataType, "INT");
  ASSERT_EQ(plan->columns[1].name, "data");
  ASSERT_EQ(plan->columns[1].dataType, "STRING");
  ASSERT_FALSE(plan->bIfNotExist);
}

TEST(AstBuilderTest, CreateTableIfNotExistStatement) {
  ANTLRInputStream input(
      "CREATE TABLE IF NOT EXISTS my_tbl1 (id INT, data STRING)");
  SqlBaseLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  SqlBaseParser parser(&tokens);
  auto parsed = parser.compoundOrSingleStatement();
  std::shared_ptr<CreateTable> plan =
      std::any_cast<std::shared_ptr<CreateTable>>(
          AstBuilder().visitCompoundOrSingleStatement(parsed));

  ASSERT_EQ(plan->name()->nameParts.size(), 1);
  ASSERT_EQ(plan->name()->nameParts[0], "my_tbl1");
  ASSERT_EQ(plan->columns.size(), 2);
  ASSERT_EQ(plan->columns[0].name, "id");
  ASSERT_EQ(plan->columns[0].dataType, "INT");
  ASSERT_EQ(plan->columns[1].name, "data");
  ASSERT_EQ(plan->columns[1].dataType, "STRING");
  ASSERT_TRUE(plan->bIfNotExist);
}

TEST(AstBuilderTest, AlterTableAddColumns) {
  ANTLRInputStream input(
      "ALTER TABLE my_tbl1 ADD COLUMNS (event_time TIMESTAMP)");
  SqlBaseLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  SqlBaseParser parser(&tokens);
  auto parsed = parser.compoundOrSingleStatement();
  std::shared_ptr<AddColumns> plan = std::any_cast<std::shared_ptr<AddColumns>>(
      AstBuilder().visitCompoundOrSingleStatement(parsed));

  ASSERT_EQ(plan->tableName()->nameParts.size(), 1);
  ASSERT_EQ(plan->tableName()->nameParts[0], "my_tbl1");
  ASSERT_EQ(plan->columnsToAdd.size(), 1);
  ASSERT_EQ(plan->columnsToAdd[0].name, "event_time");
  ASSERT_EQ(plan->columnsToAdd[0].dataType, "TIMESTAMP");
  ASSERT_TRUE(plan->columnsToAdd[0].bNullable);
  ASSERT_TRUE(plan->columnsToAdd[0].comment.empty());
  ASSERT_TRUE(plan->columnsToAdd[0].defaultExpr.empty());
}

TEST(AstBuilderTest, AlterTableAddColumnsWithCommentInSingleQuote) {
  ANTLRInputStream input("ALTER TABLE my_tbl1 ADD COLUMNS (event_time "
                         "TIMESTAMP COMMENT 'Event time')");
  SqlBaseLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  SqlBaseParser parser(&tokens);
  auto parsed = parser.compoundOrSingleStatement();
  std::shared_ptr<AddColumns> plan = std::any_cast<std::shared_ptr<AddColumns>>(
      AstBuilder().visitCompoundOrSingleStatement(parsed));

  ASSERT_EQ(plan->tableName()->nameParts.size(), 1);
  ASSERT_EQ(plan->tableName()->nameParts[0], "my_tbl1");
  ASSERT_EQ(plan->columnsToAdd.size(), 1);
  ASSERT_EQ(plan->columnsToAdd[0].name, "event_time");
  ASSERT_EQ(plan->columnsToAdd[0].dataType, "TIMESTAMP");
  ASSERT_TRUE(plan->columnsToAdd[0].bNullable);
  ASSERT_EQ("Event time", plan->columnsToAdd[0].comment);
  ASSERT_TRUE(plan->columnsToAdd[0].defaultExpr.empty());
}

TEST(AstBuilderTest, AlterTableAddColumnsWithCommentInDoubleQuote) {
  ANTLRInputStream input("ALTER TABLE my_tbl1 ADD COLUMNS (event_time "
                         "TIMESTAMP COMMENT \"Event time\")");
  SqlBaseLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  SqlBaseParser parser(&tokens);
  auto parsed = parser.compoundOrSingleStatement();
  std::shared_ptr<AddColumns> plan = std::any_cast<std::shared_ptr<AddColumns>>(
      AstBuilder().visitCompoundOrSingleStatement(parsed));

  ASSERT_EQ(plan->tableName()->nameParts.size(), 1);
  ASSERT_EQ(plan->tableName()->nameParts[0], "my_tbl1");
  ASSERT_EQ(plan->columnsToAdd.size(), 1);
  ASSERT_EQ(plan->columnsToAdd[0].name, "event_time");
  ASSERT_EQ(plan->columnsToAdd[0].dataType, "TIMESTAMP");
  ASSERT_TRUE(plan->columnsToAdd[0].bNullable);
  ASSERT_EQ("Event time", plan->columnsToAdd[0].comment);
  ASSERT_TRUE(plan->columnsToAdd[0].defaultExpr.empty());
}

TEST(AstBuilderTest, AlterTableAddColumnsWithNOTNULL) {
  ANTLRInputStream input("ALTER TABLE my_tbl1 ADD COLUMNS (event_time "
                         "TIMESTAMP NOT NULL)");
  SqlBaseLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  SqlBaseParser parser(&tokens);
  auto parsed = parser.compoundOrSingleStatement();
  std::shared_ptr<AddColumns> plan = std::any_cast<std::shared_ptr<AddColumns>>(
      AstBuilder().visitCompoundOrSingleStatement(parsed));

  ASSERT_EQ(plan->tableName()->nameParts.size(), 1);
  ASSERT_EQ(plan->tableName()->nameParts[0], "my_tbl1");
  ASSERT_EQ(plan->columnsToAdd.size(), 1);
  ASSERT_EQ(plan->columnsToAdd[0].name, "event_time");
  ASSERT_EQ(plan->columnsToAdd[0].dataType, "TIMESTAMP");
  ASSERT_FALSE(plan->columnsToAdd[0].bNullable);
  ASSERT_TRUE(plan->columnsToAdd[0].comment.empty());
  ASSERT_TRUE(plan->columnsToAdd[0].defaultExpr.empty());
}

TEST(AstBuilderTest, AlterTableAddColumnsWithDefaultExpr) {
  ANTLRInputStream input("ALTER TABLE my_tbl1 ADD COLUMNS (event_time "
                         "TIMESTAMP DEFAULT current_timestamp())");
  SqlBaseLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  SqlBaseParser parser(&tokens);
  auto parsed = parser.compoundOrSingleStatement();
  std::shared_ptr<AddColumns> plan = std::any_cast<std::shared_ptr<AddColumns>>(
      AstBuilder().visitCompoundOrSingleStatement(parsed));

  ASSERT_EQ(plan->tableName()->nameParts.size(), 1);
  ASSERT_EQ(plan->tableName()->nameParts[0], "my_tbl1");
  ASSERT_EQ(plan->columnsToAdd.size(), 1);
  ASSERT_EQ(plan->columnsToAdd[0].name, "event_time");
  ASSERT_EQ(plan->columnsToAdd[0].dataType, "TIMESTAMP");
  ASSERT_TRUE(plan->columnsToAdd[0].bNullable);
  ASSERT_TRUE(plan->columnsToAdd[0].comment.empty());
  ASSERT_EQ("current_timestamp", plan->columnsToAdd[0].defaultExpr);
}

TEST(AstBuilderTest, AlterTableAddColumnsWithAllDescriptors) {
  ANTLRInputStream input(
      "ALTER TABLE my_tbl1 ADD COLUMNS (event_time "
      "TIMESTAMP NOT NULL COMMENT 'Event time' DEFAULT current_timestamp())");
  SqlBaseLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  SqlBaseParser parser(&tokens);
  auto parsed = parser.compoundOrSingleStatement();
  std::shared_ptr<AddColumns> plan = std::any_cast<std::shared_ptr<AddColumns>>(
      AstBuilder().visitCompoundOrSingleStatement(parsed));

  ASSERT_EQ(plan->tableName()->nameParts.size(), 1);
  ASSERT_EQ(plan->tableName()->nameParts[0], "my_tbl1");
  ASSERT_EQ(plan->columnsToAdd.size(), 1);
  ASSERT_EQ(plan->columnsToAdd[0].name, "event_time");
  ASSERT_EQ(plan->columnsToAdd[0].dataType, "TIMESTAMP");
  ASSERT_FALSE(plan->columnsToAdd[0].bNullable);
  ASSERT_EQ("Event time", plan->columnsToAdd[0].comment);
  ASSERT_EQ("current_timestamp", plan->columnsToAdd[0].defaultExpr);
}

std::time_t stringToTime(const char *timeString) {
  struct std::tm tm {};

  if (strptime(timeString, "%Y-%m-%d %H:%M:%S", &tm) == nullptr) {
    std::cerr << "Failed to parse time string." << std::endl;
    return (std::time_t)-1; // Return error value
  }

  std::time_t time = mktime(&tm);
  if (time == (std::time_t)-1) {
    std::cerr << "Failed to convert to time_t." << std::endl;
  }
  return time;
}

TEST(AstBuilderTest, InsertIntoWithValues) {
  ANTLRInputStream input("INSERT INTO my_tbl1 VALUES (1, 'data1', "
                         "TIMESTAMP '2023-10-01 12:00:00')");
  SqlBaseLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  SqlBaseParser parser(&tokens);
  auto parsed = parser.compoundOrSingleStatement();
  std::shared_ptr<InsertInto> plan = std::any_cast<std::shared_ptr<InsertInto>>(
      AstBuilder().visitCompoundOrSingleStatement(parsed));

  ASSERT_EQ(plan->tableName()->nameParts.size(), 1);
  ASSERT_EQ(plan->tableName()->nameParts[0], "my_tbl1");
  auto query = std::dynamic_pointer_cast<InlineTable>(plan->query());
  ASSERT_EQ(query->rows.size(), 1);
  std::vector<std::variant<int, long long, std::string, std::time_t>>
      expectedCols{1, "data1", stringToTime("2023-10-01 12:00:00")};
  ASSERT_EQ(expectedCols, query->rows[0]->values);
}
