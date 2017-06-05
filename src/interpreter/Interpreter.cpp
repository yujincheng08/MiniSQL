#include "Interpreter.h"
#include "Action.h"
#include "scanner/Scanner.h"
#include "parser/parser.h"
#include <iostream>
#include <fstream>
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

void test(Action *action)
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
            cout<<"\tprimaryKey: "<< *i.primaryKey()->name()<<endl;
        if(i.uniques())
        {
            cout<<"\tUniques: "<<endl;
            for(auto j : *i.uniques())
            {
                cout<<"\t"<<*j<<endl;
            }
        }
    }
    if(action->conditions())
    {
        printCondition(action->conditions());
        cout<<endl;
    }

}

void Interpreter::query()
{
    if(Error)
    {
        cerr<<"Error occurs at line " << LineNo
           <<" near \""<<Near<<"\" : "<<ErrorMsg<<endl;
    }
    else
    {
        test(action);
        emit parsered(*action);
    }
    ErrorMsg = "";

    delete action;
    action = new Action();
    Error = false;
}

Interpreter::~Interpreter()
{
    ParserFree(parser, free);
}

void Interpreter::error(const string &msg)
{
    if(!Error)
    {
        LineNo = scanner->lineNr();
        Error = true;
        ErrorMsg = msg;
        Near = scanner->matched();
    }
}



void Interpreter::run()
{
    action = new Action();
    while(int token = scanner->lex())
    {
        const string &text = scanner->matched();
        if(token == EXEC)
        {
            string filename;
            getline(cin,filename);
            if(filename.back()!=';')
            {
                error("Syntax error. Expected ';'.");
                continue;
            }
            else
            {
                filename.pop_back();
                if(filename.front()=='"' && filename.back()=='"')
                    filename = filename.substr(1U,filename.length()-2);
                ifstream file(filename);
                if(!file.is_open())
                {
                    error("File not exists.");
                    continue;
                }
                file.close();
                scanner->switchIstream(filename);
                continue;
            }
        }
        Parser(parser, token, new string(text),this);
        if(token == SEMICOLON)
        {
            Parser(parser, 0, nullptr,this);
            query();
        }
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
            return error("Syntax error: Multiple primary keys");
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

void Interpreter::expected(const Interpreter::string &token)
{
    ;
}


void Interpreter::newColumn (const string& columnName, const Column::Type type,
                             const string &tableName)
{
    if(!action->Columns)
        action->Columns = std::make_shared<list<ptr<const Column>>>();
    //std::cout<<"Get column "<<columnName<<" type "<<type<<std::endl;
    if(action->Columns->size()>32U)
        return error("More than 32 attributes in one table.");
    auto column = std::make_shared<Column>(Column());
    column->ColumnType = type;
    column->Name = std::make_shared<string>(columnName);
    if(!tableName.empty())
        column->TableName = std::make_shared<string>(tableName);
    action->Columns->push_back(column);
}
