#include "AstBuilder.h"
#include "SqlBaseParserVisitor.h"
#include "SqlParserVisitor.h"

AstBuilder::AstBuilder(/* args */)
{
}

AstBuilder::~AstBuilder()
{
}

std::string AstBuilder::visitCompoundOrSingleStatement(sqlgrammar::SqlBaseParser::CompoundOrSingleStatementContext* context)
{
    sqlgrammar::SqlBaseParser::SingleStatementContext* single_stmt = context->singleStatement();
    SqlParserVisitor visitor;
    std::any r = single_stmt->accept(&visitor);
    return std::any_cast<std::string>(r);
}
