#include "Interpreter.h"
#include "Action.h"
#include "scanner/Scanner.h"
#include "parser/parser.h"
#include <iostream>
#include <fstream>

using namespace std;
extern void *ParserAlloc(void *(*)(size_t));
extern void ParserFree(void *, void(*)(void *));
extern void Parser(void *, int, const std::string *, BaseInterpreter*);

Interpreter::Interpreter(QObject *parent) : QObject(parent)
{
    parser = ParserAlloc(malloc);
    scanner = new Scanner;
}

void Interpreter::query()
{
    if(Error)
    {
        cerr<<"Error occurs";
        if(File.is_open())
            cerr<<" at line " << LineNo;
        cerr<<" near \""<<Near<<"\" : "<<ErrorMsg<<endl;
    }
    else
    {
#ifdef TEST
        extern void testInterpreter(Action *action);
        testInterpreter(action);
#endif
        emit parsered(*action);
    }
    reset();
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
    reset();
    while(int token = scanner->lex())
    {
        const string &text = scanner->matched();
        if(token == EXEC)
        {
            string filename;
            getline(cin,filename);
            if(filename.back()!=';')
            {
                error("Syntax error: Expected ';'.");
                query();
                continue;
            }
            else
            {
                filename.pop_back();
                if(filename.front()=='"' && filename.back()=='"')
                    filename = filename.substr(1U,filename.length()-2);
                if(File.is_open())
                    File.close();
                File.open(filename,ios_base::in);
                if(!File.is_open())
                {
                    error("File \"" + filename + "\" not exists.");
                    query();
                    continue;
                }
                scanner->switchStreams(File);
                continue;
            }
        }
        if(token == QUIT)
        {
            if(File.is_open())
            {
                scanner->switchStreams(cin);
                File.close();
                reset();
                continue;
            }
            else
                break;
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
