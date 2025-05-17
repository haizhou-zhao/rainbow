#include "InMemoryCatalog.h"
#include "SqlPlan.h"

void InMemoryCatalog::createTable(std::shared_ptr<ResolvedIdentifier> identifier)
{
    std::string database;
    std::string table;
    if (identifier->nameParts.size() == 1) {
        database = DEFAULT_DATABASE;
        table = identifier->nameParts[0];
    } else if (identifier->nameParts.size() == 2) {
        database = identifier->nameParts[0];
        table = identifier->nameParts[1];
    } else {
        //TODO: throw exception
    }
    catalogMemory[database].insert(table);
}
