#ifndef BPTREECTRL_H
#define BPTREECTRL_H

#include <memory>
#include <map>
#include <vector>
#include "Types.h"
#include "../indexManager/BpTree.h"
#include "../catalogManager/CatalogManager.h"
#include "../bufferManager/File.h"
#include "../interpreter/Column.h"
#include "../recordManager/RecordManager.h"

using std::unordered_map; using std::vector;
using std::string;

class BpTreeCtrl{
public:
    template<typename T>
    using ptr = std::shared_ptr<T>;
    using Record = vector<Column>;
    BpTreeCtrl(){}
    BpTreeCtrl(ptr<catalogManager>,const string&);
    ~BpTreeCtrl();
    string getTableName();
    static void index(Column::Type, const string&);
    //void addBpTree(Column::Type, const string&);
    void dropIndices();
    bool checkViolate(const Record&);
    void insData(File::pos_type pos, const Record&);
    void delData(const Record&);
    std::vector<File::pos_type> queryByIndex(const string& , const string& , Column::Type , Condition::Type op);
private:
    string tableName;
    ptr<catalogManager> catalog;
    unordered_map<string,ptr<bpTree<FixString>>> strTree;
    unordered_map<string,ptr<bpTree<int>>> intTree;
    unordered_map<string,ptr<bpTree<float>>> floatTree;
    //vector<File::pos_type> query(const Column&);
    template <typename T>
    static vector<File::pos_type> query(ptr<bpTree<T>>,T,Condition::Type);
};

inline string BpTreeCtrl::getTableName()
{
    return tableName;
}

#endif // BPTREECTRL_H
