#ifndef CATALOGMANAGER_H
#define CATALOGMANAGER_H

#include <QObject>
#include <fstream>
#include <vector>

class catalogManager : public QObject
{
    Q_OBJECT
    using string = std::string;
    using ifstream = std::ifstream;
    using ofstream = std::ofstream;
    template<typename T>
    using vector = std::vector<T>;
private:
    ifstream fin;
    string Database;//数据库名字
    string TableName;//目前找到的表名字
    int RecordLength = 0;//每条记录的长度
    int AttrNum = 0;//表属性个数
    vector<string> Attribute;//表的属性
    vector<unsigned int> type;//表属性的类型
    vector<bool> IsUnique;//判断是否unique
    vector<bool> HaveIndex;//判断是否有索引
    vector<string> IndexName;//索引名字
    int PriIndex;//主键编号
    //设置类的属性
    void SetAttrNum(const int Num);
    void SetAttribute(const vector<string> &Attr);
    void SetType(const vector<unsigned int> &t);
    void SetIsUnique(const vector<bool> &IsUni);
    void SetHaveIndex(const vector<bool> &HavInd);
    void SetIndexName(const vector<string> &IndName);
    void SetPriIndex(const int PrimaryKey);
    void SetRecordLength(const int length);
    string TableNameFromStr(const string &Str);

public:
    //构造函数和析构函数
    /***********************************************/
    catalogManager(const string &DBName, const string &TableName = string());
    ~catalogManager();
    /***********************************************/

    //删除数据库
    /***********************************************/
    void DropDatabase();
    /***********************************************/

    //判断catalogManager中是否存在表TableName
    bool FindTableName();
    //判断catalogManager中是否存在名字为Name的表
    bool FindTableName(const string Name);
    /*对catalog文件进行操作的函数*/
    /***********************************************/
    //从catalog中获取TableName的信息，放入到类的变量中
    bool GetTableInfo();
    //从catalog中获取名字为Name的表的信息，放入到类的变量中
    bool GetTableInfo(const string &Name);
    //向catalog中添加表信息，Str为要写入的信息
    bool AddTableInfo(const string &Str);
    //向catalog中添加表信息，需要调用Set开头的函数，事先设置好类中的所有信息
    bool AddTableInfo();
    //在catalog中删除当前的表
    bool DropTable();
    //在catalog中删除名字为Name的表
    bool DropTable(const string &Name);
    //在catalog中删除表Table中的名为Index的索引
    bool DropIndex(const string &Table,const string &Index);
    //在Table表的Attr属性上创建名字为Index的索引
    bool CreateIndex(const string &Table,const string &Attr, const string &Index);
    /***********************************************/



    //Set类函数，用于设置类内的信息
    /***********************************************/
    //设置TableName，会清空除了名字以外的其他内容
    void SetTableName(const string &Name);
    //设置Attribute等信息
    void SetAttributeInfo(const int num,
                          const vector<string> &Attr,
                          const vector<unsigned int> &t,
                          const vector<bool> &IsUni,
                          const vector<bool> &HavInd,
                          const vector<string> &IndName,
                          const int PrimaryKey);
    /***********************************************/


    //以下函数用于获取类内的信息
    /***********************************************/
    //找到表中是否有某个属性，没有返回-1，有则返回属性数组下标
    int FindAttributeIndex(const string &AttrName);
    //找到根据Index名称找到数组下标，没有返回-1，有则返回属性数组下标
    int FindIndexAccordingToIndexName(const string &Index);
    //根据数组下标得到相应数据，数组下标可以用FindAttribute函数得到
    bool GetIsUnique(const int i);
    int GetType(const int i);
    bool GetHaveIndex(const int i);
    string GetIndexName(const int i);
    int GetRecordLength();
    int GetAttrNum();
    int GetPriIndex();
    //返回Attribute向量
    std::vector<string> GetAttrName();
    //返回主键名称
    string GetPrimaryKey();
    /***********************************************/


    //一些其他函数
    /***********************************************/
    //删除类里的所有信息
    void Clear();
    //从catalog中获取数据并且打印表信息
#ifdef TEST
    void PrintInfo();
    /***********************************************/
#endif

signals:
    void error(const string &msg);
};

inline catalogManager::catalogManager(const string &DBName, const string &TableName):
Database(DBName),TableName(TableName)
{
    fin.open(Database);
}

inline catalogManager::~catalogManager()
{
    fin.close();
}

inline void catalogManager::SetTableName(const string &Name)
{
    Clear();
    TableName = Name;
}

inline void catalogManager::SetRecordLength(const int length)
{
    RecordLength = length;
}

inline void catalogManager::SetAttrNum(const int Num)
{
    AttrNum = Num;
}

inline void catalogManager::SetPriIndex(const int PrimaryKey)
{
    PriIndex = PrimaryKey;
}

inline void catalogManager::SetAttribute(const vector<string> &Attr)
{
    Attribute.clear();
    for(int i = 0; i < AttrNum; i++)
        Attribute.push_back(Attr[i]);
}

inline void catalogManager::SetType(const vector<unsigned int> &t)
{
    type.clear();
    for(int i = 0; i < AttrNum; i++)
        type.push_back(t[i]);
}

inline void catalogManager::SetIsUnique(const vector<bool> &IsUni)
{
    IsUnique.clear();
    for(int i = 0; i < AttrNum; i++)
        IsUnique.push_back(IsUni[i]);
}

inline void catalogManager::SetHaveIndex(const vector<bool> &HavInd)
{
    HaveIndex.clear();
    for(int i = 0; i < AttrNum; i++)
        HaveIndex.push_back(HavInd[i]);
}

inline void catalogManager::SetIndexName(const vector<string> &IndName)
{
    IndexName.clear();
    for(int i = 0; i < AttrNum; i++)
    {
        if(HaveIndex[i])
            IndexName.push_back(IndName[i]);
        else
            IndexName.push_back("\0");
    }
}

inline auto catalogManager::GetPrimaryKey() -> string
{
    for(int i = 0; i < AttrNum; i++)
    {
        if(i == PriIndex)
            return Attribute[i];
    }
    return string();
}

inline bool catalogManager::GetIsUnique(const int i)
{
    return IsUnique[i];
}

inline int catalogManager::GetType(const int i)
{
    return type[i];
}

inline bool catalogManager::GetHaveIndex(const int i)
{
    return HaveIndex[i];
}

inline auto catalogManager::GetIndexName(const int i) ->string
{
    return IndexName[i];
}

inline int catalogManager::GetRecordLength()
{
    return RecordLength;
}

inline int catalogManager::GetAttrNum()
{
    return AttrNum;
}

inline int catalogManager::GetPriIndex()
{
    return PriIndex;
}

inline auto catalogManager::GetAttrName() -> const vector<string> &
{
    return Attribute;
}

#endif // CATALOGMANAGER_H
