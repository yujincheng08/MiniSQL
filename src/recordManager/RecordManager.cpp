#include "RecordManager.h"

File &RecordManager::OpenTableFile(const std::string &tableName) {
    return BufferManager::open(tableName + ".tbl");
}

void RecordManager::FlushTableFile(const std::string &tableName) {
    RecordManager::OpenTableFile(tableName).flush();
}

void RecordManager::CreateTable(const std::string &tableName) {
    File &file = RecordManager::OpenTableFile(tableName);
    file.seekp(0);
    File::pos_type invalid = 0xffffffff;
    // last write record and first invalid
    file << invalid << invalid;
    // if both invalid it's initail empty state
    file.flush();
}

void RecordManager::DropTable(const std::string &tableName) {
    // use File class delete method
    auto &file = RecordManager::OpenTableFile(tableName);
    file.remove();
}

bool RecordManager::DeleteRecords(const std::string &tableName, std::vector<File::pos_type> positions) {
    File &file = RecordManager::OpenTableFile(tableName);
}

void RecordManager::InsertRecord(const std::string &tableName, Record record) {
    auto &file = RecordManager::OpenTableFile(tableName);
    File::pos_type lastWritePos, firstInvalidPos;
    file.seekg(0);
    file >> lastWritePos >> firstInvalidPos;
    File::pos_type nextPos;
    if (firstInvalidPos == 0xffffffff) {
        if (lastWritePos == 0xffffffff) {
            // empty initial

        } else {
            // seek to the next write position
            file.seekg(lastWritePos);
            // seek to end
            for (auto &column : record) {
                auto type = column.type();
                auto &rawData = *(column.name());
                if (type == Column::Int) {
                    int data = std::stoi(rawData);
                    file >> data;
                } else if (type == Column::Float) {
                    float data = std::stof(rawData);
                    file >> data;
                } else if (type <= 1 && type < Column::Int) {
                    FixString data(RecordManager::getColumnSize(column));
                     file >> data;
                } else {
                }
            }
        }
        nextPos = file.tellg() + 1;
    } else {
        nextPos = firstInvalidPos;
        bool valid;
        file.seekg(firstInvalidPos);
        file >> valid >> firstInvalidPos;
        file.seekp(0);
        // will be cover later
        file << lastWritePos;
        // write back
        file << firstInvalidPos;
    }

    if (lastWritePos != 0xffffffff) {
        // link this to last
        file.seekp(lastWritePos);
        file << true << nextPos;
    }

    // write lastWrite to file
    file.seekp(0);
    file << nextPos;
    file.seekp(nextPos);
    // valid
    // means end of valid list
    File::pos_type invalid = 0xffffffff;
    file << true << invalid;
    for (auto &column : record) {
        auto type = column.type();
        auto &rawData = *(column.name());
        if (type == Column::Int) {
            int data = std::stoi(rawData);
            file << data;
        } else if (type == Column::Float) {
            float data = std::stof(rawData);
            file << data;
        } else if (1 <= type && type < Column::Int) {
            FixString data(rawData);
            file << data;
        } else {
            // Undefined should not happen
        }
    }
}

std::vector<RecordManager::Record> RecordManager::queryRecordsByOffsets(const std::string &tableName, std::vector<File::pos_type> offsets, RecordManager::Record templateRecord) {

}

std::vector<File::pos_type> RecordManager::queryRecordsOffsets(const std::string &tableName, int recordSize) {

}

RecordManager::Record RecordManager::makeTestRecord() {
    Column intCol;
    intCol.ColumnType = Column::Int;
    intCol.Name = std::make_shared<std::string>("42");
    Column floatCol;
    floatCol.ColumnType = Column::Float;
    floatCol.Name = std::make_shared<std::string>("3.141592");
    Column charCol;
    charCol.ColumnType = 7;
    charCol.Name = std::make_shared<std::string>("1234567");
    Record record = {intCol, floatCol, charCol};
    return record;
}

 int RecordManager::getColumnSize(const Column& col) {
     if (col.type() >= 256) {
         // int or float
         return 4;
     } else {
         // it's char 0 ~255
         return col.type();
     }
 }

 int RecordManager::getRecordSize(const Record &record) {
     int size = 0;
     for(const auto &col : record) {
         size += RecordManager::getColumnSize(col);
     }
     return size;
 }
