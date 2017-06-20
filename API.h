#ifndef API_H
#define API_H


#include "../catalogManager/CatalogManager.h"
#include "../recordManager/RecordManager.h"
#include "../bufferManager/File.h"
#include "../interpreter/Column.h"
#include "../interpreter/Condition.h"
#include "../interpreter/Action.h"
#include "../interpreter/Constraint.h"
#include "BpTreeCtrl.h"
#include "Types.h"
#include <memory>
#include <QObject>
#include <string>
#include <assert.h>
#include <set>

//#define assert(x) if(!(x)) displayMsg(string("Assert wrong"))

using std::string; using std::vector;

class Predication
{
    friend class API;
public:
    template<typename T>
    using ptr = std::shared_ptr<T>;
    template<typename T>
    using set = std::set<T>;
    template<typename T>
    using vector = std::vector<T>;
    using string = std::string;
private:
    Predication() {}
    Predication(bool haveIndex, const ptr<const Condition>condNode) :haveIndex(haveIndex), condNode(condNode) {}
    bool haveIndex = false;
    ptr<const Condition> condNode = nullptr;
    ptr<vector<int>> cResult = nullptr;
};

class API : public QObject
{
    Q_OBJECT
public:
    template<typename T>
    using ptr = std::shared_ptr<T>;
    template<typename T>
    using vector = std::vector<T>;
    template<typename T>
    using list = std::list<T>;
    template<typename T>
    using set = std::set<T>;
    using string = std::string;
    using pos_type = File::pos_type;
    using Record = RecordManager::Record;
private:
    ptr<catalogManager> catalog = nullptr;
    ptr<BpTreeCtrl> bpCtrl;
    int manipulateCount = 0;
    string presentName;
public:
    explicit API(QObject *parent = 0);
    ~API(){flushTable();}
public slots:
    void execute(const Action& action);
signals:
    void displayLine(const string& result);
private:
    void insertTuple(std::size_t length);
    void insertTuple(const Action&);
    void deleteTuples(const Action&);
    void dropTable(const Action&);
    void createTable(const Action&);
    void createIndex(const Action&);
    void dropIndex(const Action& action);
    void select(const Action& action);
    void displaySelect(const vector<string>& attrNames, const vector<vector<Column>>& tuples);
    void displayMsg(const string& result);
    void displayMsg(const list<string>& results);
    bool checkSyn(ptr <const Condition>);
    Column::Type getColumnType(const ptr<const Column> column);
    RecordManager::Record getTemplateRecord();
    vector<pos_type> queryByCondition(const Action& action);
    vector<pos_type> checkTuples(const ptr<list<Predication>>,const vector<pos_type>&,const vector<Record>&);
    void setList(ptr<const Condition> , std::list<Record>&, std::list<pos_type>& );
    vector<File::pos_type> queryByIndex(ptr<const Condition> condition);
    ptr<list<Predication>> optimization(ptr<const Condition>);
    void postOrderTrav(ptr<const Condition> cNode, ptr<list<Predication>>);
    void flushTable();
};



inline void API::displayMsg(const string& result)
{
    emit displayLine(result);
    //std::cout << result<<std::endl;
}

inline void API::displayMsg(const list<string>& results)
{
    for (auto result : results) {
        emit displayLine(result);
        //std::cout << result <<std::endl;
    }
}



inline void API::flushTable()
{
    if(presentName.size() != 0){
        RecordManager::FlushTableFile(presentName);
        manipulateCount = 0;
        displayMsg(string("Flush table"));
    }
}

inline Column::Type API::getColumnType(const ptr<const Column> column)
{
    Column::Type type1 = column->type();
    if (type1 == Column::Undefined) {
        int index = catalog->FindAttributeIndex(*column->name());
        type1 = catalog->GetType(index);
    }
    return type1;
}

/*
inline bool API::consistent(Condition::Type operand, int leftValue, int rightValue)
{
    switch (operand) {
    case Condition::Equal:
        return leftValue == rightValue;
    case Condition::GreaterThan:
        return leftValue > rightValue;
    case Condition::GreaterEqual:
        return leftValue >= rightValue;
    case Condition::LessEqual:
        return leftValue <= rightValue;
    case Condition::LessThan:
        return leftValue < rightValue;
    case Condition::NotEqual:
        return leftValue != rightValue;
    default:return false;
    }
}



inline bool API::consistent(Condition::Type operand, string leftValue, string rightValue)
{
    switch (operand) {
    case Condition::Equal:
        return leftValue == rightValue;
    case Condition::GreaterThan:
        return leftValue > rightValue;
    case Condition::GreaterEqual:
        return leftValue >= rightValue;
    case Condition::LessEqual:
        return leftValue <= rightValue;
    case Condition::LessThan:
        return leftValue < rightValue;
    case Condition::NotEqual:
        return leftValue != rightValue;
    default:return false;
    }
}*/



#endif  //API_H
