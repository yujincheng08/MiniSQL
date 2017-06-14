#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include <QObject>
#include "../bufferManager/File.h"
#include "../bufferManager/BufferManager.h"
#include "../interpreter/Column.h"

class RecordManager : public QObject
{
    Q_OBJECT
    friend int main(int argc, char *argv[]);
    friend void testInsert(const std::string &tableName);
public:
    using Record = std::vector<Column>;
    using MetaData = std::tuple<File::pos_type, File::pos_type, File::pos_type, File::pos_type>;
    static constexpr File::pos_type INVALID_POS = 0xffffffff;
    static File &OpenTableFile(const std::string &tableName);
    static  void FlushTableFile(const std::string &tableName);
    // check if the table already exits before calling this
    static  void CreateTable(const std::string &tableName);
    // check if the table already exits before calling this
    static  void DropTable(const std::string &tableName);
    //
    static  void DeleteRecords(const std::string &tableName, std::vector<File::pos_type> positions);
    static  void InsertRecord(const std::string &tableNam, Record record);
    static  std::vector<Record> queryRecordsByOffsets(const std::string &tableName, std::vector<File::pos_type> offsets,  RecordManager::Record templateRecord);
    static  std::vector<File::pos_type> queryRecordsOffsets(const std::string &tableName);
private:
    // lastWritePos, firstInvalidPos, maxPos, firstValidPos
    static MetaData getMetaData(const std::string &tableName);
    static void setMetaData(const std::string &tableName, const MetaData metaData);
    static RecordManager::Record getRecordByOffset(File &file,Record &templateRecord, File::pos_type offset);
    static Record makeTestRecord(int id);
    static int getColumnSize(const Column &col);
    static int getRecordSize(const Record &record);
    static void seekToPreviousFiled(File &file, File::pos_type begin);
    static void seekToRecordData(File &file, File::pos_type);
signals:

public slots:
};

#endif // RECORDMANAGER_H
