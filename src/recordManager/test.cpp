#include "RecordManager.h"
#include <QCoreApplication>

void testInsert(const std::string &tableName) {
        auto Record = RecordManager::makeTestRecord();
        RecordManager::DropTable(tableName);
        RecordManager::CreateTable(tableName);
        for (int i = 0; i < 30; i++) {
            RecordManager::InsertRecord(tableName, Record);
        }
        RecordManager::FlushTableFile(tableName);
        auto offset= RecordManager::queryRecordsOffsets(tableName);
        auto records = RecordManager::queryRecordsByOffsets(tableName, offset, Record);
        auto metaData = RecordManager::getMetaData(tableName);
        for (auto &record: records) {
            for(auto &column: record) {
                std::cout << *column.name() << "\n";
            }
        }
}

void testWriteFile(const std::string &tableName) {
        RecordManager::DropTable(tableName);
        RecordManager::CreateTable(tableName);
        auto &file = BufferManager::open(tableName + ".tbl");

        //auto record = RecordManager::makeTestRecord();
        file.seekp(0);
        for (int i = 0; i < 400; i++) {

        }

}

int main(int argc, char *argv[]) {
    std::string tableName("test");
    QCoreApplication app(argc, argv);

  //  testWriteFile(tableName);
//    testWriteFile(tableName);
    testInsert(tableName);
    return app.exec();
}
