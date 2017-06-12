#include "RecordManager.h"
#include <QCoreApplication>

void testInsert(const std::string &tableName) {
        auto Record = RecordManager::makeTestRecord();
        RecordManager::DropTable(tableName);
        RecordManager::CreateTable(tableName);
        for (int i = 0; i < 10; i++) {
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
        File::pos_type lastWritePos, firstInvalidPos, maxPos, nextPos = 120;
        file.seekg(0);
        // 0xfffffff, 0xfffffff, 0
        file >> lastWritePos >> firstInvalidPos >> maxPos;

        // for test
        file.seekg(0);
        // 0xfffffff, 0xfffffff, 0
        file >> lastWritePos >> firstInvalidPos >> maxPos;
        // write lastWrite to file
        file.seekp(0);
        // should only change lastWritePos
        file << nextPos;
        // for test
        file.seekg(0);
        // 120, 0 <- bug, 0
        file >> lastWritePos >> firstInvalidPos >> maxPos;
        file.seekg(8);
        // 120 <- bug
        file >> firstInvalidPos;

}

int main(int argc, char *argv[]) {
    std::string tableName("test");
    QCoreApplication app(argc, argv);

  //  testWriteFile(tableName);
//    testWriteFile(tableName);
    testInsert(tableName);
    return app.exec();
}
