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
public:
    using Record = std::vector<Column>;
    constexpr static File::pos_type INVALID_POS = 0xffffffff;
    static File &OpenTableFile(const std::string &tableName);
    static  void FlushTableFile(const std::string &tableName);
    // check if the table already exits before calling this
    static  void CreateTable(const std::string &tableName);
    // check if the table already exits before calling this
    static  void DropTable(const std::string &tableName);
    //
    static  bool DeleteRecords(const std::string &tableName, std::vector<File::pos_type> positions);
    static  void InsertRecord(const std::string &tableNam, Record record);
    static  std::vector<Record> queryRecordsByOffsets(const std::string &tableName, std::vector<File::pos_type> offsets,  RecordManager::Record templateRecord);
    static  std::vector<File::pos_type> queryRecordsOffsets(const std::string &tableName, int recordSize);
private:
    static Record makeTestRecord();
    static int getColumnSize(const Column &col);
    static int getRecordSize(const Record &record);
signals:

public slots:
};

#endif // RECORDMANAGER_H
