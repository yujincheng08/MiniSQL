#ifndef CATALOGMANAGER_H
#define CATALOGMANAGER_H

#include <QObject>
#include <fstream>

class catalogManager : public QObject
{
    Q_OBJECT
    using string = std::string;
    using ifstream = std::ifstream;
    using ofstream = std::ofstream;
private:
    ifstream fin;
    string Database;//数据库名字
    string TableName;//目前找到的表名字
    int RecordLength = 0;//每条记录的长度
    int AttrNum = 0;//表属性个数
    string* Attribute = nullptr;//表的属性
    string* type = nullptr;//表属性的类型
    bool* IsUnique = nullptr;//判断是否unique
    bool* HaveIndex = nullptr;//判断是否有索引
    string* IndexName = nullptr;//索引名字
    int PriIndex;//主键编号
    const char* DB = nullptr;

    //判断catalogManager中是否存在表TableName
    bool FindTableName();
    //判断catalogManager中是否存在名字为Name的表
    bool FindTableName(string Name);
    //设置类的属性
    void SetAttrNum(int Num);
    void SetAttribute(string* Attr);
    void SetType(const string *t);
    void SetIsUnique(bool* IsUni);
    void SetHaveIndex(bool* HavInd);
    void SetIndexName(const string *IndName);
    void SetPriIndex(int PrimaryKey);
    string TableNameFromStr(const string &Str);

public:
    //构造函数和析构函数
    /***********************************************/
    catalogManager(string DBName);
    catalogManager(string DBName, string TableName);
    ~catalogManager();
    /***********************************************/

    //删除数据库
    /***********************************************/
    void DropDatabase();
    /***********************************************/


    /*对catalog文件进行操作的函数*/
    /***********************************************/
    //从catalog中获取TableName的信息，放入到类的变量中
    bool GetTableInfo();
    //从catalog中获取名字为Name的表的信息，放入到类的变量中
    bool GetTableInfo(string Name);
    //向catalog中添加表信息，Str为要写入的信息
    bool AddTableInfo(string Str);
    //向catalog中添加表信息，需要调用Set开头的函数，事先设置好类中的所有信息
    bool AddTableInfo();
    //在catalog中删除当前的表
    bool DropTable();
    //在catalog中删除名字为Name的表
    bool DropTable(string Name);
    //在catalog中删除表Table中的名为Index的索引
    bool DropIndex(string Table,string Index);
    /***********************************************/



    //Set类函数，用于设置类内的信息
    /***********************************************/
    //设置TableName
    void SetTableName(string Name);
    //设置RecordLength
    void SetRecordLength(int length);
    //设置Attribute等信息
    void SetAttributeInfo(int num,string* Attr,string *t,bool* IsUni,bool* HavInd,string *IndName,int PrimaryKey);
    /***********************************************/


    //以下函数用于获取类内的信息
    /***********************************************/
    //找到表中是否有某个属性，没有返回-1，有则返回属性数组下标
    int FindAttributeIndex(string AttrName);
    //找到根据Index名称找到数组下标，没有返回-1，有则返回属性数组下标
    int FindIndexAccordingToIndexName(string Index);
    //根据数组下标得到相应数据，数组下标可以用FindAttribute函数得到
    bool GetIsUnique(int i);
    string GetType(int i);
    bool GetHaveIndex(int i);
    string GetIndexName(int i);
    int GetRecordLength();
    int GetAttrNum();
    int GetPriIndex();
    //返回主键名称
    string GetPrimaryKey();
    /***********************************************/


    //一些其他函数
    /***********************************************/
    //删除类里的所有信息
    void Clear();
    //从catalog中获取数据并且打印表信息
    void PrintInfo();
    /***********************************************/


};


#endif // CATALOGMANAGER_H
