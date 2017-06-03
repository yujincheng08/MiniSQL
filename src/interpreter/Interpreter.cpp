#include "Interpreter.h"
#include "Action.h"
#include "scanner/Scanner.h"
#include "parser/parser.h"
#include <iostream>
using namespace std;
extern void *ParserAlloc(void *(*)(size_t));
extern void ParserFree(void *, void(*)(void *));
extern void Parser(void *, int, const std::string *, Interpreter*);

Interpreter::Interpreter(QObject *parent) : QObject(parent)
{
    parser = ParserAlloc(malloc);
    scanner = new Scanner;
}


ostream &operator<<(ostream &out, const Column c)
{

    if(c.name())
        out<<*c.name();
    out<<"{"<<c.type() <<"}";
    if(c.tableName())
        out<<"["<< *c.tableName() << "]";
    return out;
}

void printCondition(Interpreter::ptr<const Condition> c)
{
    if(!c) return;
    cout<<"(";
    if(c->firstOperand() && c->firstOperand()->op()==Condition::Node)
        cout<<*c->firstOperand()->value();
    else
        printCondition(Interpreter::ptr<const Condition>(c->firstOperand()));
    cout<<" "<<c->op()<<" ";
    if(!c->secondOperand())
    {
        cout<<")";
        return;
    }
    if(c->secondOperand()->op()==Condition::Node)
        cout<<*c->secondOperand()->value();
    else
        printCondition(Interpreter::ptr<const Condition>(c->secondOperand()));
    cout<<")";

}

void Interpreter::query()
{
    cout<<"Type: "<<action->actionType()<<endl;
    if(action->tableName())
    {
        cout<<"Table List: "<<endl;
        for(auto i : *action->tableName())
        {
            cout<<"\t"<<*i<<endl;
        }
    }
    if(action->indexName())
    {
        cout<<"Index Name: "<<
              "\t"<<*action->indexName()<<endl;
    }
    if(action->columns())
    {
        cout<<"Column List: "<<endl;
        for(auto i : *action->columns())
        {
            cout<<"\t"<<*i<<endl;
        }
    }
    if(action->constraints())
    {
        cout<<"Constraints List: "<<endl;
        auto i = *action->constraints();
        if(i.primaryKey())
            cout<<"\tprimaryKey: "<< *i.primaryKey()<<endl;
        if(i.uniques())
        {
            cout<<"\tUniques: "<<endl;
            for(auto j : *i.uniques())
            {
                cout<<"\t"<<*j<<endl;
            }
        }
    }
    if(action->values())
    {
        cout<<"value List: "<<endl;
        for(auto i : *action->values())
        {
            cout<<"(";
            for(auto j : *i)
            {
                cout<<"\t"<<j->type()<<":"<<*j->name();
            }
            cout<<"\t)"<<endl;
        }
    }
    if(action->conditions())
    {
        printCondition(action->conditions());
        cout<<endl;
    }
    emit parsered(*action);
    delete action;
    action = new Action();
}

Interpreter::~Interpreter()
{
    ParserFree(parser, free);
}

void Interpreter::run()
{
    action = new Action();
    while(int token = scanner->lex())
    {
        const string &text = scanner->matched();
        if(token == NEWLINE)
        {
            LineNo++;
            continue;
        }
        else if(token == EXEC)
        {
            int newtoken = scanner->lex();
            if(newtoken!=STRING)
            {
                error("error filename");
            }
        }
        //cout<<"Get "<<token<<" with "<<text<<endl;
        Parser(parser, token, new string(text),this);
        if(token == SEMICOLON)
            Parser(parser, 0, nullptr,this);
    }
    cout<<"Good Bye!"<<endl;
}

void Interpreter::newConstraint(const string &columnName, const Constraint::Type type)
{
    if(type == Constraint::None) return;
    if(!action->Constraints)
        action->Constraints = make_shared<Constraint>(Constraint());
    //cout<<"Get Constraint "<<columnName<<" type "<<type<<endl;
    if(type==Constraint::PrimaryKey)
    {
        if(action->Constraints->Primary)
            return error("Syntax error");
        auto column = make_shared<Column>(Column());
        action->Constraints->Primary  = column;
        column->Name = make_shared<string>(columnName);
    }
    else if(type==Constraint::Unique)
    {
        if(!action->Constraints->Uniques)
            action->Constraints->Uniques = make_shared<list<ptr<const Column>>>();
        auto column = make_shared<Column>(Column());
        column->Name = make_shared<string>(columnName);
        action->Constraints->Uniques->push_back(column);
    }
}


void Interpreter::newColumn (const string& columnName, const Column::Type type,
                             const string &tableName)
{
    if(!action->Columns)
        action->Columns = std::make_shared<list<ptr<const Column>>>();
    //std::cout<<"Get column "<<columnName<<" type "<<type<<std::endl;
    if(action->Columns->size()>32U)
        return error("syntax error");
    auto column = std::make_shared<Column>(Column());
    column->ColumnType = type;
    column->Name = std::make_shared<string>(columnName);
    if(!tableName.empty())
        column->TableName = std::make_shared<string>(tableName);
    action->Columns->push_back(column);
}
