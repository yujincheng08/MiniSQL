#include "RecordManager.h"

File &RecordManager::OpenTableFile(const std::string &tableName) {
    return BufferManager::open(tableName + ".tbl");
}

void RecordManager::CreateTable(const std::string &tableName) {
    File &file = RecordManager::OpenTableFile(tableName);

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

std::pair<File::pos_type, File::pos_type> RecordManager::InsertRecord(const std::string &tableName, File::pos_type lastWritePos, File::pos_type firstInvalidPos, Record record) {
    auto &file = RecordManager::OpenTableFile(tableName);
    
    File::pos_type nextPos;
    if (firstInvalidPos == 0xffffffff) {
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
        nextPos = file.tellg() + 1;
    } else {
        nextPos = firstInvalidPos;
        bool valid;
        file.seekg(firstInvalidPos);
        file >> valid;
        file >> firstInvalidPos;
    }
    
    // valid
    file << true;
    file << 0xffffffff;
    // get the positionof the record
    for (auto &column : record) {
        auto type = column.type();
        auto &rawData = *(column.name());
        if (type == Column::Int) {
            int data = std::stoi(rawData);
            file << data;
        } else if (type == Column::Float) {
            float data = std::stof(rawData);
            file << data;
        } else if (type <= 1 && type <Column::Int) {
            FixString data(rawData);
            file << data;
        } else {
            // Undefined should not happen
        }
    }

    // write this position to last valid record

    return std::pair<File::pos_type, File::pos_type>(nextPos, firstInvalidPos);
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
