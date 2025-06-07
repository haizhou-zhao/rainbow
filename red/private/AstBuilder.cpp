#include "AstBuilder.h"
#include "SqlPlan.h"

AstBuilder::AstBuilder() {}

AstBuilder::~AstBuilder() {}

void AstBuilder::stripSingleQuotes(std::string &s) const {
  if (s.length() >= 2) {
    if (s.front() == '\'') {
      s.erase(0, 1);
    }
    if (s.back() == '\'') {
      s.pop_back();
    }
  }
}

void AstBuilder::stripDoubleQuotes(std::string &s) const {
  if (s.length() >= 2) {
    if (s.front() == '"') {
      s.erase(0, 1);
    }
    if (s.back() == '"') {
      s.pop_back();
    }
  }
}

std::any AstBuilder::visitCompoundOrSingleStatement(
    SqlBaseParser::CompoundOrSingleStatementContext *context) {
  // TODO compound stmt
  sqlgrammar::SqlBaseParser::SingleStatementContext *single_stmt =
      context->singleStatement();
  return single_stmt->accept(this);
}

std::any AstBuilder::visitSingleCompoundStatement(
    SqlBaseParser::SingleCompoundStatementContext *context) {
  return std::any();
}

std::any AstBuilder::visitBeginEndCompoundBlock(
    SqlBaseParser::BeginEndCompoundBlockContext *context) {
  return std::any();
}

std::any
AstBuilder::visitCompoundBody(SqlBaseParser::CompoundBodyContext *context) {
  return std::any();
}

std::any AstBuilder::visitCompoundStatement(
    SqlBaseParser::CompoundStatementContext *context) {
  return std::any();
}

std::any AstBuilder::visitSetVariableWithOptionalKeyword(
    SqlBaseParser::SetVariableWithOptionalKeywordContext *context) {
  return std::any();
}

std::any
AstBuilder::visitSqlStateValue(SqlBaseParser::SqlStateValueContext *context) {
  return std::any();
}

std::any AstBuilder::visitDeclareConditionStatement(
    SqlBaseParser::DeclareConditionStatementContext *context) {
  return std::any();
}

std::any
AstBuilder::visitConditionValue(SqlBaseParser::ConditionValueContext *context) {
  return std::any();
}

std::any AstBuilder::visitConditionValues(
    SqlBaseParser::ConditionValuesContext *context) {
  return std::any();
}

std::any AstBuilder::visitDeclareHandlerStatement(
    SqlBaseParser::DeclareHandlerStatementContext *context) {
  return std::any();
}

std::any
AstBuilder::visitWhileStatement(SqlBaseParser::WhileStatementContext *context) {
  return std::any();
}

std::any AstBuilder::visitIfElseStatement(
    SqlBaseParser::IfElseStatementContext *context) {
  return std::any();
}

std::any AstBuilder::visitRepeatStatement(
    SqlBaseParser::RepeatStatementContext *context) {
  return std::any();
}

std::any
AstBuilder::visitLeaveStatement(SqlBaseParser::LeaveStatementContext *context) {
  return std::any();
}

std::any AstBuilder::visitIterateStatement(
    SqlBaseParser::IterateStatementContext *context) {
  return std::any();
}

std::any AstBuilder::visitSearchedCaseStatement(
    SqlBaseParser::SearchedCaseStatementContext *context) {
  return std::any();
}

std::any AstBuilder::visitSimpleCaseStatement(
    SqlBaseParser::SimpleCaseStatementContext *context) {
  return std::any();
}

std::any
AstBuilder::visitLoopStatement(SqlBaseParser::LoopStatementContext *context) {
  return std::any();
}

std::any
AstBuilder::visitForStatement(SqlBaseParser::ForStatementContext *context) {
  return std::any();
}

std::any AstBuilder::visitSingleStatement(
    SqlBaseParser::SingleStatementContext *context) {
  return context->statement()->accept(this);
  ;
}

std::any
AstBuilder::visitBeginLabel(SqlBaseParser::BeginLabelContext *context) {
  return std::any();
}

std::any AstBuilder::visitEndLabel(SqlBaseParser::EndLabelContext *context) {
  return std::any();
}

std::any AstBuilder::visitSingleExpression(
    SqlBaseParser::SingleExpressionContext *context) {
  return std::any();
}

std::any AstBuilder::visitSingleTableIdentifier(
    SqlBaseParser::SingleTableIdentifierContext *context) {
  return std::any();
}

std::any AstBuilder::visitSingleMultipartIdentifier(
    SqlBaseParser::SingleMultipartIdentifierContext *context) {
  return std::any();
}

std::any AstBuilder::visitSingleFunctionIdentifier(
    SqlBaseParser::SingleFunctionIdentifierContext *context) {
  return std::any();
}

std::any
AstBuilder::visitSingleDataType(SqlBaseParser::SingleDataTypeContext *context) {
  return std::any();
}

std::any AstBuilder::visitSingleTableSchema(
    SqlBaseParser::SingleTableSchemaContext *context) {
  return std::any();
}

std::any AstBuilder::visitStatementDefault(
    SqlBaseParser::StatementDefaultContext *context) {
  return std::any();
}

std::any AstBuilder::visitVisitExecuteImmediate(
    SqlBaseParser::VisitExecuteImmediateContext *context) {
  return std::any();
}

std::any
AstBuilder::visitDmlStatement(SqlBaseParser::DmlStatementContext *context) {
  return std::any();
}

std::any AstBuilder::visitUse(SqlBaseParser::UseContext *context) {
  return std::any();
}

std::any
AstBuilder::visitUseNamespace(SqlBaseParser::UseNamespaceContext *context) {
  return std::any();
}

std::any
AstBuilder::visitSetCatalog(SqlBaseParser::SetCatalogContext *context) {
  return std::any();
}

std::any AstBuilder::visitCreateNamespace(
    SqlBaseParser::CreateNamespaceContext *context) {
  return std::any();
}

std::any AstBuilder::visitSetNamespaceProperties(
    SqlBaseParser::SetNamespacePropertiesContext *context) {
  return std::any();
}

std::any AstBuilder::visitUnsetNamespaceProperties(
    SqlBaseParser::UnsetNamespacePropertiesContext *context) {
  return std::any();
}

std::any AstBuilder::visitSetNamespaceLocation(
    SqlBaseParser::SetNamespaceLocationContext *context) {
  return std::any();
}

std::any
AstBuilder::visitDropNamespace(SqlBaseParser::DropNamespaceContext *context) {
  return std::any();
}

std::any
AstBuilder::visitShowNamespaces(SqlBaseParser::ShowNamespacesContext *context) {
  return std::any();
}

std::any AstBuilder::AstBuilder::visitCreateTable(
    SqlBaseParser::CreateTableContext *context) {
  std::shared_ptr<CreateTable> plan = std::make_shared<CreateTable>();
  CreateTableHeader header = std::any_cast<CreateTableHeader>(
      visitCreateTableHeader(context->createTableHeader()));
  auto identifiers = header.identifierRefCtx->multipartIdentifier()
                         ->errorCapturingIdentifier();
  std::transform(identifiers.begin(), identifiers.end(),
                 std::back_inserter(plan->name()->nameParts),
                 [](SqlBaseParser::ErrorCapturingIdentifierContext *ctx) {
                   return ctx->identifier()->getText();
                 });
  auto cols = std::any_cast<TableElements>(
      visitTableElementList(context->tableElementList()));
  std::swap(plan->columns, cols.columnDef);
  plan->bIfNotExist = header.bIfNotExist;
  return plan;
}

std::any AstBuilder::visitCreateTableLike(
    SqlBaseParser::CreateTableLikeContext *context) {
  return std::any();
}

std::any
AstBuilder::visitReplaceTable(SqlBaseParser::ReplaceTableContext *context) {
  return std::any();
}

std::any AstBuilder::visitAnalyze(SqlBaseParser::AnalyzeContext *context) {
  return std::any();
}

std::any
AstBuilder::visitAnalyzeTables(SqlBaseParser::AnalyzeTablesContext *context) {
  return std::any();
}

std::any AstBuilder::visitAddTableColumns(
    SqlBaseParser::AddTableColumnsContext *context) {
  std::shared_ptr<AddColumns> plan = std::make_shared<AddColumns>();
  plan->tableName()->nameParts = std::any_cast<std::vector<std::string>>(
      context->identifierReference()->accept(this));
  plan->columnsToAdd =
      std::any_cast<std::vector<Column>>(context->columns->accept(this));
  return plan;
}

std::any AstBuilder::visitRenameTableColumn(
    SqlBaseParser::RenameTableColumnContext *context) {
  return std::any();
}

std::any AstBuilder::visitDropTableColumns(
    SqlBaseParser::DropTableColumnsContext *context) {
  return std::any();
}

std::any
AstBuilder::visitRenameTable(SqlBaseParser::RenameTableContext *context) {
  return std::any();
}

std::any AstBuilder::visitSetTableProperties(
    SqlBaseParser::SetTablePropertiesContext *context) {
  return std::any();
}

std::any AstBuilder::visitUnsetTableProperties(
    SqlBaseParser::UnsetTablePropertiesContext *context) {
  return std::any();
}

std::any AstBuilder::visitAlterTableAlterColumn(
    SqlBaseParser::AlterTableAlterColumnContext *context) {
  return std::any();
}

std::any AstBuilder::visitHiveChangeColumn(
    SqlBaseParser::HiveChangeColumnContext *context) {
  return std::any();
}

std::any AstBuilder::visitHiveReplaceColumns(
    SqlBaseParser::HiveReplaceColumnsContext *context) {
  return std::any();
}

std::any
AstBuilder::visitSetTableSerDe(SqlBaseParser::SetTableSerDeContext *context) {
  return std::any();
}

std::any AstBuilder::visitAddTablePartition(
    SqlBaseParser::AddTablePartitionContext *context) {
  return std::any();
}

std::any AstBuilder::visitRenameTablePartition(
    SqlBaseParser::RenameTablePartitionContext *context) {
  return std::any();
}

std::any AstBuilder::visitDropTablePartitions(
    SqlBaseParser::DropTablePartitionsContext *context) {
  return std::any();
}

std::any AstBuilder::visitSetTableLocation(
    SqlBaseParser::SetTableLocationContext *context) {
  return std::any();
}

std::any AstBuilder::visitRecoverPartitions(
    SqlBaseParser::RecoverPartitionsContext *context) {
  return std::any();
}

std::any
AstBuilder::visitAlterClusterBy(SqlBaseParser::AlterClusterByContext *context) {
  return std::any();
}

std::any AstBuilder::visitAlterTableCollation(
    SqlBaseParser::AlterTableCollationContext *context) {
  return std::any();
}

std::any AstBuilder::visitAddTableConstraint(
    SqlBaseParser::AddTableConstraintContext *context) {
  return std::any();
}

std::any AstBuilder::visitDropTableConstraint(
    SqlBaseParser::DropTableConstraintContext *context) {
  return std::any();
}

std::any AstBuilder::visitDropTable(SqlBaseParser::DropTableContext *context) {
  return std::any();
}

std::any AstBuilder::visitDropView(SqlBaseParser::DropViewContext *context) {
  return std::any();
}

std::any
AstBuilder::visitCreateView(SqlBaseParser::CreateViewContext *context) {
  return std::any();
}

std::any AstBuilder::visitCreateTempViewUsing(
    SqlBaseParser::CreateTempViewUsingContext *context) {
  return std::any();
}

std::any
AstBuilder::visitAlterViewQuery(SqlBaseParser::AlterViewQueryContext *context) {
  return std::any();
}

std::any AstBuilder::visitAlterViewSchemaBinding(
    SqlBaseParser::AlterViewSchemaBindingContext *context) {
  return std::any();
}

std::any
AstBuilder::visitCreateFunction(SqlBaseParser::CreateFunctionContext *context) {
  return std::any();
}

std::any AstBuilder::visitCreateUserDefinedFunction(
    SqlBaseParser::CreateUserDefinedFunctionContext *context) {
  return std::any();
}

std::any
AstBuilder::visitDropFunction(SqlBaseParser::DropFunctionContext *context) {
  return std::any();
}

std::any
AstBuilder::visitCreateVariable(SqlBaseParser::CreateVariableContext *context) {
  return std::any();
}

std::any
AstBuilder::visitDropVariable(SqlBaseParser::DropVariableContext *context) {
  return std::any();
}

std::any AstBuilder::visitExplain(SqlBaseParser::ExplainContext *context) {
  return std::any();
}

std::any
AstBuilder::visitShowTables(SqlBaseParser::ShowTablesContext *context) {
  return std::any();
}

std::any AstBuilder::visitShowTableExtended(
    SqlBaseParser::ShowTableExtendedContext *context) {
  return std::any();
}

std::any AstBuilder::visitShowTblProperties(
    SqlBaseParser::ShowTblPropertiesContext *context) {
  return std::any();
}

std::any
AstBuilder::visitShowColumns(SqlBaseParser::ShowColumnsContext *context) {
  return std::any();
}

std::any AstBuilder::visitShowViews(SqlBaseParser::ShowViewsContext *context) {
  return std::any();
}

std::any
AstBuilder::visitShowPartitions(SqlBaseParser::ShowPartitionsContext *context) {
  return std::any();
}

std::any
AstBuilder::visitShowFunctions(SqlBaseParser::ShowFunctionsContext *context) {
  return std::any();
}

std::any
AstBuilder::visitShowProcedures(SqlBaseParser::ShowProceduresContext *context) {
  return std::any();
}

std::any AstBuilder::visitShowCreateTable(
    SqlBaseParser::ShowCreateTableContext *context) {
  return std::any();
}

std::any AstBuilder::visitShowCurrentNamespace(
    SqlBaseParser::ShowCurrentNamespaceContext *context) {
  return std::any();
}

std::any
AstBuilder::visitShowCatalogs(SqlBaseParser::ShowCatalogsContext *context) {
  return std::any();
}

std::any AstBuilder::visitDescribeFunction(
    SqlBaseParser::DescribeFunctionContext *context) {
  return std::any();
}

std::any AstBuilder::visitDescribeProcedure(
    SqlBaseParser::DescribeProcedureContext *context) {
  return std::any();
}

std::any AstBuilder::visitDescribeNamespace(
    SqlBaseParser::DescribeNamespaceContext *context) {
  return std::any();
}

std::any AstBuilder::visitDescribeRelation(
    SqlBaseParser::DescribeRelationContext *context) {
  return std::any();
}

std::any
AstBuilder::visitDescribeQuery(SqlBaseParser::DescribeQueryContext *context) {
  return std::any();
}

std::any AstBuilder::visitCommentNamespace(
    SqlBaseParser::CommentNamespaceContext *context) {
  return std::any();
}

std::any
AstBuilder::visitCommentTable(SqlBaseParser::CommentTableContext *context) {
  return std::any();
}

std::any
AstBuilder::visitRefreshTable(SqlBaseParser::RefreshTableContext *context) {
  return std::any();
}

std::any AstBuilder::visitRefreshFunction(
    SqlBaseParser::RefreshFunctionContext *context) {
  return std::any();
}

std::any AstBuilder::visitRefreshResource(
    SqlBaseParser::RefreshResourceContext *context) {
  return std::any();
}

std::any
AstBuilder::visitCacheTable(SqlBaseParser::CacheTableContext *context) {
  return std::any();
}

std::any
AstBuilder::visitUncacheTable(SqlBaseParser::UncacheTableContext *context) {
  return std::any();
}

std::any
AstBuilder::visitClearCache(SqlBaseParser::ClearCacheContext *context) {
  return std::any();
}

std::any AstBuilder::visitLoadData(SqlBaseParser::LoadDataContext *context) {
  return std::any();
}

std::any
AstBuilder::visitTruncateTable(SqlBaseParser::TruncateTableContext *context) {
  return std::any();
}

std::any
AstBuilder::visitRepairTable(SqlBaseParser::RepairTableContext *context) {
  return std::any();
}

std::any
AstBuilder::visitManageResource(SqlBaseParser::ManageResourceContext *context) {
  return std::any();
}

std::any
AstBuilder::visitCreateIndex(SqlBaseParser::CreateIndexContext *context) {
  return std::any();
}

std::any AstBuilder::visitDropIndex(SqlBaseParser::DropIndexContext *context) {
  return std::any();
}

std::any AstBuilder::visitCall(SqlBaseParser::CallContext *context) {
  return std::any();
}

std::any AstBuilder::visitFailNativeCommand(
    SqlBaseParser::FailNativeCommandContext *context) {
  return std::any();
}

std::any
AstBuilder::visitFailSetRole(SqlBaseParser::FailSetRoleContext *context) {
  return std::any();
}

std::any
AstBuilder::visitSetTimeZone(SqlBaseParser::SetTimeZoneContext *context) {
  return std::any();
}

std::any
AstBuilder::visitSetVariable(SqlBaseParser::SetVariableContext *context) {
  return std::any();
}

std::any AstBuilder::visitSetQuotedConfiguration(
    SqlBaseParser::SetQuotedConfigurationContext *context) {
  return std::any();
}

std::any AstBuilder::visitSetConfiguration(
    SqlBaseParser::SetConfigurationContext *context) {
  return std::any();
}

std::any AstBuilder::visitResetQuotedConfiguration(
    SqlBaseParser::ResetQuotedConfigurationContext *context) {
  return std::any();
}

std::any AstBuilder::visitResetConfiguration(
    SqlBaseParser::ResetConfigurationContext *context) {
  return std::any();
}

std::any AstBuilder::visitExecuteImmediate(
    SqlBaseParser::ExecuteImmediateContext *context) {
  return std::any();
}

std::any AstBuilder::visitExecuteImmediateUsing(
    SqlBaseParser::ExecuteImmediateUsingContext *context) {
  return std::any();
}

std::any AstBuilder::visitExecuteImmediateQueryParam(
    SqlBaseParser::ExecuteImmediateQueryParamContext *context) {
  return std::any();
}

std::any AstBuilder::visitExecuteImmediateArgument(
    SqlBaseParser::ExecuteImmediateArgumentContext *context) {
  return std::any();
}

std::any AstBuilder::visitExecuteImmediateArgumentSeq(
    SqlBaseParser::ExecuteImmediateArgumentSeqContext *context) {
  return std::any();
}

std::any AstBuilder::visitTimezone(SqlBaseParser::TimezoneContext *context) {
  return std::any();
}

std::any AstBuilder::visitConfigKey(SqlBaseParser::ConfigKeyContext *context) {
  return std::any();
}

std::any
AstBuilder::visitConfigValue(SqlBaseParser::ConfigValueContext *context) {
  return std::any();
}

std::any AstBuilder::visitUnsupportedHiveNativeCommands(
    SqlBaseParser::UnsupportedHiveNativeCommandsContext *context) {
  return std::any();
}

std::any AstBuilder::visitCreateTableHeader(
    SqlBaseParser::CreateTableHeaderContext *context) {
  CreateTableHeader header;
  header.bIsTemporary = context->TEMPORARY();
  header.bIfNotExist = context->EXISTS();
  header.bIsExternal = context->EXTERNAL();
  header.identifierRefCtx = context->identifierReference();
  // if (temporary && ifNotExists) {
  //     invalidStatement("CREATE TEMPORARY TABLE ... IF NOT EXISTS", ctx)
  //   }
  return header;
}

std::any AstBuilder::visitReplaceTableHeader(
    SqlBaseParser::ReplaceTableHeaderContext *context) {
  return std::any();
}

std::any
AstBuilder::visitClusterBySpec(SqlBaseParser::ClusterBySpecContext *context) {
  return std::any();
}

std::any
AstBuilder::visitBucketSpec(SqlBaseParser::BucketSpecContext *context) {
  return std::any();
}

std::any AstBuilder::visitSkewSpec(SqlBaseParser::SkewSpecContext *context) {
  return std::any();
}

std::any
AstBuilder::visitLocationSpec(SqlBaseParser::LocationSpecContext *context) {
  return std::any();
}

std::any
AstBuilder::visitSchemaBinding(SqlBaseParser::SchemaBindingContext *context) {
  return std::any();
}

std::any
AstBuilder::visitCommentSpec(SqlBaseParser::CommentSpecContext *context) {
  return visitStringLit(context->stringLit());
}

std::any
AstBuilder::visitSingleQuery(SqlBaseParser::SingleQueryContext *context) {
  return std::any();
}

std::any AstBuilder::visitQuery(SqlBaseParser::QueryContext *context) {
  return std::any();
}

std::any AstBuilder::visitInsertOverwriteTable(
    SqlBaseParser::InsertOverwriteTableContext *context) {
  return std::any();
}

std::any AstBuilder::visitInsertIntoTable(
    SqlBaseParser::InsertIntoTableContext *context) {
  return std::any();
}

std::any AstBuilder::visitInsertIntoReplaceWhere(
    SqlBaseParser::InsertIntoReplaceWhereContext *context) {
  return std::any();
}

std::any AstBuilder::visitInsertOverwriteHiveDir(
    SqlBaseParser::InsertOverwriteHiveDirContext *context) {
  return std::any();
}

std::any AstBuilder::visitInsertOverwriteDir(
    SqlBaseParser::InsertOverwriteDirContext *context) {
  return std::any();
}

std::any AstBuilder::visitPartitionSpecLocation(
    SqlBaseParser::PartitionSpecLocationContext *context) {
  return std::any();
}

std::any
AstBuilder::visitPartitionSpec(SqlBaseParser::PartitionSpecContext *context) {
  return std::any();
}

std::any
AstBuilder::visitPartitionVal(SqlBaseParser::PartitionValContext *context) {
  return std::any();
}

std::any AstBuilder::visitNamespace(SqlBaseParser::NamespaceContext *context) {
  return std::any();
}

std::any
AstBuilder::visitNamespaces(SqlBaseParser::NamespacesContext *context) {
  return std::any();
}

std::any AstBuilder::visitVariable(SqlBaseParser::VariableContext *context) {
  return std::any();
}

std::any AstBuilder::visitDescribeFuncName(
    SqlBaseParser::DescribeFuncNameContext *context) {
  return std::any();
}

std::any AstBuilder::visitDescribeColName(
    SqlBaseParser::DescribeColNameContext *context) {
  return std::any();
}

std::any AstBuilder::visitCtes(SqlBaseParser::CtesContext *context) {
  return std::any();
}

std::any
AstBuilder::visitNamedQuery(SqlBaseParser::NamedQueryContext *context) {
  return std::any();
}

std::any
AstBuilder::visitTableProvider(SqlBaseParser::TableProviderContext *context) {
  return std::any();
}

std::any AstBuilder::visitCreateTableClauses(
    SqlBaseParser::CreateTableClausesContext *context) {
  return std::any();
}

std::any
AstBuilder::visitPropertyList(SqlBaseParser::PropertyListContext *context) {
  return std::any();
}

std::any AstBuilder::visitProperty(SqlBaseParser::PropertyContext *context) {
  return std::any();
}

std::any
AstBuilder::visitPropertyKey(SqlBaseParser::PropertyKeyContext *context) {
  return std::any();
}

std::any
AstBuilder::visitPropertyValue(SqlBaseParser::PropertyValueContext *context) {
  return std::any();
}

std::any AstBuilder::visitExpressionPropertyList(
    SqlBaseParser::ExpressionPropertyListContext *context) {
  return std::any();
}

std::any AstBuilder::visitExpressionProperty(
    SqlBaseParser::ExpressionPropertyContext *context) {
  return std::any();
}

std::any
AstBuilder::visitConstantList(SqlBaseParser::ConstantListContext *context) {
  return std::any();
}

std::any AstBuilder::visitNestedConstantList(
    SqlBaseParser::NestedConstantListContext *context) {
  return std::any();
}

std::any AstBuilder::visitCreateFileFormat(
    SqlBaseParser::CreateFileFormatContext *context) {
  return std::any();
}

std::any AstBuilder::visitTableFileFormat(
    SqlBaseParser::TableFileFormatContext *context) {
  return std::any();
}

std::any AstBuilder::visitGenericFileFormat(
    SqlBaseParser::GenericFileFormatContext *context) {
  return std::any();
}

std::any
AstBuilder::visitStorageHandler(SqlBaseParser::StorageHandlerContext *context) {
  return std::any();
}

std::any AstBuilder::visitResource(SqlBaseParser::ResourceContext *context) {
  return std::any();
}

std::any AstBuilder::visitSingleInsertQuery(
    SqlBaseParser::SingleInsertQueryContext *context) {
  return std::any();
}

std::any AstBuilder::visitMultiInsertQuery(
    SqlBaseParser::MultiInsertQueryContext *context) {
  return std::any();
}

std::any AstBuilder::visitDeleteFromTable(
    SqlBaseParser::DeleteFromTableContext *context) {
  return std::any();
}

std::any
AstBuilder::visitUpdateTable(SqlBaseParser::UpdateTableContext *context) {
  return std::any();
}

std::any
AstBuilder::visitMergeIntoTable(SqlBaseParser::MergeIntoTableContext *context) {
  return std::any();
}

std::any AstBuilder::visitIdentifierReference(
    SqlBaseParser::IdentifierReferenceContext *context) {
  return context->multipartIdentifier()->accept(this);
}

std::any AstBuilder::visitCatalogIdentifierReference(
    SqlBaseParser::CatalogIdentifierReferenceContext *context) {
  return std::any();
}

std::any AstBuilder::visitQueryOrganization(
    SqlBaseParser::QueryOrganizationContext *context) {
  return std::any();
}

std::any AstBuilder::visitMultiInsertQueryBody(
    SqlBaseParser::MultiInsertQueryBodyContext *context) {
  return std::any();
}

std::any AstBuilder::visitOperatorPipeStatement(
    SqlBaseParser::OperatorPipeStatementContext *context) {
  return std::any();
}

std::any AstBuilder::visitQueryTermDefault(
    SqlBaseParser::QueryTermDefaultContext *context) {
  return std::any();
}

std::any
AstBuilder::visitSetOperation(SqlBaseParser::SetOperationContext *context) {
  return std::any();
}

std::any AstBuilder::visitQueryPrimaryDefault(
    SqlBaseParser::QueryPrimaryDefaultContext *context) {
  return std::any();
}

std::any AstBuilder::visitFromStmt(SqlBaseParser::FromStmtContext *context) {
  return std::any();
}

std::any AstBuilder::visitTable(SqlBaseParser::TableContext *context) {
  return std::any();
}

std::any AstBuilder::visitInlineTableDefault1(
    SqlBaseParser::InlineTableDefault1Context *context) {
  return std::any();
}

std::any AstBuilder::visitSubquery(SqlBaseParser::SubqueryContext *context) {
  return std::any();
}

std::any AstBuilder::visitSortItem(SqlBaseParser::SortItemContext *context) {
  return std::any();
}

std::any
AstBuilder::visitFromStatement(SqlBaseParser::FromStatementContext *context) {
  return std::any();
}

std::any AstBuilder::visitFromStatementBody(
    SqlBaseParser::FromStatementBodyContext *context) {
  return std::any();
}

std::any AstBuilder::visitTransformQuerySpecification(
    SqlBaseParser::TransformQuerySpecificationContext *context) {
  return std::any();
}

std::any AstBuilder::visitRegularQuerySpecification(
    SqlBaseParser::RegularQuerySpecificationContext *context) {
  return std::any();
}

std::any AstBuilder::visitTransformClause(
    SqlBaseParser::TransformClauseContext *context) {
  return std::any();
}

std::any
AstBuilder::visitSelectClause(SqlBaseParser::SelectClauseContext *context) {
  return std::any();
}

std::any AstBuilder::visitSetClause(SqlBaseParser::SetClauseContext *context) {
  return std::any();
}

std::any
AstBuilder::visitMatchedClause(SqlBaseParser::MatchedClauseContext *context) {
  return std::any();
}

std::any AstBuilder::visitNotMatchedClause(
    SqlBaseParser::NotMatchedClauseContext *context) {
  return std::any();
}

std::any AstBuilder::visitNotMatchedBySourceClause(
    SqlBaseParser::NotMatchedBySourceClauseContext *context) {
  return std::any();
}

std::any
AstBuilder::visitMatchedAction(SqlBaseParser::MatchedActionContext *context) {
  return std::any();
}

std::any AstBuilder::visitNotMatchedAction(
    SqlBaseParser::NotMatchedActionContext *context) {
  return std::any();
}

std::any AstBuilder::visitNotMatchedBySourceAction(
    SqlBaseParser::NotMatchedBySourceActionContext *context) {
  return std::any();
}

std::any
AstBuilder::visitExceptClause(SqlBaseParser::ExceptClauseContext *context) {
  return std::any();
}

std::any
AstBuilder::visitAssignmentList(SqlBaseParser::AssignmentListContext *context) {
  return std::any();
}

std::any
AstBuilder::visitAssignment(SqlBaseParser::AssignmentContext *context) {
  return std::any();
}

std::any
AstBuilder::visitWhereClause(SqlBaseParser::WhereClauseContext *context) {
  return std::any();
}

std::any
AstBuilder::visitHavingClause(SqlBaseParser::HavingClauseContext *context) {
  return std::any();
}

std::any AstBuilder::visitHint(SqlBaseParser::HintContext *context) {
  return std::any();
}

std::any
AstBuilder::visitHintStatement(SqlBaseParser::HintStatementContext *context) {
  return std::any();
}

std::any
AstBuilder::visitFromClause(SqlBaseParser::FromClauseContext *context) {
  return std::any();
}

std::any
AstBuilder::visitTemporalClause(SqlBaseParser::TemporalClauseContext *context) {
  return std::any();
}

std::any AstBuilder::visitAggregationClause(
    SqlBaseParser::AggregationClauseContext *context) {
  return std::any();
}

std::any
AstBuilder::visitGroupByClause(SqlBaseParser::GroupByClauseContext *context) {
  return std::any();
}

std::any AstBuilder::visitGroupingAnalytics(
    SqlBaseParser::GroupingAnalyticsContext *context) {
  return std::any();
}

std::any AstBuilder::visitGroupingElement(
    SqlBaseParser::GroupingElementContext *context) {
  return std::any();
}

std::any
AstBuilder::visitGroupingSet(SqlBaseParser::GroupingSetContext *context) {
  return std::any();
}

std::any
AstBuilder::visitPivotClause(SqlBaseParser::PivotClauseContext *context) {
  return std::any();
}

std::any
AstBuilder::visitPivotColumn(SqlBaseParser::PivotColumnContext *context) {
  return std::any();
}

std::any
AstBuilder::visitPivotValue(SqlBaseParser::PivotValueContext *context) {
  return std::any();
}

std::any
AstBuilder::visitUnpivotClause(SqlBaseParser::UnpivotClauseContext *context) {
  return std::any();
}

std::any AstBuilder::visitUnpivotNullClause(
    SqlBaseParser::UnpivotNullClauseContext *context) {
  return std::any();
}

std::any AstBuilder::visitUnpivotOperator(
    SqlBaseParser::UnpivotOperatorContext *context) {
  return std::any();
}

std::any AstBuilder::visitUnpivotSingleValueColumnClause(
    SqlBaseParser::UnpivotSingleValueColumnClauseContext *context) {
  return std::any();
}

std::any AstBuilder::visitUnpivotMultiValueColumnClause(
    SqlBaseParser::UnpivotMultiValueColumnClauseContext *context) {
  return std::any();
}

std::any AstBuilder::visitUnpivotColumnSet(
    SqlBaseParser::UnpivotColumnSetContext *context) {
  return std::any();
}

std::any AstBuilder::visitUnpivotValueColumn(
    SqlBaseParser::UnpivotValueColumnContext *context) {
  return std::any();
}

std::any AstBuilder::visitUnpivotNameColumn(
    SqlBaseParser::UnpivotNameColumnContext *context) {
  return std::any();
}

std::any AstBuilder::visitUnpivotColumnAndAlias(
    SqlBaseParser::UnpivotColumnAndAliasContext *context) {
  return std::any();
}

std::any
AstBuilder::visitUnpivotColumn(SqlBaseParser::UnpivotColumnContext *context) {
  return std::any();
}

std::any
AstBuilder::visitUnpivotAlias(SqlBaseParser::UnpivotAliasContext *context) {
  return std::any();
}

std::any
AstBuilder::visitLateralView(SqlBaseParser::LateralViewContext *context) {
  return std::any();
}

std::any
AstBuilder::visitSetQuantifier(SqlBaseParser::SetQuantifierContext *context) {
  return std::any();
}

std::any AstBuilder::visitRelation(SqlBaseParser::RelationContext *context) {
  return std::any();
}

std::any AstBuilder::visitRelationExtension(
    SqlBaseParser::RelationExtensionContext *context) {
  return std::any();
}

std::any
AstBuilder::visitJoinRelation(SqlBaseParser::JoinRelationContext *context) {
  return std::any();
}

std::any AstBuilder::visitJoinType(SqlBaseParser::JoinTypeContext *context) {
  return std::any();
}

std::any
AstBuilder::visitJoinCriteria(SqlBaseParser::JoinCriteriaContext *context) {
  return std::any();
}

std::any AstBuilder::visitSample(SqlBaseParser::SampleContext *context) {
  return std::any();
}

std::any AstBuilder::visitSampleByPercentile(
    SqlBaseParser::SampleByPercentileContext *context) {
  return std::any();
}

std::any
AstBuilder::visitSampleByRows(SqlBaseParser::SampleByRowsContext *context) {
  return std::any();
}

std::any
AstBuilder::visitSampleByBucket(SqlBaseParser::SampleByBucketContext *context) {
  return std::any();
}

std::any
AstBuilder::visitSampleByBytes(SqlBaseParser::SampleByBytesContext *context) {
  return std::any();
}

std::any
AstBuilder::visitIdentifierList(SqlBaseParser::IdentifierListContext *context) {
  return std::any();
}

std::any
AstBuilder::visitIdentifierSeq(SqlBaseParser::IdentifierSeqContext *context) {
  return std::any();
}

std::any AstBuilder::visitOrderedIdentifierList(
    SqlBaseParser::OrderedIdentifierListContext *context) {
  return std::any();
}

std::any AstBuilder::visitOrderedIdentifier(
    SqlBaseParser::OrderedIdentifierContext *context) {
  return std::any();
}

std::any AstBuilder::visitIdentifierCommentList(
    SqlBaseParser::IdentifierCommentListContext *context) {
  return std::any();
}

std::any AstBuilder::visitIdentifierComment(
    SqlBaseParser::IdentifierCommentContext *context) {
  return std::any();
}

std::any AstBuilder::visitTableName(SqlBaseParser::TableNameContext *context) {
  return std::any();
}

std::any
AstBuilder::visitAliasedQuery(SqlBaseParser::AliasedQueryContext *context) {
  return std::any();
}

std::any AstBuilder::visitAliasedRelation(
    SqlBaseParser::AliasedRelationContext *context) {
  return std::any();
}

std::any AstBuilder::visitInlineTableDefault2(
    SqlBaseParser::InlineTableDefault2Context *context) {
  return std::any();
}

std::any AstBuilder::visitTableValuedFunction(
    SqlBaseParser::TableValuedFunctionContext *context) {
  return std::any();
}

std::any
AstBuilder::visitOptionsClause(SqlBaseParser::OptionsClauseContext *context) {
  return std::any();
}

std::any
AstBuilder::visitInlineTable(SqlBaseParser::InlineTableContext *context) {
  return std::any();
}

std::any AstBuilder::visitFunctionTableSubqueryArgument(
    SqlBaseParser::FunctionTableSubqueryArgumentContext *context) {
  return std::any();
}

std::any AstBuilder::visitTableArgumentPartitioning(
    SqlBaseParser::TableArgumentPartitioningContext *context) {
  return std::any();
}

std::any AstBuilder::visitFunctionTableNamedArgumentExpression(
    SqlBaseParser::FunctionTableNamedArgumentExpressionContext *context) {
  return std::any();
}

std::any AstBuilder::visitFunctionTableReferenceArgument(
    SqlBaseParser::FunctionTableReferenceArgumentContext *context) {
  return std::any();
}

std::any AstBuilder::visitFunctionTableArgument(
    SqlBaseParser::FunctionTableArgumentContext *context) {
  return std::any();
}

std::any
AstBuilder::visitFunctionTable(SqlBaseParser::FunctionTableContext *context) {
  return std::any();
}

std::any
AstBuilder::visitTableAlias(SqlBaseParser::TableAliasContext *context) {
  return std::any();
}

std::any
AstBuilder::visitRowFormatSerde(SqlBaseParser::RowFormatSerdeContext *context) {
  return std::any();
}

std::any AstBuilder::visitRowFormatDelimited(
    SqlBaseParser::RowFormatDelimitedContext *context) {
  return std::any();
}

std::any AstBuilder::visitMultipartIdentifierList(
    SqlBaseParser::MultipartIdentifierListContext *context) {
  return std::any();
}

std::any AstBuilder::visitMultipartIdentifier(
    SqlBaseParser::MultipartIdentifierContext *context) {
  std::vector<std::string> parts;
  auto errorCapturingIdentifiers = context->errorCapturingIdentifier();
  std::transform(errorCapturingIdentifiers.begin(),
                 errorCapturingIdentifiers.end(), std::back_inserter(parts),
                 [this](SqlBaseParser::ErrorCapturingIdentifierContext *part) {
                   return std::any_cast<std::string>(part->accept(this));
                 });
  return parts;
}

std::any AstBuilder::visitMultipartIdentifierPropertyList(
    SqlBaseParser::MultipartIdentifierPropertyListContext *context) {
  return std::any();
}

std::any AstBuilder::visitMultipartIdentifierProperty(
    SqlBaseParser::MultipartIdentifierPropertyContext *context) {
  return std::any();
}

std::any AstBuilder::visitTableIdentifier(
    SqlBaseParser::TableIdentifierContext *context) {
  return std::any();
}

std::any AstBuilder::visitFunctionIdentifier(
    SqlBaseParser::FunctionIdentifierContext *context) {
  return std::any();
}

std::any AstBuilder::visitNamedExpression(
    SqlBaseParser::NamedExpressionContext *context) {
  return std::any();
}

std::any AstBuilder::visitNamedExpressionSeq(
    SqlBaseParser::NamedExpressionSeqContext *context) {
  return std::any();
}

std::any AstBuilder::visitPartitionFieldList(
    SqlBaseParser::PartitionFieldListContext *context) {
  return std::any();
}

std::any AstBuilder::visitPartitionTransform(
    SqlBaseParser::PartitionTransformContext *context) {
  return std::any();
}

std::any AstBuilder::visitPartitionColumn(
    SqlBaseParser::PartitionColumnContext *context) {
  return std::any();
}

std::any AstBuilder::visitIdentityTransform(
    SqlBaseParser::IdentityTransformContext *context) {
  return std::any();
}

std::any
AstBuilder::visitApplyTransform(SqlBaseParser::ApplyTransformContext *context) {
  return std::any();
}

std::any AstBuilder::visitTransformArgument(
    SqlBaseParser::TransformArgumentContext *context) {
  return std::any();
}

std::any
AstBuilder::visitExpression(SqlBaseParser::ExpressionContext *context) {
  return context->getText();
}

std::any AstBuilder::visitNamedArgumentExpression(
    SqlBaseParser::NamedArgumentExpressionContext *context) {
  return std::any();
}

std::any AstBuilder::visitFunctionArgument(
    SqlBaseParser::FunctionArgumentContext *context) {
  return std::any();
}

std::any
AstBuilder::visitExpressionSeq(SqlBaseParser::ExpressionSeqContext *context) {
  return std::any();
}

std::any
AstBuilder::visitLogicalNot(SqlBaseParser::LogicalNotContext *context) {
  return std::any();
}

std::any
AstBuilder::visitPredicated(SqlBaseParser::PredicatedContext *context) {
  return std::any();
}

std::any AstBuilder::visitExists(SqlBaseParser::ExistsContext *context) {
  return std::any();
}

std::any
AstBuilder::visitLogicalBinary(SqlBaseParser::LogicalBinaryContext *context) {
  return std::any();
}

std::any AstBuilder::visitPredicate(SqlBaseParser::PredicateContext *context) {
  return std::any();
}

std::any AstBuilder::visitErrorCapturingNot(
    SqlBaseParser::ErrorCapturingNotContext *context) {
  return std::any();
}

std::any AstBuilder::visitValueExpressionDefault(
    SqlBaseParser::ValueExpressionDefaultContext *context) {
  return std::any();
}

std::any
AstBuilder::visitComparison(SqlBaseParser::ComparisonContext *context) {
  return std::any();
}

std::any AstBuilder::visitShiftExpression(
    SqlBaseParser::ShiftExpressionContext *context) {
  return std::any();
}

std::any AstBuilder::visitArithmeticBinary(
    SqlBaseParser::ArithmeticBinaryContext *context) {
  return std::any();
}

std::any AstBuilder::visitArithmeticUnary(
    SqlBaseParser::ArithmeticUnaryContext *context) {
  return std::any();
}

std::any
AstBuilder::visitShiftOperator(SqlBaseParser::ShiftOperatorContext *context) {
  return std::any();
}

std::any
AstBuilder::visitDatetimeUnit(SqlBaseParser::DatetimeUnitContext *context) {
  return std::any();
}

std::any AstBuilder::visitStruct(SqlBaseParser::StructContext *context) {
  return std::any();
}

std::any
AstBuilder::visitDereference(SqlBaseParser::DereferenceContext *context) {
  return std::any();
}

std::any
AstBuilder::visitCastByColon(SqlBaseParser::CastByColonContext *context) {
  return std::any();
}

std::any
AstBuilder::visitTimestampadd(SqlBaseParser::TimestampaddContext *context) {
  return std::any();
}

std::any AstBuilder::visitSubstring(SqlBaseParser::SubstringContext *context) {
  return std::any();
}

std::any AstBuilder::visitCast(SqlBaseParser::CastContext *context) {
  return std::any();
}

std::any AstBuilder::visitLambda(SqlBaseParser::LambdaContext *context) {
  return std::any();
}

std::any AstBuilder::visitParenthesizedExpression(
    SqlBaseParser::ParenthesizedExpressionContext *context) {
  return std::any();
}

std::any AstBuilder::visitAny_value(SqlBaseParser::Any_valueContext *context) {
  return std::any();
}

std::any AstBuilder::visitTrim(SqlBaseParser::TrimContext *context) {
  return std::any();
}

std::any
AstBuilder::visitSimpleCase(SqlBaseParser::SimpleCaseContext *context) {
  return std::any();
}

std::any
AstBuilder::visitCurrentLike(SqlBaseParser::CurrentLikeContext *context) {
  return std::any();
}

std::any AstBuilder::visitColumnReference(
    SqlBaseParser::ColumnReferenceContext *context) {
  return std::any();
}

std::any
AstBuilder::visitRowConstructor(SqlBaseParser::RowConstructorContext *context) {
  return std::any();
}

std::any AstBuilder::visitLast(SqlBaseParser::LastContext *context) {
  return std::any();
}

std::any AstBuilder::visitStar(SqlBaseParser::StarContext *context) {
  return std::any();
}

std::any AstBuilder::visitOverlay(SqlBaseParser::OverlayContext *context) {
  return std::any();
}

std::any AstBuilder::visitSubscript(SqlBaseParser::SubscriptContext *context) {
  return std::any();
}

std::any
AstBuilder::visitTimestampdiff(SqlBaseParser::TimestampdiffContext *context) {
  return std::any();
}

std::any AstBuilder::visitSubqueryExpression(
    SqlBaseParser::SubqueryExpressionContext *context) {
  return std::any();
}

std::any AstBuilder::visitCollate(SqlBaseParser::CollateContext *context) {
  return std::any();
}

std::any AstBuilder::visitConstantDefault(
    SqlBaseParser::ConstantDefaultContext *context) {
  return std::any();
}

std::any AstBuilder::visitExtract(SqlBaseParser::ExtractContext *context) {
  return std::any();
}

std::any
AstBuilder::visitFunctionCall(SqlBaseParser::FunctionCallContext *context) {
  return std::any();
}

std::any
AstBuilder::visitSearchedCase(SqlBaseParser::SearchedCaseContext *context) {
  return std::any();
}

std::any AstBuilder::visitPosition(SqlBaseParser::PositionContext *context) {
  return std::any();
}

std::any AstBuilder::visitFirst(SqlBaseParser::FirstContext *context) {
  return std::any();
}

std::any
AstBuilder::visitLiteralType(SqlBaseParser::LiteralTypeContext *context) {
  return std::any();
}

std::any
AstBuilder::visitNullLiteral(SqlBaseParser::NullLiteralContext *context) {
  return std::any();
}

std::any AstBuilder::visitPosParameterLiteral(
    SqlBaseParser::PosParameterLiteralContext *context) {
  return std::any();
}

std::any AstBuilder::visitNamedParameterLiteral(
    SqlBaseParser::NamedParameterLiteralContext *context) {
  return std::any();
}

std::any AstBuilder::visitIntervalLiteral(
    SqlBaseParser::IntervalLiteralContext *context) {
  return std::any();
}

std::any AstBuilder::visitTypeConstructor(
    SqlBaseParser::TypeConstructorContext *context) {
  return std::any();
}

std::any
AstBuilder::visitNumericLiteral(SqlBaseParser::NumericLiteralContext *context) {
  return std::any();
}

std::any
AstBuilder::visitBooleanLiteral(SqlBaseParser::BooleanLiteralContext *context) {
  return std::any();
}

std::any
AstBuilder::visitStringLiteral(SqlBaseParser::StringLiteralContext *context) {
  return std::any();
}

std::any AstBuilder::visitComparisonOperator(
    SqlBaseParser::ComparisonOperatorContext *context) {
  return std::any();
}

std::any AstBuilder::visitArithmeticOperator(
    SqlBaseParser::ArithmeticOperatorContext *context) {
  return std::any();
}

std::any AstBuilder::visitPredicateOperator(
    SqlBaseParser::PredicateOperatorContext *context) {
  return std::any();
}

std::any
AstBuilder::visitBooleanValue(SqlBaseParser::BooleanValueContext *context) {
  return std::any();
}

std::any AstBuilder::visitInterval(SqlBaseParser::IntervalContext *context) {
  return std::any();
}

std::any AstBuilder::visitErrorCapturingMultiUnitsInterval(
    SqlBaseParser::ErrorCapturingMultiUnitsIntervalContext *context) {
  return std::any();
}

std::any AstBuilder::visitMultiUnitsInterval(
    SqlBaseParser::MultiUnitsIntervalContext *context) {
  return std::any();
}

std::any AstBuilder::visitErrorCapturingUnitToUnitInterval(
    SqlBaseParser::ErrorCapturingUnitToUnitIntervalContext *context) {
  return std::any();
}

std::any AstBuilder::visitUnitToUnitInterval(
    SqlBaseParser::UnitToUnitIntervalContext *context) {
  return std::any();
}

std::any
AstBuilder::visitIntervalValue(SqlBaseParser::IntervalValueContext *context) {
  return std::any();
}

std::any AstBuilder::visitUnitInMultiUnits(
    SqlBaseParser::UnitInMultiUnitsContext *context) {
  return std::any();
}

std::any AstBuilder::visitUnitInUnitToUnit(
    SqlBaseParser::UnitInUnitToUnitContext *context) {
  return std::any();
}

std::any
AstBuilder::visitColPosition(SqlBaseParser::ColPositionContext *context) {
  return static_cast<std::size_t>(std::stoull(context->position->getText()));
}

std::any
AstBuilder::visitCollationSpec(SqlBaseParser::CollationSpecContext *context) {
  return std::any();
}

std::any
AstBuilder::visitCollateClause(SqlBaseParser::CollateClauseContext *context) {
  return std::any();
}

std::any AstBuilder::visitType(SqlBaseParser::TypeContext *context) {
  return std::any();
}

std::any AstBuilder::visitComplexDataType(
    SqlBaseParser::ComplexDataTypeContext *context) {
  // TODO proper type struct
  return context->complex->getText();
}

std::any AstBuilder::visitYearMonthIntervalDataType(
    SqlBaseParser::YearMonthIntervalDataTypeContext *context) {
  // TODO proper type struct
  std::string type = "YearMonthInterval: (" + context->from->getText() + ", " +
                     context->to->getText() + ")";
  return type;
}

std::any AstBuilder::visitDayTimeIntervalDataType(
    SqlBaseParser::DayTimeIntervalDataTypeContext *context) {
  // TODO proper type struct
  std::string type = "DayTimeInterval: (" + context->from->getText() + ", " +
                     context->to->getText() + ")";
  return type;
}

std::any AstBuilder::visitPrimitiveDataType(
    SqlBaseParser::PrimitiveDataTypeContext *context) {
  return context->type()->start->getText();
}

std::any AstBuilder::visitQualifiedColTypeWithPositionList(
    SqlBaseParser::QualifiedColTypeWithPositionListContext *context) {
  std::vector<Column> colDefs;
  auto colTypeWithPosition = context->qualifiedColTypeWithPosition();
  colDefs.reserve(colTypeWithPosition.size());
  std::transform(
      colTypeWithPosition.begin(), colTypeWithPosition.end(),
      std::back_inserter(colDefs),
      [this](SqlBaseParser::QualifiedColTypeWithPositionContext *ctx) {
        return std::any_cast<Column>(visitQualifiedColTypeWithPosition(ctx));
      });
  return colDefs;
}

std::any AstBuilder::visitQualifiedColTypeWithPosition(
    SqlBaseParser::QualifiedColTypeWithPositionContext *context) {
  Column colDef;
  auto nameParts = std::any_cast<std::vector<std::string>>(
      context->multipartIdentifier()->accept(this));
  colDef.name = nameParts.empty() ? "" : nameParts.front();
  colDef.dataType = context->dataType()->getText();
  for (const auto &colDefDescriptor :
       context->colDefinitionDescriptorWithPosition()) {
    if (colDefDescriptor->errorCapturingNot() && colDefDescriptor->NULL_()) {
      // Handle NOT NULL case
      colDef.bNullable = false;
    } else if (colDefDescriptor->commentSpec()) {
      // Handle comment specification
      colDef.comment = std::any_cast<std::string>(
          visitCommentSpec(colDefDescriptor->commentSpec()));
    } else if (colDefDescriptor->defaultExpression()) {
      // Handle default expression
      colDef.defaultExpr = std::any_cast<std::string>(
          visitDefaultExpression(colDefDescriptor->defaultExpression()));
    } else if (colDefDescriptor->colPosition()) {
      // Handle column position
      colDef.position = std::any_cast<std::size_t>(
          visitColPosition(colDefDescriptor->colPosition()));
    }
  }
  return colDef;
}

std::any AstBuilder::visitColDefinitionDescriptorWithPosition(
    SqlBaseParser::ColDefinitionDescriptorWithPositionContext *context) {
  return std::any();
}

std::any AstBuilder::visitDefaultExpression(
    SqlBaseParser::DefaultExpressionContext *context) {
  return context->expression()->accept(this);
}

std::any AstBuilder::visitVariableDefaultExpression(
    SqlBaseParser::VariableDefaultExpressionContext *context) {
  return std::any();
}

std::any
AstBuilder::visitColTypeList(SqlBaseParser::ColTypeListContext *context) {
  return std::any();
}

std::any AstBuilder::visitColType(SqlBaseParser::ColTypeContext *context) {
  return std::any();
}

std::any AstBuilder::visitTableElementList(
    SqlBaseParser::TableElementListContext *context) {
  TableElements elements;
  auto tblElemCtx = context->tableElement();
  std::transform(tblElemCtx.begin(), tblElemCtx.end(),
                 std::back_inserter(elements.columnDef),
                 [this](SqlBaseParser::TableElementContext *ctx) {
                   // TODO: table constraint

                   return std::any_cast<Column>(
                       visitColDefinition(ctx->colDefinition()));
                 });
  // TODO: validate only one primary key
  return elements;
}

std::any
AstBuilder::visitTableElement(SqlBaseParser::TableElementContext *context) {
  return visitColDefinition(context->colDefinition());
}

std::any AstBuilder::visitColDefinitionList(
    SqlBaseParser::ColDefinitionListContext *context) {
  return std::any();
}

std::any
AstBuilder::visitColDefinition(SqlBaseParser::ColDefinitionContext *context) {
  Column colDef;
  colDef.name = context->colName->identifier()->getText();
  colDef.dataType =
      std::any_cast<std::string>(context->dataType()->accept(this));
  colDef.bNullable = true;
  std::for_each(context->colDefinitionOption().begin(),
                context->colDefinitionOption().end(),
                [&](SqlBaseParser::ColDefinitionOptionContext *ctx) {
                  if (ctx->NULL_()) {
                    // TODO throw on ! as NOT
                    // TODO validate NOT NULL is not set twice
                    colDef.bNullable = false;
                  }
                  if (ctx->commentSpec()) {
                    // TODO validate comment is not specified twice
                    colDef.comment = std::any_cast<std::string>(
                        visitCommentSpec(ctx->commentSpec()));
                  }
                  // TODO: default expr
                  // TODO: generation expr
                  // TODO: col constraint
                });
  return colDef;
}

std::any AstBuilder::visitColDefinitionOption(
    SqlBaseParser::ColDefinitionOptionContext *context) {
  return std::any();
}

std::any AstBuilder::visitGeneratedColumn(
    SqlBaseParser::GeneratedColumnContext *context) {
  return std::any();
}

std::any
AstBuilder::visitIdentityColumn(SqlBaseParser::IdentityColumnContext *context) {
  return std::any();
}

std::any AstBuilder::visitIdentityColSpec(
    SqlBaseParser::IdentityColSpecContext *context) {
  return std::any();
}

std::any AstBuilder::visitSequenceGeneratorOption(
    SqlBaseParser::SequenceGeneratorOptionContext *context) {
  return std::any();
}

std::any AstBuilder::visitSequenceGeneratorStartOrStep(
    SqlBaseParser::SequenceGeneratorStartOrStepContext *context) {
  return std::any();
}

std::any AstBuilder::visitComplexColTypeList(
    SqlBaseParser::ComplexColTypeListContext *context) {
  return std::any();
}

std::any
AstBuilder::visitComplexColType(SqlBaseParser::ComplexColTypeContext *context) {
  return std::any();
}

std::any AstBuilder::visitRoutineCharacteristics(
    SqlBaseParser::RoutineCharacteristicsContext *context) {
  return std::any();
}

std::any AstBuilder::visitRoutineLanguage(
    SqlBaseParser::RoutineLanguageContext *context) {
  return std::any();
}

std::any
AstBuilder::visitSpecificName(SqlBaseParser::SpecificNameContext *context) {
  return std::any();
}

std::any
AstBuilder::visitDeterministic(SqlBaseParser::DeterministicContext *context) {
  return std::any();
}

std::any
AstBuilder::visitSqlDataAccess(SqlBaseParser::SqlDataAccessContext *context) {
  return std::any();
}

std::any AstBuilder::visitNullCall(SqlBaseParser::NullCallContext *context) {
  return std::any();
}

std::any
AstBuilder::visitRightsClause(SqlBaseParser::RightsClauseContext *context) {
  return std::any();
}

std::any
AstBuilder::visitWhenClause(SqlBaseParser::WhenClauseContext *context) {
  return std::any();
}

std::any
AstBuilder::visitWindowClause(SqlBaseParser::WindowClauseContext *context) {
  return std::any();
}

std::any
AstBuilder::visitNamedWindow(SqlBaseParser::NamedWindowContext *context) {
  return std::any();
}

std::any AstBuilder::visitWindowRef(SqlBaseParser::WindowRefContext *context) {
  return std::any();
}

std::any AstBuilder::visitWindowDef(SqlBaseParser::WindowDefContext *context) {
  return std::any();
}

std::any
AstBuilder::visitWindowFrame(SqlBaseParser::WindowFrameContext *context) {
  return std::any();
}

std::any
AstBuilder::visitFrameBound(SqlBaseParser::FrameBoundContext *context) {
  return std::any();
}

std::any AstBuilder::visitQualifiedNameList(
    SqlBaseParser::QualifiedNameListContext *context) {
  return std::any();
}

std::any
AstBuilder::visitFunctionName(SqlBaseParser::FunctionNameContext *context) {
  return std::any();
}

std::any
AstBuilder::visitQualifiedName(SqlBaseParser::QualifiedNameContext *context) {
  return std::any();
}

std::any AstBuilder::visitErrorCapturingIdentifier(
    SqlBaseParser::ErrorCapturingIdentifierContext *context) {
  return context->identifier()->accept(this);
}

std::any
AstBuilder::visitErrorIdent(SqlBaseParser::ErrorIdentContext *context) {
  return std::any();
}

std::any AstBuilder::visitRealIdent(SqlBaseParser::RealIdentContext *context) {
  return std::any();
}

std::any
AstBuilder::visitIdentifier(SqlBaseParser::IdentifierContext *context) {
  return context->getText();
}

std::any AstBuilder::visitUnquotedIdentifier(
    SqlBaseParser::UnquotedIdentifierContext *context) {
  return std::any();
}

std::any AstBuilder::visitQuotedIdentifierAlternative(
    SqlBaseParser::QuotedIdentifierAlternativeContext *context) {
  return std::any();
}

std::any AstBuilder::visitQuotedIdentifier(
    SqlBaseParser::QuotedIdentifierContext *context) {
  return std::any();
}

std::any AstBuilder::visitBackQuotedIdentifier(
    SqlBaseParser::BackQuotedIdentifierContext *context) {
  return std::any();
}

std::any AstBuilder::visitExponentLiteral(
    SqlBaseParser::ExponentLiteralContext *context) {
  return std::any();
}

std::any
AstBuilder::visitDecimalLiteral(SqlBaseParser::DecimalLiteralContext *context) {
  return std::any();
}

std::any AstBuilder::visitLegacyDecimalLiteral(
    SqlBaseParser::LegacyDecimalLiteralContext *context) {
  return std::any();
}

std::any
AstBuilder::visitIntegerLiteral(SqlBaseParser::IntegerLiteralContext *context) {
  return std::any();
}

std::any
AstBuilder::visitBigIntLiteral(SqlBaseParser::BigIntLiteralContext *context) {
  return std::any();
}

std::any AstBuilder::visitSmallIntLiteral(
    SqlBaseParser::SmallIntLiteralContext *context) {
  return std::any();
}

std::any
AstBuilder::visitTinyIntLiteral(SqlBaseParser::TinyIntLiteralContext *context) {
  return std::any();
}

std::any
AstBuilder::visitDoubleLiteral(SqlBaseParser::DoubleLiteralContext *context) {
  return std::any();
}

std::any
AstBuilder::visitFloatLiteral(SqlBaseParser::FloatLiteralContext *context) {
  return std::any();
}

std::any AstBuilder::visitBigDecimalLiteral(
    SqlBaseParser::BigDecimalLiteralContext *context) {
  return std::any();
}

std::any AstBuilder::visitColumnConstraintDefinition(
    SqlBaseParser::ColumnConstraintDefinitionContext *context) {
  return std::any();
}

std::any AstBuilder::visitColumnConstraint(
    SqlBaseParser::ColumnConstraintContext *context) {
  return std::any();
}

std::any AstBuilder::visitTableConstraintDefinition(
    SqlBaseParser::TableConstraintDefinitionContext *context) {
  return std::any();
}

std::any AstBuilder::visitTableConstraint(
    SqlBaseParser::TableConstraintContext *context) {
  return std::any();
}

std::any AstBuilder::visitCheckConstraint(
    SqlBaseParser::CheckConstraintContext *context) {
  return std::any();
}

std::any
AstBuilder::visitUniqueSpec(SqlBaseParser::UniqueSpecContext *context) {
  return std::any();
}

std::any AstBuilder::visitUniqueConstraint(
    SqlBaseParser::UniqueConstraintContext *context) {
  return std::any();
}

std::any
AstBuilder::visitReferenceSpec(SqlBaseParser::ReferenceSpecContext *context) {
  return std::any();
}

std::any AstBuilder::visitForeignKeyConstraint(
    SqlBaseParser::ForeignKeyConstraintContext *context) {
  return std::any();
}

std::any AstBuilder::visitConstraintCharacteristic(
    SqlBaseParser::ConstraintCharacteristicContext *context) {
  return std::any();
}

std::any AstBuilder::visitEnforcedCharacteristic(
    SqlBaseParser::EnforcedCharacteristicContext *context) {
  return std::any();
}

std::any AstBuilder::visitRelyCharacteristic(
    SqlBaseParser::RelyCharacteristicContext *context) {
  return std::any();
}

std::any AstBuilder::visitAlterColumnSpecList(
    SqlBaseParser::AlterColumnSpecListContext *context) {
  return std::any();
}

std::any AstBuilder::visitAlterColumnSpec(
    SqlBaseParser::AlterColumnSpecContext *context) {
  return std::any();
}

std::any AstBuilder::visitAlterColumnAction(
    SqlBaseParser::AlterColumnActionContext *context) {
  return std::any();
}

std::any AstBuilder::visitStringLit(SqlBaseParser::StringLitContext *context) {
  if (context) {
    if (context->STRING_LITERAL()) {
      auto text = context->STRING_LITERAL()->getSymbol()->getText();
      stripSingleQuotes(text);
      return text;
    } else {
      auto text = context->DOUBLEQUOTED_STRING()->getSymbol()->getText();
      stripDoubleQuotes(text);
      return text;
    }
  } else {
    return std::string();
  }
}

std::any AstBuilder::visitComment(SqlBaseParser::CommentContext *context) {
  return std::any();
}

std::any AstBuilder::visitVersion(SqlBaseParser::VersionContext *context) {
  return std::any();
}

std::any AstBuilder::visitOperatorPipeRightSide(
    SqlBaseParser::OperatorPipeRightSideContext *context) {
  return std::any();
}

std::any AstBuilder::visitOperatorPipeSetAssignmentSeq(
    SqlBaseParser::OperatorPipeSetAssignmentSeqContext *context) {
  return std::any();
}

std::any AstBuilder::visitAnsiNonReserved(
    SqlBaseParser::AnsiNonReservedContext *context) {
  return std::any();
}

std::any AstBuilder::visitStrictNonReserved(
    SqlBaseParser::StrictNonReservedContext *context) {
  return std::any();
}

std::any
AstBuilder::visitNonReserved(SqlBaseParser::NonReservedContext *context) {
  return std::any();
}
