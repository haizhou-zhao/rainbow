#include <iostream>
#include <cassert>
#include "antlr4-runtime.h"
#include "SqlBaseLexer.h"
#include "SqlBaseParser.h"
#include "AstBuilder.h"
#include "Catalog.h"
#include "InMemoryCatalog.h"
#include "Rule.h"
#include "SqlContext.h"
#include "TreeNode.h"

using namespace sqlgrammar;
using namespace antlr4;


int main(int , const char **) {
  SqlContext sqlCtx;
  sqlCtx.catalogManager = new CatalogManager();
  sqlCtx.catalogManager->addCatalog("default", std::make_shared<InMemoryCatalog>());

  ANTLRInputStream input("CREATE TABLE my_tbl1 (id INT, data STRING)");
  SqlBaseLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  SqlBaseParser parser(&tokens);
  SqlBaseParser::CompoundOrSingleStatementContext* parsed = parser.compoundOrSingleStatement();

  std::cout << parsed->toStringTree() << std::endl;
  std::shared_ptr<CreateTable> plan = std::any_cast<std::shared_ptr<CreateTable>>(AstBuilder().visitCompoundOrSingleStatement(parsed));
  ResolveCatalogs r;
  r.init(&sqlCtx);
  auto result = plan->resolveRulesDownWithPruning([](const TreeNode* n){ return false; }, &r);
  (std::dynamic_pointer_cast<CreateTable>(result.afterRule))->run(&sqlCtx);
  assert(sqlCtx.currentCatalog()->tableExists("default", "my_tbl1"));

  ANTLRInputStream input2("ALTER TABLE my_tbl1 ADD COLUMNS (event_time TIMESTAMP)");
  SqlBaseLexer lexer2(&input2);
  CommonTokenStream tokens2(&lexer2);
  SqlBaseParser parser2(&tokens2);
  SqlBaseParser::CompoundOrSingleStatementContext* parsed2 = parser2.compoundOrSingleStatement();
  std::cout << parsed2->toStringTree() << std::endl;
  std::shared_ptr<AddColumns> plan2 = std::any_cast<std::shared_ptr<AddColumns>>(AstBuilder().visitCompoundOrSingleStatement(parsed2));
  auto result2 = plan2->resolveRulesDownWithPruning([](const TreeNode* n){ return false; }, &r);
  std::shared_ptr<ResolvedIdentifier> identifier2 = std::static_pointer_cast<ResolvedIdentifier>(std::static_pointer_cast<AddColumns>(result2.afterRule)->tableName());
  
  assert(plan2->tableName()->nameParts.size() == 2);
  assert(plan2->tableName()->nameParts[0] == "default");
  assert(plan2->tableName()->nameParts[1] == "my_tbl1");
  assert(plan2->columnsToAdd.size() == 1);
  assert(plan2->columnsToAdd[0].name == "event_time");
  assert(plan2->columnsToAdd[0].dataType.typeName == "TIMESTAMP");
  assert(plan2->columnsToAdd[0].bNullable == true);

  return 0;
}
