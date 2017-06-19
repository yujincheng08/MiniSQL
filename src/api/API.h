#ifndef API_H
#define API_H


#include "../catalogManager/CatalogManager.h"
#include "../indexManager/BpTree.h"
#include "../recordManager/RecordManager.h"
#include "../bufferManager/File.h"
#include "../interpreter/Column.h"
#include "../interpreter/Condition.h"
#include "../interpreter/Action.h"
#include "../interpreter/Constraint.h"
#include <memory>
#include <QObject>
#include <string>
#include <assert.h>
#include <set>

//#define assert(x) if(!(x)) displayMsg(string("Assert wrong"))

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
    //ptr<bpTree> bpTree = nullptr;
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
    bool isConjunction(Condition::Type type);
    bool isPredication(Condition::Type type);
    Column::Type getColumnType(const ptr<const Column> column);
    RecordManager::Record getTemplateRecord();
    vector<pos_type> queryByCondition(const Action& action);
    vector<pos_type> checkTuples(const ptr<list<Predication>>,const vector<pos_type>&,const vector<Record>&);
    vector<File::pos_type> queryByIndex(ptr<const Condition> condition);
    ptr<list<Predication>> optimization(ptr<const Condition>);
    void postOrderTrav(ptr<const Condition> cNode, ptr<list<Predication>>);
    bool consistent(Condition::Type, int, int);
    bool consistent(Condition::Type, float,float);
    bool consistent(Condition::Type, string,string);
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

inline bool isChar(Column::Type type)
{
    return type < 256U && type > 0U;
}

inline bool convertible(Column::Type type1, Column::Type type2)
{//Verify if type1 can be inverted to type2
    bool ret = false;
    ret = type1 == type2;
    if (!ret) {
        ret = isChar(type1) && isChar(type2) && type1 < type2;
    }
    if (!ret) {
        ret = type1 == Column::Int && type2 == Column::Float;
    }
    return ret;
}

inline std::string opName(Condition::Type type)
{
    switch (type) {
    case Condition::NotEqual:
        return "not equal";
    case Condition::Equal:
        return "\'=\'";
    case Condition::GreaterThan:
        return "\'>\'";
    case Condition::LessThan:
        return "\'<\'";
    case Condition::LessEqual:
        return "\'<=\'";
    case Condition::GreaterEqual:
        return "\'>=\'";
    case Condition::And:
        return "\'and\'";
    case Condition::Or:
        return "\'or\'";
    case Condition::Not:
        return "\'not\'";
    default:
        return "";
    };
}


inline bool API::isPredication(Condition::Type type)
{
    return
        type == Condition::NotEqual ||
        type == Condition::Equal ||
        type == Condition::GreaterThan ||
        type == Condition::LessThan ||
        type == Condition::LessEqual ||
        type == Condition::GreaterEqual;
}

inline bool API::isConjunction(Condition::Type type)
{
    return
            type == Condition::And ||
            type == Condition::Or;
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

inline std::string getTypeName(const Column::Type& type)
{//@@##Using a map or function?
    std::string ret;
    if (type > 0U && type < 256U) {
        ret = std::string("char(") + std::to_string(type) + std::string(")");
    }
    else if (type == 0 || type == 256 || type == 257) {
        switch (type)
        {
        case Column::Int:
            ret = "int";
            break;
        case Column::Float:
            ret = "float";
            break;
        case Column::Undefined:
            ret = "Undefined";
            break;
        }
    }
    return ret;
}

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

inline bool API::consistent(Condition::Type operand, float leftValue, float rightValue)
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
}

inline std::string formalize(const std::string& value, Column::Type type)
{
    if(type > value.size())
        return value+std::string(type-value.size(),'\0');
    else
        return value;
}

#endif  //API_H
