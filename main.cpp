#include <iostream>

#include "antlr4-runtime.h"
#include "SqlBaseLexer.h"
#include "SqlBaseParser.h"
#include "AstBuilder.h"

using namespace sqlgrammar;
using namespace antlr4;

int main(int , const char **) {
  ANTLRInputStream input("CREATE TABLE my_tbl1 (id INT, data STRING)");
  SqlBaseLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  SqlBaseParser parser(&tokens);
  SqlBaseParser::CompoundOrSingleStatementContext* parsed = parser.compoundOrSingleStatement();

  std::cout << parsed->toStringTree() << std::endl;
  std::cout << AstBuilder().visitCompoundOrSingleStatement(parsed) << std::endl << std::endl;

  return 0;
}
