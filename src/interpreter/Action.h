#ifndef ACTION_H
#define ACTION_H
#include <list>
#include <memory>
#include <string>
class Constraint;
class Column;
class Condition;
class Action
{
    template<typename T>
    using ptr = std::shared_ptr<T>;
    template<typename T>
    using list = std::list<T>;
    using string = std::string;
    friend class Interpreter;
public:
    enum Type
    {
        Undefined, CreateTable, CreateIndex, Insert,
        Delete, DropIndex, Select, DropTable
    };
private:
    Type ActionType = Undefined;
    ptr<list<ptr<const Column>>> Columns = nullptr;
    ptr<Constraint> Constraints = nullptr;
    ptr<list<ptr<const string>>> TableName = nullptr;
    ptr<string> IndexName = nullptr;
    ptr<Condition> Conditions = nullptr;
    ptr<list<ptr<list<ptr<const Column>>>>> Values = nullptr;
    Action();
public:
    auto actionType() const -> const Type &;
    auto columns() const -> const ptr<const list<ptr<const Column>>>;
    auto constraints() const -> const ptr<const Constraint>;
    auto tableName() const -> const ptr<const list<ptr<const string>>>;
    auto indexName() const -> const ptr<const string>;
    auto conditions() const -> const ptr<const Condition>;
    auto values() const -> const ptr<const list<ptr<list<ptr<const Column>>>>>;
};

inline Action::Action()
{}

inline auto Action::columns() const -> const ptr<const list<ptr<const Column>>>
{
    return Columns;
}

inline auto Action::constraints() const -> const ptr<const Constraint>
{
    return Constraints;
}

inline auto Action::tableName() const -> const ptr<const list<ptr<const string>>>
{
    return TableName;
}

inline auto Action::indexName() const -> const ptr<const string>
{
    return IndexName;
}

inline auto Action::conditions() const -> const ptr<const Condition>
{
    return Conditions;
}

inline auto Action::actionType() const -> const Type &
{
    return ActionType;
}

inline auto Action::values() const -> const ptr<const list<ptr<list<ptr<const Column>>>>>
{
  return Values;
}
#endif //ACTION_H
