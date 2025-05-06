#pragma once

#include <string>
#include "SqlBaseParser.h"

class AstBuilder
{
public:
    AstBuilder();
    ~AstBuilder();

    std::string visitCompoundOrSingleStatement(sqlgrammar::SqlBaseParser::CompoundOrSingleStatementContext* context);
};
