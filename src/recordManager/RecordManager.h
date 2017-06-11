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
    static File &OpenTableFile(const std::string &tableName);
    // check if the table already exits before calling this
    static  void CreateTable(const std::string &tableName);
    // check if the table already exits before calling this
    static  void DropTable(const std::string &tableName);
    //
    static  bool DeleteRecords(const std::string &tableName, std::vector<File::pos_type> positions);
    static std::pair<File::pos_type, File::pos_type> InsertRecord(const std::string &tableName, File::pos_type lastWritePos, File::pos_type firstInvalidPos, Record record);
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
