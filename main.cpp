#include <iostream>
#include <cassert>
#include "antlr4-runtime.h"
#include "SqlBaseLexer.h"
#include "SqlBaseParser.h"
#include "AstBuilder.h"
#include "Catalog.h"
#include "Rule.h"
#include "SqlContext.h"
#include "TreeNode.h"

using namespace sqlgrammar;
using namespace antlr4;


int main(int , const char **) {
  SqlContext sqlCtx;
  sqlCtx.catalogManager = new CatalogManager();

  ANTLRInputStream input("CREATE TABLE my_tbl1 (id INT, data STRING)");
  SqlBaseLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  SqlBaseParser parser(&tokens);
  SqlBaseParser::CompoundOrSingleStatementContext* parsed = parser.compoundOrSingleStatement();

  std::cout << parsed->toStringTree() << std::endl;
  std::shared_ptr<CreateTable> plan = std::any_cast<std::shared_ptr<CreateTable>>(AstBuilder().visitCompoundOrSingleStatement(parsed));
  ResolveCatalogs r;
  auto result = plan->resolveRulesDownWithPruning([](const TreeNode* n){ return false; }, &r);
  

  std::shared_ptr<ResolvedIdentifier> identifier = std::static_pointer_cast<ResolvedIdentifier>(std::static_pointer_cast<CreateTable>(result.afterRule)->name());
  if (identifier != nullptr) {
    std::string database;
    std::string table;
    if (identifier->nameParts.size() == 2) {
      database = identifier->nameParts[0];
      table = identifier->nameParts[1];
    } else if (identifier->nameParts.size() == 1) {
      table = identifier->nameParts[0];
    }
    sqlCtx.catalogManager->catalog(identifier->catalogName)->createTable(database, table);
  }

  assert(sqlCtx.catalogManager->currentCatalog()->tableExists("", "my_tbl1"));

  return 0;
}
