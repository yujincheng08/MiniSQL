#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "Action.h"
#include "Column.h"
#include "Constraint.h"
#include "Condition.h"
#include <QObject>
#include <iostream>
#include <memory>
class Scanner;
class Interpreter : public QObject
{
public:
    template<typename T>
    using list = std::list<T>;
    using string = std::string;
    template<typename T>
    using ptr = std::shared_ptr<T>;
private:
    Q_OBJECT
    void *parser = nullptr;
    Scanner *scanner = nullptr;
    size_t LineNo;
    Action *action = nullptr;
    bool Error;
public:
    enum
    {
        QUIT = 0x0, EXEC = -0x1, NEWLINE = -0x2
    };
    explicit Interpreter(QObject *parent = 0);
    void error(const string &msg);
    void query();
    void setActionType(const Action::Type type);
    void addTableName(const string &tableName);
    void newColumn(const string& columnName, const Column::Type type,
                   const string &tableName = string());
    void newConstraint(const string &columnName, const Constraint::Type type);
    void addIndexName(const string &indexName);
    void addValue(const string &value, const Column::Type type);
    void beginValue();
    Condition *newCondition(const string& columnName, const Column::Type,
                      const string &tableName = string());
    Condition *newCondition(const Condition::Type type,
                      Condition *first, Condition * second = nullptr);
    void newCondition(Condition *condition);

    ~Interpreter();
signals:
    void parsered(Action);
public slots:
    void run();
};

inline void Interpreter::error(const string &msg)
{
    std::cerr<<msg<<std::endl;
}

inline void Interpreter::setActionType(const Action::Type type)
{
    if(action->ActionType==Action::Undefined)
        action->ActionType = type;
    else
        error("syntax error");
}

inline void Interpreter::addTableName(const string &tableName)
{
    if(!action->TableName)
        action->TableName = std::make_shared<list<ptr<const string>>>();
    action->TableName->push_back(std::make_shared<const string>(tableName));
}

inline void Interpreter::addIndexName(const string &indexName)
{
    if(!action->IndexName)
        action->IndexName = std::make_shared<string>(indexName);
    else
        error("syntax error");
}

//TODO: check type with the pevious value;
inline void Interpreter::addValue(const string &value,const Column::Type type)
{
    auto column = std::make_shared<Column>(Column());
    column->ColumnType = type;
    column->Name = std::make_shared<string>(value);
    action->Values->back()->push_back(column);
}

inline void Interpreter::beginValue()
{
    if(!action->Values)
        action->Values = std::make_shared<list<ptr<list<ptr<const Column>>>>>();
    action->Values->push_back(std::make_shared<list<ptr<const Column>>>());
}

inline Condition *Interpreter::newCondition(const string &columnName, const Column::Type type,
                                            const string &tableName)
{
    Condition * condition = new Condition();
    condition->Op = Condition::Node;
    condition->Value = std::make_shared<Column>(Column());
    condition->Value->ColumnType = type;
    condition->Value->Name = std::make_shared<string>(columnName);
    if(!tableName.empty())
        condition->Value->TableName = std::make_shared<string>(tableName);
    return condition;
}

inline Condition *Interpreter::newCondition(const Condition::Type type,
                                            Condition *first, Condition * second)
{
    Condition * condition = new Condition();
    condition->Op = type;
    condition->FirstOperand = ptr<Condition>(first);
    condition->SecondOperand = ptr<Condition>(second);
    return condition;
}

inline void Interpreter::newCondition(Condition *condition)
{
    action->Conditions = std::shared_ptr<Condition>(condition);
}



#endif // INTERPRETER_H
