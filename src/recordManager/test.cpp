#include "RecordManager.h"
int main(int argc, char *argv[]) {
    std::string tableName("test");
    auto Record = RecordManager::makeTestRecord();
    RecordManager::CreateTable(tableName);

    RecordManager::DropTable(tableName);
    return 0;
}
