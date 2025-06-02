#pragma once
#include "SqlBaseParser.h"
#include "SqlBaseParserVisitor.h"
#include "SqlPlan.h"

using namespace sqlgrammar;

class AstBuilder : public SqlBaseParserVisitor {
private:
  struct CreateTableHeader {
    SqlBaseParser::IdentifierReferenceContext *identifierRefCtx;
    bool bIsTemporary;
    bool bIfNotExist;
    bool bIsExternal;
  };

  struct TableElements {
    std::vector<ColumnDef> columnDef;
    // std::vector<TableConstraint> tableConstraint;
  };

  void stripSingleQuotes(std::string &s) const;

  void stripDoubleQuotes(std::string &s) const;

public:
  AstBuilder(/* args */);
  ~AstBuilder();

  std::any visitCompoundOrSingleStatement(
      SqlBaseParser::CompoundOrSingleStatementContext *context);

  std::any visitSingleCompoundStatement(
      SqlBaseParser::SingleCompoundStatementContext *context);

  std::any visitBeginEndCompoundBlock(
      SqlBaseParser::BeginEndCompoundBlockContext *context);

  std::any visitCompoundBody(SqlBaseParser::CompoundBodyContext *context);

  std::any
  visitCompoundStatement(SqlBaseParser::CompoundStatementContext *context);

  std::any visitSetVariableWithOptionalKeyword(
      SqlBaseParser::SetVariableWithOptionalKeywordContext *context);

  std::any visitSqlStateValue(SqlBaseParser::SqlStateValueContext *context);

  std::any visitDeclareConditionStatement(
      SqlBaseParser::DeclareConditionStatementContext *context);

  std::any visitConditionValue(SqlBaseParser::ConditionValueContext *context);

  std::any visitConditionValues(SqlBaseParser::ConditionValuesContext *context);

  std::any visitDeclareHandlerStatement(
      SqlBaseParser::DeclareHandlerStatementContext *context);

  std::any visitWhileStatement(SqlBaseParser::WhileStatementContext *context);

  std::any visitIfElseStatement(SqlBaseParser::IfElseStatementContext *context);

  std::any visitRepeatStatement(SqlBaseParser::RepeatStatementContext *context);

  std::any visitLeaveStatement(SqlBaseParser::LeaveStatementContext *context);

  std::any
  visitIterateStatement(SqlBaseParser::IterateStatementContext *context);

  std::any visitSearchedCaseStatement(
      SqlBaseParser::SearchedCaseStatementContext *context);

  std::any
  visitSimpleCaseStatement(SqlBaseParser::SimpleCaseStatementContext *context);

  std::any visitLoopStatement(SqlBaseParser::LoopStatementContext *context);

  std::any visitForStatement(SqlBaseParser::ForStatementContext *context);

  std::any visitSingleStatement(SqlBaseParser::SingleStatementContext *context);

  std::any visitBeginLabel(SqlBaseParser::BeginLabelContext *context);

  std::any visitEndLabel(SqlBaseParser::EndLabelContext *context);

  std::any
  visitSingleExpression(SqlBaseParser::SingleExpressionContext *context);

  std::any visitSingleTableIdentifier(
      SqlBaseParser::SingleTableIdentifierContext *context);

  std::any visitSingleMultipartIdentifier(
      SqlBaseParser::SingleMultipartIdentifierContext *context);

  std::any visitSingleFunctionIdentifier(
      SqlBaseParser::SingleFunctionIdentifierContext *context);

  std::any visitSingleDataType(SqlBaseParser::SingleDataTypeContext *context);

  std::any
  visitSingleTableSchema(SqlBaseParser::SingleTableSchemaContext *context);

  std::any
  visitStatementDefault(SqlBaseParser::StatementDefaultContext *context);

  std::any visitVisitExecuteImmediate(
      SqlBaseParser::VisitExecuteImmediateContext *context);

  std::any visitDmlStatement(SqlBaseParser::DmlStatementContext *context);

  std::any visitUse(SqlBaseParser::UseContext *context);

  std::any visitUseNamespace(SqlBaseParser::UseNamespaceContext *context);

  std::any visitSetCatalog(SqlBaseParser::SetCatalogContext *context);

  std::any visitCreateNamespace(SqlBaseParser::CreateNamespaceContext *context);

  std::any visitSetNamespaceProperties(
      SqlBaseParser::SetNamespacePropertiesContext *context);

  std::any visitUnsetNamespaceProperties(
      SqlBaseParser::UnsetNamespacePropertiesContext *context);

  std::any visitSetNamespaceLocation(
      SqlBaseParser::SetNamespaceLocationContext *context);

  std::any visitDropNamespace(SqlBaseParser::DropNamespaceContext *context);

  std::any visitShowNamespaces(SqlBaseParser::ShowNamespacesContext *context);

  std::any visitCreateTable(SqlBaseParser::CreateTableContext *context);

  std::any visitCreateTableLike(SqlBaseParser::CreateTableLikeContext *context);

  std::any visitReplaceTable(SqlBaseParser::ReplaceTableContext *context);

  std::any visitAnalyze(SqlBaseParser::AnalyzeContext *context);

  std::any visitAnalyzeTables(SqlBaseParser::AnalyzeTablesContext *context);

  std::any visitAddTableColumns(SqlBaseParser::AddTableColumnsContext *context);

  std::any
  visitRenameTableColumn(SqlBaseParser::RenameTableColumnContext *context);

  std::any
  visitDropTableColumns(SqlBaseParser::DropTableColumnsContext *context);

  std::any visitRenameTable(SqlBaseParser::RenameTableContext *context);

  std::any
  visitSetTableProperties(SqlBaseParser::SetTablePropertiesContext *context);

  std::any visitUnsetTableProperties(
      SqlBaseParser::UnsetTablePropertiesContext *context);

  std::any visitAlterTableAlterColumn(
      SqlBaseParser::AlterTableAlterColumnContext *context);

  std::any
  visitHiveChangeColumn(SqlBaseParser::HiveChangeColumnContext *context);

  std::any
  visitHiveReplaceColumns(SqlBaseParser::HiveReplaceColumnsContext *context);

  std::any visitSetTableSerDe(SqlBaseParser::SetTableSerDeContext *context);

  std::any
  visitAddTablePartition(SqlBaseParser::AddTablePartitionContext *context);

  std::any visitRenameTablePartition(
      SqlBaseParser::RenameTablePartitionContext *context);

  std::any
  visitDropTablePartitions(SqlBaseParser::DropTablePartitionsContext *context);

  std::any
  visitSetTableLocation(SqlBaseParser::SetTableLocationContext *context);

  std::any
  visitRecoverPartitions(SqlBaseParser::RecoverPartitionsContext *context);

  std::any visitAlterClusterBy(SqlBaseParser::AlterClusterByContext *context);

  std::any
  visitAlterTableCollation(SqlBaseParser::AlterTableCollationContext *context);

  std::any
  visitAddTableConstraint(SqlBaseParser::AddTableConstraintContext *context);

  std::any
  visitDropTableConstraint(SqlBaseParser::DropTableConstraintContext *context);

  std::any visitDropTable(SqlBaseParser::DropTableContext *context);

  std::any visitDropView(SqlBaseParser::DropViewContext *context);

  std::any visitCreateView(SqlBaseParser::CreateViewContext *context);

  std::any
  visitCreateTempViewUsing(SqlBaseParser::CreateTempViewUsingContext *context);

  std::any visitAlterViewQuery(SqlBaseParser::AlterViewQueryContext *context);

  std::any visitAlterViewSchemaBinding(
      SqlBaseParser::AlterViewSchemaBindingContext *context);

  std::any visitCreateFunction(SqlBaseParser::CreateFunctionContext *context);

  std::any visitCreateUserDefinedFunction(
      SqlBaseParser::CreateUserDefinedFunctionContext *context);

  std::any visitDropFunction(SqlBaseParser::DropFunctionContext *context);

  std::any visitCreateVariable(SqlBaseParser::CreateVariableContext *context);

  std::any visitDropVariable(SqlBaseParser::DropVariableContext *context);

  std::any visitExplain(SqlBaseParser::ExplainContext *context);

  std::any visitShowTables(SqlBaseParser::ShowTablesContext *context);

  std::any
  visitShowTableExtended(SqlBaseParser::ShowTableExtendedContext *context);

  std::any
  visitShowTblProperties(SqlBaseParser::ShowTblPropertiesContext *context);

  std::any visitShowColumns(SqlBaseParser::ShowColumnsContext *context);

  std::any visitShowViews(SqlBaseParser::ShowViewsContext *context);

  std::any visitShowPartitions(SqlBaseParser::ShowPartitionsContext *context);

  std::any visitShowFunctions(SqlBaseParser::ShowFunctionsContext *context);

  std::any visitShowProcedures(SqlBaseParser::ShowProceduresContext *context);

  std::any visitShowCreateTable(SqlBaseParser::ShowCreateTableContext *context);

  std::any visitShowCurrentNamespace(
      SqlBaseParser::ShowCurrentNamespaceContext *context);

  std::any visitShowCatalogs(SqlBaseParser::ShowCatalogsContext *context);

  std::any
  visitDescribeFunction(SqlBaseParser::DescribeFunctionContext *context);

  std::any
  visitDescribeProcedure(SqlBaseParser::DescribeProcedureContext *context);

  std::any
  visitDescribeNamespace(SqlBaseParser::DescribeNamespaceContext *context);

  std::any
  visitDescribeRelation(SqlBaseParser::DescribeRelationContext *context);

  std::any visitDescribeQuery(SqlBaseParser::DescribeQueryContext *context);

  std::any
  visitCommentNamespace(SqlBaseParser::CommentNamespaceContext *context);

  std::any visitCommentTable(SqlBaseParser::CommentTableContext *context);

  std::any visitRefreshTable(SqlBaseParser::RefreshTableContext *context);

  std::any visitRefreshFunction(SqlBaseParser::RefreshFunctionContext *context);

  std::any visitRefreshResource(SqlBaseParser::RefreshResourceContext *context);

  std::any visitCacheTable(SqlBaseParser::CacheTableContext *context);

  std::any visitUncacheTable(SqlBaseParser::UncacheTableContext *context);

  std::any visitClearCache(SqlBaseParser::ClearCacheContext *context);

  std::any visitLoadData(SqlBaseParser::LoadDataContext *context);

  std::any visitTruncateTable(SqlBaseParser::TruncateTableContext *context);

  std::any visitRepairTable(SqlBaseParser::RepairTableContext *context);

  std::any visitManageResource(SqlBaseParser::ManageResourceContext *context);

  std::any visitCreateIndex(SqlBaseParser::CreateIndexContext *context);

  std::any visitDropIndex(SqlBaseParser::DropIndexContext *context);

  std::any visitCall(SqlBaseParser::CallContext *context);

  std::any
  visitFailNativeCommand(SqlBaseParser::FailNativeCommandContext *context);

  std::any visitFailSetRole(SqlBaseParser::FailSetRoleContext *context);

  std::any visitSetTimeZone(SqlBaseParser::SetTimeZoneContext *context);

  std::any visitSetVariable(SqlBaseParser::SetVariableContext *context);

  std::any visitSetQuotedConfiguration(
      SqlBaseParser::SetQuotedConfigurationContext *context);

  std::any
  visitSetConfiguration(SqlBaseParser::SetConfigurationContext *context);

  std::any visitResetQuotedConfiguration(
      SqlBaseParser::ResetQuotedConfigurationContext *context);

  std::any
  visitResetConfiguration(SqlBaseParser::ResetConfigurationContext *context);

  std::any
  visitExecuteImmediate(SqlBaseParser::ExecuteImmediateContext *context);

  std::any visitExecuteImmediateUsing(
      SqlBaseParser::ExecuteImmediateUsingContext *context);

  std::any visitExecuteImmediateQueryParam(
      SqlBaseParser::ExecuteImmediateQueryParamContext *context);

  std::any visitExecuteImmediateArgument(
      SqlBaseParser::ExecuteImmediateArgumentContext *context);

  std::any visitExecuteImmediateArgumentSeq(
      SqlBaseParser::ExecuteImmediateArgumentSeqContext *context);

  std::any visitTimezone(SqlBaseParser::TimezoneContext *context);

  std::any visitConfigKey(SqlBaseParser::ConfigKeyContext *context);

  std::any visitConfigValue(SqlBaseParser::ConfigValueContext *context);

  std::any visitUnsupportedHiveNativeCommands(
      SqlBaseParser::UnsupportedHiveNativeCommandsContext *context);

  std::any
  visitCreateTableHeader(SqlBaseParser::CreateTableHeaderContext *context);

  std::any
  visitReplaceTableHeader(SqlBaseParser::ReplaceTableHeaderContext *context);

  std::any visitClusterBySpec(SqlBaseParser::ClusterBySpecContext *context);

  std::any visitBucketSpec(SqlBaseParser::BucketSpecContext *context);

  std::any visitSkewSpec(SqlBaseParser::SkewSpecContext *context);

  std::any visitLocationSpec(SqlBaseParser::LocationSpecContext *context);

  std::any visitSchemaBinding(SqlBaseParser::SchemaBindingContext *context);

  std::any visitCommentSpec(SqlBaseParser::CommentSpecContext *context);

  std::any visitSingleQuery(SqlBaseParser::SingleQueryContext *context);

  std::any visitQuery(SqlBaseParser::QueryContext *context);

  std::any visitInsertOverwriteTable(
      SqlBaseParser::InsertOverwriteTableContext *context);

  std::any visitInsertIntoTable(SqlBaseParser::InsertIntoTableContext *context);

  std::any visitInsertIntoReplaceWhere(
      SqlBaseParser::InsertIntoReplaceWhereContext *context);

  std::any visitInsertOverwriteHiveDir(
      SqlBaseParser::InsertOverwriteHiveDirContext *context);

  std::any
  visitInsertOverwriteDir(SqlBaseParser::InsertOverwriteDirContext *context);

  std::any visitPartitionSpecLocation(
      SqlBaseParser::PartitionSpecLocationContext *context);

  std::any visitPartitionSpec(SqlBaseParser::PartitionSpecContext *context);

  std::any visitPartitionVal(SqlBaseParser::PartitionValContext *context);

  std::any visitNamespace(SqlBaseParser::NamespaceContext *context);

  std::any visitNamespaces(SqlBaseParser::NamespacesContext *context);

  std::any visitVariable(SqlBaseParser::VariableContext *context);

  std::any
  visitDescribeFuncName(SqlBaseParser::DescribeFuncNameContext *context);

  std::any visitDescribeColName(SqlBaseParser::DescribeColNameContext *context);

  std::any visitCtes(SqlBaseParser::CtesContext *context);

  std::any visitNamedQuery(SqlBaseParser::NamedQueryContext *context);

  std::any visitTableProvider(SqlBaseParser::TableProviderContext *context);

  std::any
  visitCreateTableClauses(SqlBaseParser::CreateTableClausesContext *context);

  std::any visitPropertyList(SqlBaseParser::PropertyListContext *context);

  std::any visitProperty(SqlBaseParser::PropertyContext *context);

  std::any visitPropertyKey(SqlBaseParser::PropertyKeyContext *context);

  std::any visitPropertyValue(SqlBaseParser::PropertyValueContext *context);

  std::any visitExpressionPropertyList(
      SqlBaseParser::ExpressionPropertyListContext *context);

  std::any
  visitExpressionProperty(SqlBaseParser::ExpressionPropertyContext *context);

  std::any visitConstantList(SqlBaseParser::ConstantListContext *context);

  std::any
  visitNestedConstantList(SqlBaseParser::NestedConstantListContext *context);

  std::any
  visitCreateFileFormat(SqlBaseParser::CreateFileFormatContext *context);

  std::any visitTableFileFormat(SqlBaseParser::TableFileFormatContext *context);

  std::any
  visitGenericFileFormat(SqlBaseParser::GenericFileFormatContext *context);

  std::any visitStorageHandler(SqlBaseParser::StorageHandlerContext *context);

  std::any visitResource(SqlBaseParser::ResourceContext *context);

  std::any
  visitSingleInsertQuery(SqlBaseParser::SingleInsertQueryContext *context);

  std::any
  visitMultiInsertQuery(SqlBaseParser::MultiInsertQueryContext *context);

  std::any visitDeleteFromTable(SqlBaseParser::DeleteFromTableContext *context);

  std::any visitUpdateTable(SqlBaseParser::UpdateTableContext *context);

  std::any visitMergeIntoTable(SqlBaseParser::MergeIntoTableContext *context);

  std::any
  visitIdentifierReference(SqlBaseParser::IdentifierReferenceContext *context);

  std::any visitCatalogIdentifierReference(
      SqlBaseParser::CatalogIdentifierReferenceContext *context);

  std::any
  visitQueryOrganization(SqlBaseParser::QueryOrganizationContext *context);

  std::any visitMultiInsertQueryBody(
      SqlBaseParser::MultiInsertQueryBodyContext *context);

  std::any visitOperatorPipeStatement(
      SqlBaseParser::OperatorPipeStatementContext *context);

  std::any
  visitQueryTermDefault(SqlBaseParser::QueryTermDefaultContext *context);

  std::any visitSetOperation(SqlBaseParser::SetOperationContext *context);

  std::any
  visitQueryPrimaryDefault(SqlBaseParser::QueryPrimaryDefaultContext *context);

  std::any visitFromStmt(SqlBaseParser::FromStmtContext *context);

  std::any visitTable(SqlBaseParser::TableContext *context);

  std::any
  visitInlineTableDefault1(SqlBaseParser::InlineTableDefault1Context *context);

  std::any visitSubquery(SqlBaseParser::SubqueryContext *context);

  std::any visitSortItem(SqlBaseParser::SortItemContext *context);

  std::any visitFromStatement(SqlBaseParser::FromStatementContext *context);

  std::any
  visitFromStatementBody(SqlBaseParser::FromStatementBodyContext *context);

  std::any visitTransformQuerySpecification(
      SqlBaseParser::TransformQuerySpecificationContext *context);

  std::any visitRegularQuerySpecification(
      SqlBaseParser::RegularQuerySpecificationContext *context);

  std::any visitTransformClause(SqlBaseParser::TransformClauseContext *context);

  std::any visitSelectClause(SqlBaseParser::SelectClauseContext *context);

  std::any visitSetClause(SqlBaseParser::SetClauseContext *context);

  std::any visitMatchedClause(SqlBaseParser::MatchedClauseContext *context);

  std::any
  visitNotMatchedClause(SqlBaseParser::NotMatchedClauseContext *context);

  std::any visitNotMatchedBySourceClause(
      SqlBaseParser::NotMatchedBySourceClauseContext *context);

  std::any visitMatchedAction(SqlBaseParser::MatchedActionContext *context);

  std::any
  visitNotMatchedAction(SqlBaseParser::NotMatchedActionContext *context);

  std::any visitNotMatchedBySourceAction(
      SqlBaseParser::NotMatchedBySourceActionContext *context);

  std::any visitExceptClause(SqlBaseParser::ExceptClauseContext *context);

  std::any visitAssignmentList(SqlBaseParser::AssignmentListContext *context);

  std::any visitAssignment(SqlBaseParser::AssignmentContext *context);

  std::any visitWhereClause(SqlBaseParser::WhereClauseContext *context);

  std::any visitHavingClause(SqlBaseParser::HavingClauseContext *context);

  std::any visitHint(SqlBaseParser::HintContext *context);

  std::any visitHintStatement(SqlBaseParser::HintStatementContext *context);

  std::any visitFromClause(SqlBaseParser::FromClauseContext *context);

  std::any visitTemporalClause(SqlBaseParser::TemporalClauseContext *context);

  std::any
  visitAggregationClause(SqlBaseParser::AggregationClauseContext *context);

  std::any visitGroupByClause(SqlBaseParser::GroupByClauseContext *context);

  std::any
  visitGroupingAnalytics(SqlBaseParser::GroupingAnalyticsContext *context);

  std::any visitGroupingElement(SqlBaseParser::GroupingElementContext *context);

  std::any visitGroupingSet(SqlBaseParser::GroupingSetContext *context);

  std::any visitPivotClause(SqlBaseParser::PivotClauseContext *context);

  std::any visitPivotColumn(SqlBaseParser::PivotColumnContext *context);

  std::any visitPivotValue(SqlBaseParser::PivotValueContext *context);

  std::any visitUnpivotClause(SqlBaseParser::UnpivotClauseContext *context);

  std::any
  visitUnpivotNullClause(SqlBaseParser::UnpivotNullClauseContext *context);

  std::any visitUnpivotOperator(SqlBaseParser::UnpivotOperatorContext *context);

  std::any visitUnpivotSingleValueColumnClause(
      SqlBaseParser::UnpivotSingleValueColumnClauseContext *context);

  std::any visitUnpivotMultiValueColumnClause(
      SqlBaseParser::UnpivotMultiValueColumnClauseContext *context);

  std::any
  visitUnpivotColumnSet(SqlBaseParser::UnpivotColumnSetContext *context);

  std::any
  visitUnpivotValueColumn(SqlBaseParser::UnpivotValueColumnContext *context);

  std::any
  visitUnpivotNameColumn(SqlBaseParser::UnpivotNameColumnContext *context);

  std::any visitUnpivotColumnAndAlias(
      SqlBaseParser::UnpivotColumnAndAliasContext *context);

  std::any visitUnpivotColumn(SqlBaseParser::UnpivotColumnContext *context);

  std::any visitUnpivotAlias(SqlBaseParser::UnpivotAliasContext *context);

  std::any visitLateralView(SqlBaseParser::LateralViewContext *context);

  std::any visitSetQuantifier(SqlBaseParser::SetQuantifierContext *context);

  std::any visitRelation(SqlBaseParser::RelationContext *context);

  std::any
  visitRelationExtension(SqlBaseParser::RelationExtensionContext *context);

  std::any visitJoinRelation(SqlBaseParser::JoinRelationContext *context);

  std::any visitJoinType(SqlBaseParser::JoinTypeContext *context);

  std::any visitJoinCriteria(SqlBaseParser::JoinCriteriaContext *context);

  std::any visitSample(SqlBaseParser::SampleContext *context);

  std::any
  visitSampleByPercentile(SqlBaseParser::SampleByPercentileContext *context);

  std::any visitSampleByRows(SqlBaseParser::SampleByRowsContext *context);

  std::any visitSampleByBucket(SqlBaseParser::SampleByBucketContext *context);

  std::any visitSampleByBytes(SqlBaseParser::SampleByBytesContext *context);

  std::any visitIdentifierList(SqlBaseParser::IdentifierListContext *context);

  std::any visitIdentifierSeq(SqlBaseParser::IdentifierSeqContext *context);

  std::any visitOrderedIdentifierList(
      SqlBaseParser::OrderedIdentifierListContext *context);

  std::any
  visitOrderedIdentifier(SqlBaseParser::OrderedIdentifierContext *context);

  std::any visitIdentifierCommentList(
      SqlBaseParser::IdentifierCommentListContext *context);

  std::any
  visitIdentifierComment(SqlBaseParser::IdentifierCommentContext *context);

  std::any visitTableName(SqlBaseParser::TableNameContext *context);

  std::any visitAliasedQuery(SqlBaseParser::AliasedQueryContext *context);

  std::any visitAliasedRelation(SqlBaseParser::AliasedRelationContext *context);

  std::any
  visitInlineTableDefault2(SqlBaseParser::InlineTableDefault2Context *context);

  std::any
  visitTableValuedFunction(SqlBaseParser::TableValuedFunctionContext *context);

  std::any visitOptionsClause(SqlBaseParser::OptionsClauseContext *context);

  std::any visitInlineTable(SqlBaseParser::InlineTableContext *context);

  std::any visitFunctionTableSubqueryArgument(
      SqlBaseParser::FunctionTableSubqueryArgumentContext *context);

  std::any visitTableArgumentPartitioning(
      SqlBaseParser::TableArgumentPartitioningContext *context);

  std::any visitFunctionTableNamedArgumentExpression(
      SqlBaseParser::FunctionTableNamedArgumentExpressionContext *context);

  std::any visitFunctionTableReferenceArgument(
      SqlBaseParser::FunctionTableReferenceArgumentContext *context);

  std::any visitFunctionTableArgument(
      SqlBaseParser::FunctionTableArgumentContext *context);

  std::any visitFunctionTable(SqlBaseParser::FunctionTableContext *context);

  std::any visitTableAlias(SqlBaseParser::TableAliasContext *context);

  std::any visitRowFormatSerde(SqlBaseParser::RowFormatSerdeContext *context);

  std::any
  visitRowFormatDelimited(SqlBaseParser::RowFormatDelimitedContext *context);

  std::any visitMultipartIdentifierList(
      SqlBaseParser::MultipartIdentifierListContext *context);

  std::any
  visitMultipartIdentifier(SqlBaseParser::MultipartIdentifierContext *context);

  std::any visitMultipartIdentifierPropertyList(
      SqlBaseParser::MultipartIdentifierPropertyListContext *context);

  std::any visitMultipartIdentifierProperty(
      SqlBaseParser::MultipartIdentifierPropertyContext *context);

  std::any visitTableIdentifier(SqlBaseParser::TableIdentifierContext *context);

  std::any
  visitFunctionIdentifier(SqlBaseParser::FunctionIdentifierContext *context);

  std::any visitNamedExpression(SqlBaseParser::NamedExpressionContext *context);

  std::any
  visitNamedExpressionSeq(SqlBaseParser::NamedExpressionSeqContext *context);

  std::any
  visitPartitionFieldList(SqlBaseParser::PartitionFieldListContext *context);

  std::any
  visitPartitionTransform(SqlBaseParser::PartitionTransformContext *context);

  std::any visitPartitionColumn(SqlBaseParser::PartitionColumnContext *context);

  std::any
  visitIdentityTransform(SqlBaseParser::IdentityTransformContext *context);

  std::any visitApplyTransform(SqlBaseParser::ApplyTransformContext *context);

  std::any
  visitTransformArgument(SqlBaseParser::TransformArgumentContext *context);

  std::any visitExpression(SqlBaseParser::ExpressionContext *context);

  std::any visitNamedArgumentExpression(
      SqlBaseParser::NamedArgumentExpressionContext *context);

  std::any
  visitFunctionArgument(SqlBaseParser::FunctionArgumentContext *context);

  std::any visitExpressionSeq(SqlBaseParser::ExpressionSeqContext *context);

  std::any visitLogicalNot(SqlBaseParser::LogicalNotContext *context);

  std::any visitPredicated(SqlBaseParser::PredicatedContext *context);

  std::any visitExists(SqlBaseParser::ExistsContext *context);

  std::any visitLogicalBinary(SqlBaseParser::LogicalBinaryContext *context);

  std::any visitPredicate(SqlBaseParser::PredicateContext *context);

  std::any
  visitErrorCapturingNot(SqlBaseParser::ErrorCapturingNotContext *context);

  std::any visitValueExpressionDefault(
      SqlBaseParser::ValueExpressionDefaultContext *context);

  std::any visitComparison(SqlBaseParser::ComparisonContext *context);

  std::any visitShiftExpression(SqlBaseParser::ShiftExpressionContext *context);

  std::any
  visitArithmeticBinary(SqlBaseParser::ArithmeticBinaryContext *context);

  std::any visitArithmeticUnary(SqlBaseParser::ArithmeticUnaryContext *context);

  std::any visitShiftOperator(SqlBaseParser::ShiftOperatorContext *context);

  std::any visitDatetimeUnit(SqlBaseParser::DatetimeUnitContext *context);

  std::any visitStruct(SqlBaseParser::StructContext *context);

  std::any visitDereference(SqlBaseParser::DereferenceContext *context);

  std::any visitCastByColon(SqlBaseParser::CastByColonContext *context);

  std::any visitTimestampadd(SqlBaseParser::TimestampaddContext *context);

  std::any visitSubstring(SqlBaseParser::SubstringContext *context);

  std::any visitCast(SqlBaseParser::CastContext *context);

  std::any visitLambda(SqlBaseParser::LambdaContext *context);

  std::any visitParenthesizedExpression(
      SqlBaseParser::ParenthesizedExpressionContext *context);

  std::any visitAny_value(SqlBaseParser::Any_valueContext *context);

  std::any visitTrim(SqlBaseParser::TrimContext *context);

  std::any visitSimpleCase(SqlBaseParser::SimpleCaseContext *context);

  std::any visitCurrentLike(SqlBaseParser::CurrentLikeContext *context);

  std::any visitColumnReference(SqlBaseParser::ColumnReferenceContext *context);

  std::any visitRowConstructor(SqlBaseParser::RowConstructorContext *context);

  std::any visitLast(SqlBaseParser::LastContext *context);

  std::any visitStar(SqlBaseParser::StarContext *context);

  std::any visitOverlay(SqlBaseParser::OverlayContext *context);

  std::any visitSubscript(SqlBaseParser::SubscriptContext *context);

  std::any visitTimestampdiff(SqlBaseParser::TimestampdiffContext *context);

  std::any
  visitSubqueryExpression(SqlBaseParser::SubqueryExpressionContext *context);

  std::any visitCollate(SqlBaseParser::CollateContext *context);

  std::any visitConstantDefault(SqlBaseParser::ConstantDefaultContext *context);

  std::any visitExtract(SqlBaseParser::ExtractContext *context);

  std::any visitFunctionCall(SqlBaseParser::FunctionCallContext *context);

  std::any visitSearchedCase(SqlBaseParser::SearchedCaseContext *context);

  std::any visitPosition(SqlBaseParser::PositionContext *context);

  std::any visitFirst(SqlBaseParser::FirstContext *context);

  std::any visitLiteralType(SqlBaseParser::LiteralTypeContext *context);

  std::any visitNullLiteral(SqlBaseParser::NullLiteralContext *context);

  std::any
  visitPosParameterLiteral(SqlBaseParser::PosParameterLiteralContext *context);

  std::any visitNamedParameterLiteral(
      SqlBaseParser::NamedParameterLiteralContext *context);

  std::any visitIntervalLiteral(SqlBaseParser::IntervalLiteralContext *context);

  std::any visitTypeConstructor(SqlBaseParser::TypeConstructorContext *context);

  std::any visitNumericLiteral(SqlBaseParser::NumericLiteralContext *context);

  std::any visitBooleanLiteral(SqlBaseParser::BooleanLiteralContext *context);

  std::any visitStringLiteral(SqlBaseParser::StringLiteralContext *context);

  std::any
  visitComparisonOperator(SqlBaseParser::ComparisonOperatorContext *context);

  std::any
  visitArithmeticOperator(SqlBaseParser::ArithmeticOperatorContext *context);

  std::any
  visitPredicateOperator(SqlBaseParser::PredicateOperatorContext *context);

  std::any visitBooleanValue(SqlBaseParser::BooleanValueContext *context);

  std::any visitInterval(SqlBaseParser::IntervalContext *context);

  std::any visitErrorCapturingMultiUnitsInterval(
      SqlBaseParser::ErrorCapturingMultiUnitsIntervalContext *context);

  std::any
  visitMultiUnitsInterval(SqlBaseParser::MultiUnitsIntervalContext *context);

  std::any visitErrorCapturingUnitToUnitInterval(
      SqlBaseParser::ErrorCapturingUnitToUnitIntervalContext *context);

  std::any
  visitUnitToUnitInterval(SqlBaseParser::UnitToUnitIntervalContext *context);

  std::any visitIntervalValue(SqlBaseParser::IntervalValueContext *context);

  std::any
  visitUnitInMultiUnits(SqlBaseParser::UnitInMultiUnitsContext *context);

  std::any
  visitUnitInUnitToUnit(SqlBaseParser::UnitInUnitToUnitContext *context);

  std::any visitColPosition(SqlBaseParser::ColPositionContext *context);

  std::any visitCollationSpec(SqlBaseParser::CollationSpecContext *context);

  std::any visitCollateClause(SqlBaseParser::CollateClauseContext *context);

  std::any visitType(SqlBaseParser::TypeContext *context);

  std::any visitComplexDataType(SqlBaseParser::ComplexDataTypeContext *context);

  std::any visitYearMonthIntervalDataType(
      SqlBaseParser::YearMonthIntervalDataTypeContext *context);

  std::any visitDayTimeIntervalDataType(
      SqlBaseParser::DayTimeIntervalDataTypeContext *context);

  std::any
  visitPrimitiveDataType(SqlBaseParser::PrimitiveDataTypeContext *context);

  std::any visitQualifiedColTypeWithPositionList(
      SqlBaseParser::QualifiedColTypeWithPositionListContext *context);

  std::any visitQualifiedColTypeWithPosition(
      SqlBaseParser::QualifiedColTypeWithPositionContext *context);

  std::any visitColDefinitionDescriptorWithPosition(
      SqlBaseParser::ColDefinitionDescriptorWithPositionContext *context);

  std::any
  visitDefaultExpression(SqlBaseParser::DefaultExpressionContext *context);

  std::any visitVariableDefaultExpression(
      SqlBaseParser::VariableDefaultExpressionContext *context);

  std::any visitColTypeList(SqlBaseParser::ColTypeListContext *context);

  std::any visitColType(SqlBaseParser::ColTypeContext *context);

  std::any
  visitTableElementList(SqlBaseParser::TableElementListContext *context);

  std::any visitTableElement(SqlBaseParser::TableElementContext *context);

  std::any
  visitColDefinitionList(SqlBaseParser::ColDefinitionListContext *context);

  std::any visitColDefinition(SqlBaseParser::ColDefinitionContext *context);

  std::any
  visitColDefinitionOption(SqlBaseParser::ColDefinitionOptionContext *context);

  std::any visitGeneratedColumn(SqlBaseParser::GeneratedColumnContext *context);

  std::any visitIdentityColumn(SqlBaseParser::IdentityColumnContext *context);

  std::any visitIdentityColSpec(SqlBaseParser::IdentityColSpecContext *context);

  std::any visitSequenceGeneratorOption(
      SqlBaseParser::SequenceGeneratorOptionContext *context);

  std::any visitSequenceGeneratorStartOrStep(
      SqlBaseParser::SequenceGeneratorStartOrStepContext *context);

  std::any
  visitComplexColTypeList(SqlBaseParser::ComplexColTypeListContext *context);

  std::any visitComplexColType(SqlBaseParser::ComplexColTypeContext *context);

  std::any visitRoutineCharacteristics(
      SqlBaseParser::RoutineCharacteristicsContext *context);

  std::any visitRoutineLanguage(SqlBaseParser::RoutineLanguageContext *context);

  std::any visitSpecificName(SqlBaseParser::SpecificNameContext *context);

  std::any visitDeterministic(SqlBaseParser::DeterministicContext *context);

  std::any visitSqlDataAccess(SqlBaseParser::SqlDataAccessContext *context);

  std::any visitNullCall(SqlBaseParser::NullCallContext *context);

  std::any visitRightsClause(SqlBaseParser::RightsClauseContext *context);

  std::any visitWhenClause(SqlBaseParser::WhenClauseContext *context);

  std::any visitWindowClause(SqlBaseParser::WindowClauseContext *context);

  std::any visitNamedWindow(SqlBaseParser::NamedWindowContext *context);

  std::any visitWindowRef(SqlBaseParser::WindowRefContext *context);

  std::any visitWindowDef(SqlBaseParser::WindowDefContext *context);

  std::any visitWindowFrame(SqlBaseParser::WindowFrameContext *context);

  std::any visitFrameBound(SqlBaseParser::FrameBoundContext *context);

  std::any
  visitQualifiedNameList(SqlBaseParser::QualifiedNameListContext *context);

  std::any visitFunctionName(SqlBaseParser::FunctionNameContext *context);

  std::any visitQualifiedName(SqlBaseParser::QualifiedNameContext *context);

  std::any visitErrorCapturingIdentifier(
      SqlBaseParser::ErrorCapturingIdentifierContext *context);

  std::any visitErrorIdent(SqlBaseParser::ErrorIdentContext *context);

  std::any visitRealIdent(SqlBaseParser::RealIdentContext *context);

  std::any visitIdentifier(SqlBaseParser::IdentifierContext *context);

  std::any
  visitUnquotedIdentifier(SqlBaseParser::UnquotedIdentifierContext *context);

  std::any visitQuotedIdentifierAlternative(
      SqlBaseParser::QuotedIdentifierAlternativeContext *context);

  std::any
  visitQuotedIdentifier(SqlBaseParser::QuotedIdentifierContext *context);

  std::any visitBackQuotedIdentifier(
      SqlBaseParser::BackQuotedIdentifierContext *context);

  std::any visitExponentLiteral(SqlBaseParser::ExponentLiteralContext *context);

  std::any visitDecimalLiteral(SqlBaseParser::DecimalLiteralContext *context);

  std::any visitLegacyDecimalLiteral(
      SqlBaseParser::LegacyDecimalLiteralContext *context);

  std::any visitIntegerLiteral(SqlBaseParser::IntegerLiteralContext *context);

  std::any visitBigIntLiteral(SqlBaseParser::BigIntLiteralContext *context);

  std::any visitSmallIntLiteral(SqlBaseParser::SmallIntLiteralContext *context);

  std::any visitTinyIntLiteral(SqlBaseParser::TinyIntLiteralContext *context);

  std::any visitDoubleLiteral(SqlBaseParser::DoubleLiteralContext *context);

  std::any visitFloatLiteral(SqlBaseParser::FloatLiteralContext *context);

  std::any
  visitBigDecimalLiteral(SqlBaseParser::BigDecimalLiteralContext *context);

  std::any visitColumnConstraintDefinition(
      SqlBaseParser::ColumnConstraintDefinitionContext *context);

  std::any
  visitColumnConstraint(SqlBaseParser::ColumnConstraintContext *context);

  std::any visitTableConstraintDefinition(
      SqlBaseParser::TableConstraintDefinitionContext *context);

  std::any visitTableConstraint(SqlBaseParser::TableConstraintContext *context);

  std::any visitCheckConstraint(SqlBaseParser::CheckConstraintContext *context);

  std::any visitUniqueSpec(SqlBaseParser::UniqueSpecContext *context);

  std::any
  visitUniqueConstraint(SqlBaseParser::UniqueConstraintContext *context);

  std::any visitReferenceSpec(SqlBaseParser::ReferenceSpecContext *context);

  std::any visitForeignKeyConstraint(
      SqlBaseParser::ForeignKeyConstraintContext *context);

  std::any visitConstraintCharacteristic(
      SqlBaseParser::ConstraintCharacteristicContext *context);

  std::any visitEnforcedCharacteristic(
      SqlBaseParser::EnforcedCharacteristicContext *context);

  std::any
  visitRelyCharacteristic(SqlBaseParser::RelyCharacteristicContext *context);

  std::any
  visitAlterColumnSpecList(SqlBaseParser::AlterColumnSpecListContext *context);

  std::any visitAlterColumnSpec(SqlBaseParser::AlterColumnSpecContext *context);

  std::any
  visitAlterColumnAction(SqlBaseParser::AlterColumnActionContext *context);

  std::any visitStringLit(SqlBaseParser::StringLitContext *context);

  std::any visitComment(SqlBaseParser::CommentContext *context);

  std::any visitVersion(SqlBaseParser::VersionContext *context);

  std::any visitOperatorPipeRightSide(
      SqlBaseParser::OperatorPipeRightSideContext *context);

  std::any visitOperatorPipeSetAssignmentSeq(
      SqlBaseParser::OperatorPipeSetAssignmentSeqContext *context);

  std::any visitAnsiNonReserved(SqlBaseParser::AnsiNonReservedContext *context);

  std::any
  visitStrictNonReserved(SqlBaseParser::StrictNonReservedContext *context);

  std::any visitNonReserved(SqlBaseParser::NonReservedContext *context);
};
