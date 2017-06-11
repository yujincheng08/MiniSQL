#include "RecordManager.h"
#include <QCoreApplication>
int main(int argc, char *argv[]) {
    std::string tableName("test");
//    auto Record = RecordManager::makeTestRecord();
//    RecordManager::DropTable(tableName);
//    RecordManager::CreateTable(tableName);
//    for (int i = 0; i < 10000; i++) {
//        RecordManager::InsertRecord(tableName, Record);
//        RecordManager::FlushTableFile(tableName);
//    }
    QCoreApplication app(argc, argv);
    auto &file = BufferManager::open(tableName);
    File::pos_type a = 0xffffffff, b = 1234, c, d;
    int e = 90; float f = 2.34; FixString g(std::string("1234"));
    file.seekp(0);
    file << a << b << e << f << g;
    file.flush();
    auto t = file.tellp();
//    std::cout<< t <<"\n";
    file.seekg(0);
    file >> c >> d;

    return app.exec();
}
