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
    // last write record, first invalid
    file << invalid << invalid;
    invalid  = 0;
    // max addr valid reford
    file << invalid;
    invalid = 0xffffffff;
    file << invalid;
    // lastWritePos, firstInvalidPos, maxPos, firstValidPos
    // if both invalid it's initail empty state
}

void RecordManager::DropTable(const std::string &tableName) {
    // use File class delete method
    auto &file = RecordManager::OpenTableFile(tableName);
    file.remove();
}

void RecordManager::DeleteRecords(const std::string &tableName, std::vector<File::pos_type> positions) {
    auto metaData = RecordManager::getMetaData(tableName);
    auto &lastValid = std::get<0>(metaData);
    auto &firstInvalid = std::get<1>(metaData);
    auto &firstValid = std::get<3>(metaData);
    File &file = RecordManager::OpenTableFile(tableName);
    for (auto &offset : positions) {
        if (offset == lastValid) {
            // delete this from tail
            File::pos_type previousValid;
            file.seekg(offset);
            file.get<bool>();
            file >> previousValid;
            lastValid = previousValid;
        }
        if (offset == firstValid) {
            // delete this from head
            File::pos_type nextValid;
            file.seekg(offset);
            file.get<bool>();
            file.get<File::pos_type>();
            file >> nextValid;
            firstValid = nextValid;
        }

        File::pos_type nextOfPrevious, previousOfNext;
        file.seekg(offset);
        file.get<bool>();
        file >> previousOfNext >> nextOfPrevious;
        if (previousOfNext != 0xffffffff) {
            file.seekg(previousOfNext);
            file.get<bool>();
            file.get<File::pos_type>();
            file.seekp(file.tellg());
            file << nextOfPrevious;
        }
        if (nextOfPrevious != 0xffffffff) {
            file.seekg(nextOfPrevious);
            file.get<bool>();
            file.seekp(file.tellg());
            file << previousOfNext;
        }
        file.seekp(offset);
        file << false << firstInvalid;
        firstInvalid = offset;
    }
    RecordManager::setMetaData(tableName, metaData);
}

void RecordManager::InsertRecord(const std::string &tableName, Record record) {
    auto &file = RecordManager::OpenTableFile(tableName);
    auto metaData = RecordManager::getMetaData(tableName);
    auto &lastWritePos = std::get<0>(metaData);
    auto &firstInvalidPos = std::get<1>(metaData);
    auto &maxPos = std::get<2>(metaData);
    auto &firstValidPos = std::get<3>(metaData);
    File::pos_type nextPos;
    if (firstInvalidPos == 0xffffffff) {
        if (lastWritePos == 0xffffffff) {
            // empty initial just write at here
            firstValidPos = file.tellg();
        } else {
            // no invalid postion now, use maxPos
            // seek to the next write position
            RecordManager::getRecordByOffset(file, record, maxPos);
        }
        nextPos = file.tellg();
    } else {
        nextPos = firstInvalidPos;
        file.seekg(firstInvalidPos);
        file.get<bool>();
        file >> firstInvalidPos;
        // assert valid = false
    }

    if (lastWritePos != 0xffffffff) {
        // link this to last
        file.seekg(lastWritePos);
        bool valid;
        File::pos_type tmp;
        file >> valid >> tmp;
        file.seekp(file.tellg());
        file << nextPos;
    }

    file.seekp(nextPos);
    // valid
    // means end of valid list
    File::pos_type invalid = 0xffffffff;
    // structure of each record:
    // if record valid
    // valid: bool, previous: pos_type, next: pos_type, [record]
    // invalid
    // valid: bool, next:pos_type
    // valid list is double list to make random insertion and deletion easier
    // invalid list is single list because we only insert or delete in head
    bool valid = true;
    file << valid << lastWritePos;
    file << invalid;

    for (auto &column : record) {
        auto type = column.type();
        auto &rawData = *(column.name());
        if (type == Column::Int) {
            file << std::stoi(rawData);
        } else if (type == Column::Float) {
            file << std::stof(rawData);
        } else if (1 <= type && type < Column::Int) {
            file << FixString(rawData.c_str(), RecordManager::getColumnSize(column));
        } else {
            // Undefined should not happen
        }
    }
    // write lastWrite to file
    lastWritePos = nextPos;
    if (firstValidPos == 0xffffffff) {
        firstValidPos  = nextPos;
    }
    if (nextPos > maxPos) {
        maxPos = nextPos;
    }
    // write back meta data first valid, last write, max pos, firstValidPos
    RecordManager::setMetaData(tableName, std::make_tuple(lastWritePos, firstInvalidPos, maxPos, firstValidPos));
}

std::vector<RecordManager::Record> RecordManager::queryRecordsByOffsets(const std::string &tableName, std::vector<File::pos_type> offsets, RecordManager::Record templateRecord) {
    std::vector<RecordManager::Record> result;
    auto &file = RecordManager::OpenTableFile(tableName);
    for (const auto &offset: offsets) {
        result.emplace_back(RecordManager::getRecordByOffset(file,  templateRecord, offset));
    }
    return result;
}

std::vector<File::pos_type> RecordManager::queryRecordsOffsets(const std::string &tableName) {
    auto metaData = RecordManager::getMetaData(tableName);
    auto firstValid = std::get<3>(metaData);
    auto &file = RecordManager::OpenTableFile(tableName);
    file.seekg(firstValid);
    std::vector<File::pos_type>  result;
    while(firstValid != 0xffffffff) {
        result.emplace_back(firstValid);
        file.seekg(firstValid);
        file.get<bool>();
        file.get<File::pos_type>();
        file >> firstValid;
    }
    return result;
}

RecordManager::MetaData RecordManager::getMetaData(const std::string &tableName) {
    File::pos_type lastWritePos, firstInvalidPos, maxPos, firstValidPos;
    auto &file = RecordManager::OpenTableFile(tableName);
    file.seekg(0);
    file >> lastWritePos >> firstInvalidPos >> maxPos >> firstValidPos;
    return std::make_tuple(lastWritePos, firstInvalidPos, maxPos, firstValidPos);
}

 void RecordManager::setMetaData(const std::string &tableName, const MetaData metaData) {
     auto &file = RecordManager::OpenTableFile(tableName);
     file.seekp(0);
     file << std::get<0>(metaData) << std::get<1>(metaData) << std::get<2>(metaData) << std::get<3>(metaData);
 }

RecordManager::Record RecordManager::getRecordByOffset(File &file,Record &record, File::pos_type offset) {
     file.seekg(offset);
     file.get<bool>();
     file.get<File::pos_type>();
     file.get<File::pos_type>();

     Record result;
     for (auto &column : record) {
         auto type = column.type();
         Column newColumn;
         std::string encodedString;
         if (type == Column::Int) {
             int data;
             file >> data;
             encodedString = std::to_string(data);
         } else if (type == Column::Float) {
             float data;
             file >> data;
             encodedString = std::to_string(data);
         } else if (1 <= type && type < Column::Int) {
             FixString data(RecordManager::getColumnSize(column));
              file >> data;
              encodedString = data.toString();
         } else {
         }
         newColumn.Name = std::make_shared<std::string>(encodedString);
         newColumn.TableName = column.TableName;
         newColumn.ColumnType = column.ColumnType;
         result.emplace_back(newColumn);
     }
     return result;
 }

RecordManager::Record RecordManager::makeTestRecord(int id) {
    Column intCol;
    intCol.ColumnType = Column::Int;
    intCol.Name = std::make_shared<std::string>(std::to_string(id));
    Column floatCol;
    floatCol.ColumnType = Column::Float;
    floatCol.Name = std::make_shared<std::string>("3.141592");
    Column charCol;
    charCol.ColumnType = 8;
    charCol.Name = std::make_shared<std::string>("123456789");
    Record record = {intCol, charCol, floatCol};
    return record;
}

 int RecordManager::getColumnSize(const Column& col) {
     if (col.type() >= 256) {
         // int or float
         return 4;
     } else {
         // it's char 1 ~255
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
