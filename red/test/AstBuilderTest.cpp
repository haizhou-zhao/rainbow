#include "AstBuilder.h"
#include "SqlBaseLexer.h"
#include "SqlBaseParser.h"
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
  ASSERT_EQ(plan->columns[0].dataType.typeName, "INT");
  ASSERT_EQ(plan->columns[1].name, "data");
  ASSERT_EQ(plan->columns[1].dataType.typeName, "STRING");
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
  ASSERT_EQ(plan->columns[0].dataType.typeName, "INT");
  ASSERT_EQ(plan->columns[1].name, "data");
  ASSERT_EQ(plan->columns[1].dataType.typeName, "STRING");
  ASSERT_TRUE(plan->bIfNotExist);
}
