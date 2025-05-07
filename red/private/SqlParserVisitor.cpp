#include "SqlParserVisitor.h"

SqlParserVisitor::SqlParserVisitor() {}

SqlParserVisitor::~SqlParserVisitor() {}

std::any SqlParserVisitor::visitCompoundOrSingleStatement(SqlBaseParser::CompoundOrSingleStatementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSingleCompoundStatement(SqlBaseParser::SingleCompoundStatementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitBeginEndCompoundBlock(SqlBaseParser::BeginEndCompoundBlockContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCompoundBody(SqlBaseParser::CompoundBodyContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCompoundStatement(SqlBaseParser::CompoundStatementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSetVariableWithOptionalKeyword(SqlBaseParser::SetVariableWithOptionalKeywordContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSqlStateValue(SqlBaseParser::SqlStateValueContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDeclareConditionStatement(SqlBaseParser::DeclareConditionStatementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitConditionValue(SqlBaseParser::ConditionValueContext *context) { return std::any(); }

std::any SqlParserVisitor::visitConditionValues(SqlBaseParser::ConditionValuesContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDeclareHandlerStatement(SqlBaseParser::DeclareHandlerStatementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitWhileStatement(SqlBaseParser::WhileStatementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitIfElseStatement(SqlBaseParser::IfElseStatementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRepeatStatement(SqlBaseParser::RepeatStatementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitLeaveStatement(SqlBaseParser::LeaveStatementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitIterateStatement(SqlBaseParser::IterateStatementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSearchedCaseStatement(SqlBaseParser::SearchedCaseStatementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSimpleCaseStatement(SqlBaseParser::SimpleCaseStatementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitLoopStatement(SqlBaseParser::LoopStatementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitForStatement(SqlBaseParser::ForStatementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSingleStatement(SqlBaseParser::SingleStatementContext *context) {
    return context->statement()->accept(this);;
}

std::any SqlParserVisitor::visitBeginLabel(SqlBaseParser::BeginLabelContext *context) { return std::any(); }

std::any SqlParserVisitor::visitEndLabel(SqlBaseParser::EndLabelContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSingleExpression(SqlBaseParser::SingleExpressionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSingleTableIdentifier(SqlBaseParser::SingleTableIdentifierContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSingleMultipartIdentifier(SqlBaseParser::SingleMultipartIdentifierContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSingleFunctionIdentifier(SqlBaseParser::SingleFunctionIdentifierContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSingleDataType(SqlBaseParser::SingleDataTypeContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSingleTableSchema(SqlBaseParser::SingleTableSchemaContext *context) { return std::any(); }

std::any SqlParserVisitor::visitStatementDefault(SqlBaseParser::StatementDefaultContext *context) { return std::any(); }

std::any SqlParserVisitor::visitVisitExecuteImmediate(SqlBaseParser::VisitExecuteImmediateContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDmlStatement(SqlBaseParser::DmlStatementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUse(SqlBaseParser::UseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUseNamespace(SqlBaseParser::UseNamespaceContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSetCatalog(SqlBaseParser::SetCatalogContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCreateNamespace(SqlBaseParser::CreateNamespaceContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSetNamespaceProperties(SqlBaseParser::SetNamespacePropertiesContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUnsetNamespaceProperties(SqlBaseParser::UnsetNamespacePropertiesContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSetNamespaceLocation(SqlBaseParser::SetNamespaceLocationContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDropNamespace(SqlBaseParser::DropNamespaceContext *context) { return std::any(); }

std::any SqlParserVisitor::visitShowNamespaces(SqlBaseParser::ShowNamespacesContext *context) { return std::any(); }

std::any SqlParserVisitor::SqlParserVisitor::visitCreateTable(SqlBaseParser::CreateTableContext *context) {
    auto header = context->createTableHeader();
    auto ident = header->identifierReference();
    return ident->getText();
    
    // auto elem_list = context->tableElementList();
    //     auto col_def = elem->colDefinition();
    //     std::string col_name = col_def->errorCapturingIdentifier()->getText();
    // }
}

std::any SqlParserVisitor::visitCreateTableLike(SqlBaseParser::CreateTableLikeContext *context) { return std::any(); }

std::any SqlParserVisitor::visitReplaceTable(SqlBaseParser::ReplaceTableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAnalyze(SqlBaseParser::AnalyzeContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAnalyzeTables(SqlBaseParser::AnalyzeTablesContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAddTableColumns(SqlBaseParser::AddTableColumnsContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRenameTableColumn(SqlBaseParser::RenameTableColumnContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDropTableColumns(SqlBaseParser::DropTableColumnsContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRenameTable(SqlBaseParser::RenameTableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSetTableProperties(SqlBaseParser::SetTablePropertiesContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUnsetTableProperties(SqlBaseParser::UnsetTablePropertiesContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAlterTableAlterColumn(SqlBaseParser::AlterTableAlterColumnContext *context) { return std::any(); }

std::any SqlParserVisitor::visitHiveChangeColumn(SqlBaseParser::HiveChangeColumnContext *context) { return std::any(); }

std::any SqlParserVisitor::visitHiveReplaceColumns(SqlBaseParser::HiveReplaceColumnsContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSetTableSerDe(SqlBaseParser::SetTableSerDeContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAddTablePartition(SqlBaseParser::AddTablePartitionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRenameTablePartition(SqlBaseParser::RenameTablePartitionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDropTablePartitions(SqlBaseParser::DropTablePartitionsContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSetTableLocation(SqlBaseParser::SetTableLocationContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRecoverPartitions(SqlBaseParser::RecoverPartitionsContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAlterClusterBy(SqlBaseParser::AlterClusterByContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAlterTableCollation(SqlBaseParser::AlterTableCollationContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAddTableConstraint(SqlBaseParser::AddTableConstraintContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDropTableConstraint(SqlBaseParser::DropTableConstraintContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDropTable(SqlBaseParser::DropTableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDropView(SqlBaseParser::DropViewContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCreateView(SqlBaseParser::CreateViewContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCreateTempViewUsing(SqlBaseParser::CreateTempViewUsingContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAlterViewQuery(SqlBaseParser::AlterViewQueryContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAlterViewSchemaBinding(SqlBaseParser::AlterViewSchemaBindingContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCreateFunction(SqlBaseParser::CreateFunctionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCreateUserDefinedFunction(SqlBaseParser::CreateUserDefinedFunctionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDropFunction(SqlBaseParser::DropFunctionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCreateVariable(SqlBaseParser::CreateVariableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDropVariable(SqlBaseParser::DropVariableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitExplain(SqlBaseParser::ExplainContext *context) { return std::any(); }

std::any SqlParserVisitor::visitShowTables(SqlBaseParser::ShowTablesContext *context) { return std::any(); }

std::any SqlParserVisitor::visitShowTableExtended(SqlBaseParser::ShowTableExtendedContext *context) { return std::any(); }

std::any SqlParserVisitor::visitShowTblProperties(SqlBaseParser::ShowTblPropertiesContext *context) { return std::any(); }

std::any SqlParserVisitor::visitShowColumns(SqlBaseParser::ShowColumnsContext *context) { return std::any(); }

std::any SqlParserVisitor::visitShowViews(SqlBaseParser::ShowViewsContext *context) { return std::any(); }

std::any SqlParserVisitor::visitShowPartitions(SqlBaseParser::ShowPartitionsContext *context) { return std::any(); }

std::any SqlParserVisitor::visitShowFunctions(SqlBaseParser::ShowFunctionsContext *context) { return std::any(); }

std::any SqlParserVisitor::visitShowProcedures(SqlBaseParser::ShowProceduresContext *context) { return std::any(); }

std::any SqlParserVisitor::visitShowCreateTable(SqlBaseParser::ShowCreateTableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitShowCurrentNamespace(SqlBaseParser::ShowCurrentNamespaceContext *context) { return std::any(); }

std::any SqlParserVisitor::visitShowCatalogs(SqlBaseParser::ShowCatalogsContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDescribeFunction(SqlBaseParser::DescribeFunctionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDescribeProcedure(SqlBaseParser::DescribeProcedureContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDescribeNamespace(SqlBaseParser::DescribeNamespaceContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDescribeRelation(SqlBaseParser::DescribeRelationContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDescribeQuery(SqlBaseParser::DescribeQueryContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCommentNamespace(SqlBaseParser::CommentNamespaceContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCommentTable(SqlBaseParser::CommentTableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRefreshTable(SqlBaseParser::RefreshTableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRefreshFunction(SqlBaseParser::RefreshFunctionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRefreshResource(SqlBaseParser::RefreshResourceContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCacheTable(SqlBaseParser::CacheTableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUncacheTable(SqlBaseParser::UncacheTableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitClearCache(SqlBaseParser::ClearCacheContext *context) { return std::any(); }

std::any SqlParserVisitor::visitLoadData(SqlBaseParser::LoadDataContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTruncateTable(SqlBaseParser::TruncateTableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRepairTable(SqlBaseParser::RepairTableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitManageResource(SqlBaseParser::ManageResourceContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCreateIndex(SqlBaseParser::CreateIndexContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDropIndex(SqlBaseParser::DropIndexContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCall(SqlBaseParser::CallContext *context) { return std::any(); }

std::any SqlParserVisitor::visitFailNativeCommand(SqlBaseParser::FailNativeCommandContext *context) { return std::any(); }

std::any SqlParserVisitor::visitFailSetRole(SqlBaseParser::FailSetRoleContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSetTimeZone(SqlBaseParser::SetTimeZoneContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSetVariable(SqlBaseParser::SetVariableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSetQuotedConfiguration(SqlBaseParser::SetQuotedConfigurationContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSetConfiguration(SqlBaseParser::SetConfigurationContext *context) { return std::any(); }

std::any SqlParserVisitor::visitResetQuotedConfiguration(SqlBaseParser::ResetQuotedConfigurationContext *context) { return std::any(); }

std::any SqlParserVisitor::visitResetConfiguration(SqlBaseParser::ResetConfigurationContext *context) { return std::any(); }

std::any SqlParserVisitor::visitExecuteImmediate(SqlBaseParser::ExecuteImmediateContext *context) { return std::any(); }

std::any SqlParserVisitor::visitExecuteImmediateUsing(SqlBaseParser::ExecuteImmediateUsingContext *context) { return std::any(); }

std::any SqlParserVisitor::visitExecuteImmediateQueryParam(SqlBaseParser::ExecuteImmediateQueryParamContext *context) { return std::any(); }

std::any SqlParserVisitor::visitExecuteImmediateArgument(SqlBaseParser::ExecuteImmediateArgumentContext *context) { return std::any(); }

std::any SqlParserVisitor::visitExecuteImmediateArgumentSeq(SqlBaseParser::ExecuteImmediateArgumentSeqContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTimezone(SqlBaseParser::TimezoneContext *context) { return std::any(); }

std::any SqlParserVisitor::visitConfigKey(SqlBaseParser::ConfigKeyContext *context) { return std::any(); }

std::any SqlParserVisitor::visitConfigValue(SqlBaseParser::ConfigValueContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUnsupportedHiveNativeCommands(SqlBaseParser::UnsupportedHiveNativeCommandsContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCreateTableHeader(SqlBaseParser::CreateTableHeaderContext *context) { return std::any(); }

std::any SqlParserVisitor::visitReplaceTableHeader(SqlBaseParser::ReplaceTableHeaderContext *context) { return std::any(); }

std::any SqlParserVisitor::visitClusterBySpec(SqlBaseParser::ClusterBySpecContext *context) { return std::any(); }

std::any SqlParserVisitor::visitBucketSpec(SqlBaseParser::BucketSpecContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSkewSpec(SqlBaseParser::SkewSpecContext *context) { return std::any(); }

std::any SqlParserVisitor::visitLocationSpec(SqlBaseParser::LocationSpecContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSchemaBinding(SqlBaseParser::SchemaBindingContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCommentSpec(SqlBaseParser::CommentSpecContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSingleQuery(SqlBaseParser::SingleQueryContext *context) { return std::any(); }

std::any SqlParserVisitor::visitQuery(SqlBaseParser::QueryContext *context) { return std::any(); }

std::any SqlParserVisitor::visitInsertOverwriteTable(SqlBaseParser::InsertOverwriteTableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitInsertIntoTable(SqlBaseParser::InsertIntoTableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitInsertIntoReplaceWhere(SqlBaseParser::InsertIntoReplaceWhereContext *context) { return std::any(); }

std::any SqlParserVisitor::visitInsertOverwriteHiveDir(SqlBaseParser::InsertOverwriteHiveDirContext *context) { return std::any(); }

std::any SqlParserVisitor::visitInsertOverwriteDir(SqlBaseParser::InsertOverwriteDirContext *context) { return std::any(); }

std::any SqlParserVisitor::visitPartitionSpecLocation(SqlBaseParser::PartitionSpecLocationContext *context) { return std::any(); }

std::any SqlParserVisitor::visitPartitionSpec(SqlBaseParser::PartitionSpecContext *context) { return std::any(); }

std::any SqlParserVisitor::visitPartitionVal(SqlBaseParser::PartitionValContext *context) { return std::any(); }

std::any SqlParserVisitor::visitNamespace(SqlBaseParser::NamespaceContext *context) { return std::any(); }

std::any SqlParserVisitor::visitNamespaces(SqlBaseParser::NamespacesContext *context) { return std::any(); }

std::any SqlParserVisitor::visitVariable(SqlBaseParser::VariableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDescribeFuncName(SqlBaseParser::DescribeFuncNameContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDescribeColName(SqlBaseParser::DescribeColNameContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCtes(SqlBaseParser::CtesContext *context) { return std::any(); }

std::any SqlParserVisitor::visitNamedQuery(SqlBaseParser::NamedQueryContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTableProvider(SqlBaseParser::TableProviderContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCreateTableClauses(SqlBaseParser::CreateTableClausesContext *context) { return std::any(); }

std::any SqlParserVisitor::visitPropertyList(SqlBaseParser::PropertyListContext *context) { return std::any(); }

std::any SqlParserVisitor::visitProperty(SqlBaseParser::PropertyContext *context) { return std::any(); }

std::any SqlParserVisitor::visitPropertyKey(SqlBaseParser::PropertyKeyContext *context) { return std::any(); }

std::any SqlParserVisitor::visitPropertyValue(SqlBaseParser::PropertyValueContext *context) { return std::any(); }

std::any SqlParserVisitor::visitExpressionPropertyList(SqlBaseParser::ExpressionPropertyListContext *context) { return std::any(); }

std::any SqlParserVisitor::visitExpressionProperty(SqlBaseParser::ExpressionPropertyContext *context) { return std::any(); }

std::any SqlParserVisitor::visitConstantList(SqlBaseParser::ConstantListContext *context) { return std::any(); }

std::any SqlParserVisitor::visitNestedConstantList(SqlBaseParser::NestedConstantListContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCreateFileFormat(SqlBaseParser::CreateFileFormatContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTableFileFormat(SqlBaseParser::TableFileFormatContext *context) { return std::any(); }

std::any SqlParserVisitor::visitGenericFileFormat(SqlBaseParser::GenericFileFormatContext *context) { return std::any(); }

std::any SqlParserVisitor::visitStorageHandler(SqlBaseParser::StorageHandlerContext *context) { return std::any(); }

std::any SqlParserVisitor::visitResource(SqlBaseParser::ResourceContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSingleInsertQuery(SqlBaseParser::SingleInsertQueryContext *context) { return std::any(); }

std::any SqlParserVisitor::visitMultiInsertQuery(SqlBaseParser::MultiInsertQueryContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDeleteFromTable(SqlBaseParser::DeleteFromTableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUpdateTable(SqlBaseParser::UpdateTableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitMergeIntoTable(SqlBaseParser::MergeIntoTableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitIdentifierReference(SqlBaseParser::IdentifierReferenceContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCatalogIdentifierReference(SqlBaseParser::CatalogIdentifierReferenceContext *context) { return std::any(); }

std::any SqlParserVisitor::visitQueryOrganization(SqlBaseParser::QueryOrganizationContext *context) { return std::any(); }

std::any SqlParserVisitor::visitMultiInsertQueryBody(SqlBaseParser::MultiInsertQueryBodyContext *context) { return std::any(); }

std::any SqlParserVisitor::visitOperatorPipeStatement(SqlBaseParser::OperatorPipeStatementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitQueryTermDefault(SqlBaseParser::QueryTermDefaultContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSetOperation(SqlBaseParser::SetOperationContext *context) { return std::any(); }

std::any SqlParserVisitor::visitQueryPrimaryDefault(SqlBaseParser::QueryPrimaryDefaultContext *context) { return std::any(); }

std::any SqlParserVisitor::visitFromStmt(SqlBaseParser::FromStmtContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTable(SqlBaseParser::TableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitInlineTableDefault1(SqlBaseParser::InlineTableDefault1Context *context) { return std::any(); }

std::any SqlParserVisitor::visitSubquery(SqlBaseParser::SubqueryContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSortItem(SqlBaseParser::SortItemContext *context) { return std::any(); }

std::any SqlParserVisitor::visitFromStatement(SqlBaseParser::FromStatementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitFromStatementBody(SqlBaseParser::FromStatementBodyContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTransformQuerySpecification(SqlBaseParser::TransformQuerySpecificationContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRegularQuerySpecification(SqlBaseParser::RegularQuerySpecificationContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTransformClause(SqlBaseParser::TransformClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSelectClause(SqlBaseParser::SelectClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSetClause(SqlBaseParser::SetClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitMatchedClause(SqlBaseParser::MatchedClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitNotMatchedClause(SqlBaseParser::NotMatchedClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitNotMatchedBySourceClause(SqlBaseParser::NotMatchedBySourceClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitMatchedAction(SqlBaseParser::MatchedActionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitNotMatchedAction(SqlBaseParser::NotMatchedActionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitNotMatchedBySourceAction(SqlBaseParser::NotMatchedBySourceActionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitExceptClause(SqlBaseParser::ExceptClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAssignmentList(SqlBaseParser::AssignmentListContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAssignment(SqlBaseParser::AssignmentContext *context) { return std::any(); }

std::any SqlParserVisitor::visitWhereClause(SqlBaseParser::WhereClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitHavingClause(SqlBaseParser::HavingClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitHint(SqlBaseParser::HintContext *context) { return std::any(); }

std::any SqlParserVisitor::visitHintStatement(SqlBaseParser::HintStatementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitFromClause(SqlBaseParser::FromClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTemporalClause(SqlBaseParser::TemporalClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAggregationClause(SqlBaseParser::AggregationClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitGroupByClause(SqlBaseParser::GroupByClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitGroupingAnalytics(SqlBaseParser::GroupingAnalyticsContext *context) { return std::any(); }

std::any SqlParserVisitor::visitGroupingElement(SqlBaseParser::GroupingElementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitGroupingSet(SqlBaseParser::GroupingSetContext *context) { return std::any(); }

std::any SqlParserVisitor::visitPivotClause(SqlBaseParser::PivotClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitPivotColumn(SqlBaseParser::PivotColumnContext *context) { return std::any(); }

std::any SqlParserVisitor::visitPivotValue(SqlBaseParser::PivotValueContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUnpivotClause(SqlBaseParser::UnpivotClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUnpivotNullClause(SqlBaseParser::UnpivotNullClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUnpivotOperator(SqlBaseParser::UnpivotOperatorContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUnpivotSingleValueColumnClause(SqlBaseParser::UnpivotSingleValueColumnClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUnpivotMultiValueColumnClause(SqlBaseParser::UnpivotMultiValueColumnClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUnpivotColumnSet(SqlBaseParser::UnpivotColumnSetContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUnpivotValueColumn(SqlBaseParser::UnpivotValueColumnContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUnpivotNameColumn(SqlBaseParser::UnpivotNameColumnContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUnpivotColumnAndAlias(SqlBaseParser::UnpivotColumnAndAliasContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUnpivotColumn(SqlBaseParser::UnpivotColumnContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUnpivotAlias(SqlBaseParser::UnpivotAliasContext *context) { return std::any(); }

std::any SqlParserVisitor::visitLateralView(SqlBaseParser::LateralViewContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSetQuantifier(SqlBaseParser::SetQuantifierContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRelation(SqlBaseParser::RelationContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRelationExtension(SqlBaseParser::RelationExtensionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitJoinRelation(SqlBaseParser::JoinRelationContext *context) { return std::any(); }

std::any SqlParserVisitor::visitJoinType(SqlBaseParser::JoinTypeContext *context) { return std::any(); }

std::any SqlParserVisitor::visitJoinCriteria(SqlBaseParser::JoinCriteriaContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSample(SqlBaseParser::SampleContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSampleByPercentile(SqlBaseParser::SampleByPercentileContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSampleByRows(SqlBaseParser::SampleByRowsContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSampleByBucket(SqlBaseParser::SampleByBucketContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSampleByBytes(SqlBaseParser::SampleByBytesContext *context) { return std::any(); }

std::any SqlParserVisitor::visitIdentifierList(SqlBaseParser::IdentifierListContext *context) { return std::any(); }

std::any SqlParserVisitor::visitIdentifierSeq(SqlBaseParser::IdentifierSeqContext *context) { return std::any(); }

std::any SqlParserVisitor::visitOrderedIdentifierList(SqlBaseParser::OrderedIdentifierListContext *context) { return std::any(); }

std::any SqlParserVisitor::visitOrderedIdentifier(SqlBaseParser::OrderedIdentifierContext *context) { return std::any(); }

std::any SqlParserVisitor::visitIdentifierCommentList(SqlBaseParser::IdentifierCommentListContext *context) { return std::any(); }

std::any SqlParserVisitor::visitIdentifierComment(SqlBaseParser::IdentifierCommentContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTableName(SqlBaseParser::TableNameContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAliasedQuery(SqlBaseParser::AliasedQueryContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAliasedRelation(SqlBaseParser::AliasedRelationContext *context) { return std::any(); }

std::any SqlParserVisitor::visitInlineTableDefault2(SqlBaseParser::InlineTableDefault2Context *context) { return std::any(); }

std::any SqlParserVisitor::visitTableValuedFunction(SqlBaseParser::TableValuedFunctionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitOptionsClause(SqlBaseParser::OptionsClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitInlineTable(SqlBaseParser::InlineTableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitFunctionTableSubqueryArgument(SqlBaseParser::FunctionTableSubqueryArgumentContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTableArgumentPartitioning(SqlBaseParser::TableArgumentPartitioningContext *context) { return std::any(); }

std::any SqlParserVisitor::visitFunctionTableNamedArgumentExpression(SqlBaseParser::FunctionTableNamedArgumentExpressionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitFunctionTableReferenceArgument(SqlBaseParser::FunctionTableReferenceArgumentContext *context) { return std::any(); }

std::any SqlParserVisitor::visitFunctionTableArgument(SqlBaseParser::FunctionTableArgumentContext *context) { return std::any(); }

std::any SqlParserVisitor::visitFunctionTable(SqlBaseParser::FunctionTableContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTableAlias(SqlBaseParser::TableAliasContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRowFormatSerde(SqlBaseParser::RowFormatSerdeContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRowFormatDelimited(SqlBaseParser::RowFormatDelimitedContext *context) { return std::any(); }

std::any SqlParserVisitor::visitMultipartIdentifierList(SqlBaseParser::MultipartIdentifierListContext *context) { return std::any(); }

std::any SqlParserVisitor::visitMultipartIdentifier(SqlBaseParser::MultipartIdentifierContext *context) { return std::any(); }

std::any SqlParserVisitor::visitMultipartIdentifierPropertyList(SqlBaseParser::MultipartIdentifierPropertyListContext *context) { return std::any(); }

std::any SqlParserVisitor::visitMultipartIdentifierProperty(SqlBaseParser::MultipartIdentifierPropertyContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTableIdentifier(SqlBaseParser::TableIdentifierContext *context) { return std::any(); }

std::any SqlParserVisitor::visitFunctionIdentifier(SqlBaseParser::FunctionIdentifierContext *context) { return std::any(); }

std::any SqlParserVisitor::visitNamedExpression(SqlBaseParser::NamedExpressionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitNamedExpressionSeq(SqlBaseParser::NamedExpressionSeqContext *context) { return std::any(); }

std::any SqlParserVisitor::visitPartitionFieldList(SqlBaseParser::PartitionFieldListContext *context) { return std::any(); }

std::any SqlParserVisitor::visitPartitionTransform(SqlBaseParser::PartitionTransformContext *context) { return std::any(); }

std::any SqlParserVisitor::visitPartitionColumn(SqlBaseParser::PartitionColumnContext *context) { return std::any(); }

std::any SqlParserVisitor::visitIdentityTransform(SqlBaseParser::IdentityTransformContext *context) { return std::any(); }

std::any SqlParserVisitor::visitApplyTransform(SqlBaseParser::ApplyTransformContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTransformArgument(SqlBaseParser::TransformArgumentContext *context) { return std::any(); }

std::any SqlParserVisitor::visitExpression(SqlBaseParser::ExpressionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitNamedArgumentExpression(SqlBaseParser::NamedArgumentExpressionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitFunctionArgument(SqlBaseParser::FunctionArgumentContext *context) { return std::any(); }

std::any SqlParserVisitor::visitExpressionSeq(SqlBaseParser::ExpressionSeqContext *context) { return std::any(); }

std::any SqlParserVisitor::visitLogicalNot(SqlBaseParser::LogicalNotContext *context) { return std::any(); }

std::any SqlParserVisitor::visitPredicated(SqlBaseParser::PredicatedContext *context) { return std::any(); }

std::any SqlParserVisitor::visitExists(SqlBaseParser::ExistsContext *context) { return std::any(); }

std::any SqlParserVisitor::visitLogicalBinary(SqlBaseParser::LogicalBinaryContext *context) { return std::any(); }

std::any SqlParserVisitor::visitPredicate(SqlBaseParser::PredicateContext *context) { return std::any(); }

std::any SqlParserVisitor::visitErrorCapturingNot(SqlBaseParser::ErrorCapturingNotContext *context) { return std::any(); }

std::any SqlParserVisitor::visitValueExpressionDefault(SqlBaseParser::ValueExpressionDefaultContext *context) { return std::any(); }

std::any SqlParserVisitor::visitComparison(SqlBaseParser::ComparisonContext *context) { return std::any(); }

std::any SqlParserVisitor::visitShiftExpression(SqlBaseParser::ShiftExpressionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitArithmeticBinary(SqlBaseParser::ArithmeticBinaryContext *context) { return std::any(); }

std::any SqlParserVisitor::visitArithmeticUnary(SqlBaseParser::ArithmeticUnaryContext *context) { return std::any(); }

std::any SqlParserVisitor::visitShiftOperator(SqlBaseParser::ShiftOperatorContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDatetimeUnit(SqlBaseParser::DatetimeUnitContext *context) { return std::any(); }

std::any SqlParserVisitor::visitStruct(SqlBaseParser::StructContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDereference(SqlBaseParser::DereferenceContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCastByColon(SqlBaseParser::CastByColonContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTimestampadd(SqlBaseParser::TimestampaddContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSubstring(SqlBaseParser::SubstringContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCast(SqlBaseParser::CastContext *context) { return std::any(); }

std::any SqlParserVisitor::visitLambda(SqlBaseParser::LambdaContext *context) { return std::any(); }

std::any SqlParserVisitor::visitParenthesizedExpression(SqlBaseParser::ParenthesizedExpressionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAny_value(SqlBaseParser::Any_valueContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTrim(SqlBaseParser::TrimContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSimpleCase(SqlBaseParser::SimpleCaseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCurrentLike(SqlBaseParser::CurrentLikeContext *context) { return std::any(); }

std::any SqlParserVisitor::visitColumnReference(SqlBaseParser::ColumnReferenceContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRowConstructor(SqlBaseParser::RowConstructorContext *context) { return std::any(); }

std::any SqlParserVisitor::visitLast(SqlBaseParser::LastContext *context) { return std::any(); }

std::any SqlParserVisitor::visitStar(SqlBaseParser::StarContext *context) { return std::any(); }

std::any SqlParserVisitor::visitOverlay(SqlBaseParser::OverlayContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSubscript(SqlBaseParser::SubscriptContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTimestampdiff(SqlBaseParser::TimestampdiffContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSubqueryExpression(SqlBaseParser::SubqueryExpressionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCollate(SqlBaseParser::CollateContext *context) { return std::any(); }

std::any SqlParserVisitor::visitConstantDefault(SqlBaseParser::ConstantDefaultContext *context) { return std::any(); }

std::any SqlParserVisitor::visitExtract(SqlBaseParser::ExtractContext *context) { return std::any(); }

std::any SqlParserVisitor::visitFunctionCall(SqlBaseParser::FunctionCallContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSearchedCase(SqlBaseParser::SearchedCaseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitPosition(SqlBaseParser::PositionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitFirst(SqlBaseParser::FirstContext *context) { return std::any(); }

std::any SqlParserVisitor::visitLiteralType(SqlBaseParser::LiteralTypeContext *context) { return std::any(); }

std::any SqlParserVisitor::visitNullLiteral(SqlBaseParser::NullLiteralContext *context) { return std::any(); }

std::any SqlParserVisitor::visitPosParameterLiteral(SqlBaseParser::PosParameterLiteralContext *context) { return std::any(); }

std::any SqlParserVisitor::visitNamedParameterLiteral(SqlBaseParser::NamedParameterLiteralContext *context) { return std::any(); }

std::any SqlParserVisitor::visitIntervalLiteral(SqlBaseParser::IntervalLiteralContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTypeConstructor(SqlBaseParser::TypeConstructorContext *context) { return std::any(); }

std::any SqlParserVisitor::visitNumericLiteral(SqlBaseParser::NumericLiteralContext *context) { return std::any(); }

std::any SqlParserVisitor::visitBooleanLiteral(SqlBaseParser::BooleanLiteralContext *context) { return std::any(); }

std::any SqlParserVisitor::visitStringLiteral(SqlBaseParser::StringLiteralContext *context) { return std::any(); }

std::any SqlParserVisitor::visitComparisonOperator(SqlBaseParser::ComparisonOperatorContext *context) { return std::any(); }

std::any SqlParserVisitor::visitArithmeticOperator(SqlBaseParser::ArithmeticOperatorContext *context) { return std::any(); }

std::any SqlParserVisitor::visitPredicateOperator(SqlBaseParser::PredicateOperatorContext *context) { return std::any(); }

std::any SqlParserVisitor::visitBooleanValue(SqlBaseParser::BooleanValueContext *context) { return std::any(); }

std::any SqlParserVisitor::visitInterval(SqlBaseParser::IntervalContext *context) { return std::any(); }

std::any SqlParserVisitor::visitErrorCapturingMultiUnitsInterval(SqlBaseParser::ErrorCapturingMultiUnitsIntervalContext *context) { return std::any(); }

std::any SqlParserVisitor::visitMultiUnitsInterval(SqlBaseParser::MultiUnitsIntervalContext *context) { return std::any(); }

std::any SqlParserVisitor::visitErrorCapturingUnitToUnitInterval(SqlBaseParser::ErrorCapturingUnitToUnitIntervalContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUnitToUnitInterval(SqlBaseParser::UnitToUnitIntervalContext *context) { return std::any(); }

std::any SqlParserVisitor::visitIntervalValue(SqlBaseParser::IntervalValueContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUnitInMultiUnits(SqlBaseParser::UnitInMultiUnitsContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUnitInUnitToUnit(SqlBaseParser::UnitInUnitToUnitContext *context) { return std::any(); }

std::any SqlParserVisitor::visitColPosition(SqlBaseParser::ColPositionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCollationSpec(SqlBaseParser::CollationSpecContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCollateClause(SqlBaseParser::CollateClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitType(SqlBaseParser::TypeContext *context) { return std::any(); }

std::any SqlParserVisitor::visitComplexDataType(SqlBaseParser::ComplexDataTypeContext *context) { return std::any(); }

std::any SqlParserVisitor::visitYearMonthIntervalDataType(SqlBaseParser::YearMonthIntervalDataTypeContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDayTimeIntervalDataType(SqlBaseParser::DayTimeIntervalDataTypeContext *context) { return std::any(); }

std::any SqlParserVisitor::visitPrimitiveDataType(SqlBaseParser::PrimitiveDataTypeContext *context) { return std::any(); }

std::any SqlParserVisitor::visitQualifiedColTypeWithPositionList(SqlBaseParser::QualifiedColTypeWithPositionListContext *context) { return std::any(); }

std::any SqlParserVisitor::visitQualifiedColTypeWithPosition(SqlBaseParser::QualifiedColTypeWithPositionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitColDefinitionDescriptorWithPosition(SqlBaseParser::ColDefinitionDescriptorWithPositionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDefaultExpression(SqlBaseParser::DefaultExpressionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitVariableDefaultExpression(SqlBaseParser::VariableDefaultExpressionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitColTypeList(SqlBaseParser::ColTypeListContext *context) { return std::any(); }

std::any SqlParserVisitor::visitColType(SqlBaseParser::ColTypeContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTableElementList(SqlBaseParser::TableElementListContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTableElement(SqlBaseParser::TableElementContext *context) { return std::any(); }

std::any SqlParserVisitor::visitColDefinitionList(SqlBaseParser::ColDefinitionListContext *context) { return std::any(); }

std::any SqlParserVisitor::visitColDefinition(SqlBaseParser::ColDefinitionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitColDefinitionOption(SqlBaseParser::ColDefinitionOptionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitGeneratedColumn(SqlBaseParser::GeneratedColumnContext *context) { return std::any(); }

std::any SqlParserVisitor::visitIdentityColumn(SqlBaseParser::IdentityColumnContext *context) { return std::any(); }

std::any SqlParserVisitor::visitIdentityColSpec(SqlBaseParser::IdentityColSpecContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSequenceGeneratorOption(SqlBaseParser::SequenceGeneratorOptionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSequenceGeneratorStartOrStep(SqlBaseParser::SequenceGeneratorStartOrStepContext *context) { return std::any(); }

std::any SqlParserVisitor::visitComplexColTypeList(SqlBaseParser::ComplexColTypeListContext *context) { return std::any(); }

std::any SqlParserVisitor::visitComplexColType(SqlBaseParser::ComplexColTypeContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRoutineCharacteristics(SqlBaseParser::RoutineCharacteristicsContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRoutineLanguage(SqlBaseParser::RoutineLanguageContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSpecificName(SqlBaseParser::SpecificNameContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDeterministic(SqlBaseParser::DeterministicContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSqlDataAccess(SqlBaseParser::SqlDataAccessContext *context) { return std::any(); }

std::any SqlParserVisitor::visitNullCall(SqlBaseParser::NullCallContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRightsClause(SqlBaseParser::RightsClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitWhenClause(SqlBaseParser::WhenClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitWindowClause(SqlBaseParser::WindowClauseContext *context) { return std::any(); }

std::any SqlParserVisitor::visitNamedWindow(SqlBaseParser::NamedWindowContext *context) { return std::any(); }

std::any SqlParserVisitor::visitWindowRef(SqlBaseParser::WindowRefContext *context) { return std::any(); }

std::any SqlParserVisitor::visitWindowDef(SqlBaseParser::WindowDefContext *context) { return std::any(); }

std::any SqlParserVisitor::visitWindowFrame(SqlBaseParser::WindowFrameContext *context) { return std::any(); }

std::any SqlParserVisitor::visitFrameBound(SqlBaseParser::FrameBoundContext *context) { return std::any(); }

std::any SqlParserVisitor::visitQualifiedNameList(SqlBaseParser::QualifiedNameListContext *context) { return std::any(); }

std::any SqlParserVisitor::visitFunctionName(SqlBaseParser::FunctionNameContext *context) { return std::any(); }

std::any SqlParserVisitor::visitQualifiedName(SqlBaseParser::QualifiedNameContext *context) { return std::any(); }

std::any SqlParserVisitor::visitErrorCapturingIdentifier(SqlBaseParser::ErrorCapturingIdentifierContext *context) { return std::any(); }

std::any SqlParserVisitor::visitErrorIdent(SqlBaseParser::ErrorIdentContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRealIdent(SqlBaseParser::RealIdentContext *context) { return std::any(); }

std::any SqlParserVisitor::visitIdentifier(SqlBaseParser::IdentifierContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUnquotedIdentifier(SqlBaseParser::UnquotedIdentifierContext *context) { return std::any(); }

std::any SqlParserVisitor::visitQuotedIdentifierAlternative(SqlBaseParser::QuotedIdentifierAlternativeContext *context) { return std::any(); }

std::any SqlParserVisitor::visitQuotedIdentifier(SqlBaseParser::QuotedIdentifierContext *context) { return std::any(); }

std::any SqlParserVisitor::visitBackQuotedIdentifier(SqlBaseParser::BackQuotedIdentifierContext *context) { return std::any(); }

std::any SqlParserVisitor::visitExponentLiteral(SqlBaseParser::ExponentLiteralContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDecimalLiteral(SqlBaseParser::DecimalLiteralContext *context) { return std::any(); }

std::any SqlParserVisitor::visitLegacyDecimalLiteral(SqlBaseParser::LegacyDecimalLiteralContext *context) { return std::any(); }

std::any SqlParserVisitor::visitIntegerLiteral(SqlBaseParser::IntegerLiteralContext *context) { return std::any(); }

std::any SqlParserVisitor::visitBigIntLiteral(SqlBaseParser::BigIntLiteralContext *context) { return std::any(); }

std::any SqlParserVisitor::visitSmallIntLiteral(SqlBaseParser::SmallIntLiteralContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTinyIntLiteral(SqlBaseParser::TinyIntLiteralContext *context) { return std::any(); }

std::any SqlParserVisitor::visitDoubleLiteral(SqlBaseParser::DoubleLiteralContext *context) { return std::any(); }

std::any SqlParserVisitor::visitFloatLiteral(SqlBaseParser::FloatLiteralContext *context) { return std::any(); }

std::any SqlParserVisitor::visitBigDecimalLiteral(SqlBaseParser::BigDecimalLiteralContext *context) { return std::any(); }

std::any SqlParserVisitor::visitColumnConstraintDefinition(SqlBaseParser::ColumnConstraintDefinitionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitColumnConstraint(SqlBaseParser::ColumnConstraintContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTableConstraintDefinition(SqlBaseParser::TableConstraintDefinitionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitTableConstraint(SqlBaseParser::TableConstraintContext *context) { return std::any(); }

std::any SqlParserVisitor::visitCheckConstraint(SqlBaseParser::CheckConstraintContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUniqueSpec(SqlBaseParser::UniqueSpecContext *context) { return std::any(); }

std::any SqlParserVisitor::visitUniqueConstraint(SqlBaseParser::UniqueConstraintContext *context) { return std::any(); }

std::any SqlParserVisitor::visitReferenceSpec(SqlBaseParser::ReferenceSpecContext *context) { return std::any(); }

std::any SqlParserVisitor::visitForeignKeyConstraint(SqlBaseParser::ForeignKeyConstraintContext *context) { return std::any(); }

std::any SqlParserVisitor::visitConstraintCharacteristic(SqlBaseParser::ConstraintCharacteristicContext *context) { return std::any(); }

std::any SqlParserVisitor::visitEnforcedCharacteristic(SqlBaseParser::EnforcedCharacteristicContext *context) { return std::any(); }

std::any SqlParserVisitor::visitRelyCharacteristic(SqlBaseParser::RelyCharacteristicContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAlterColumnSpecList(SqlBaseParser::AlterColumnSpecListContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAlterColumnSpec(SqlBaseParser::AlterColumnSpecContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAlterColumnAction(SqlBaseParser::AlterColumnActionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitStringLit(SqlBaseParser::StringLitContext *context) { return std::any(); }

std::any SqlParserVisitor::visitComment(SqlBaseParser::CommentContext *context) { return std::any(); }

std::any SqlParserVisitor::visitVersion(SqlBaseParser::VersionContext *context) { return std::any(); }

std::any SqlParserVisitor::visitOperatorPipeRightSide(SqlBaseParser::OperatorPipeRightSideContext *context) { return std::any(); }

std::any SqlParserVisitor::visitOperatorPipeSetAssignmentSeq(SqlBaseParser::OperatorPipeSetAssignmentSeqContext *context) { return std::any(); }

std::any SqlParserVisitor::visitAnsiNonReserved(SqlBaseParser::AnsiNonReservedContext *context) { return std::any(); }

std::any SqlParserVisitor::visitStrictNonReserved(SqlBaseParser::StrictNonReservedContext *context) { return std::any(); }

std::any SqlParserVisitor::visitNonReserved(SqlBaseParser::NonReservedContext *context) { return std::any(); }
