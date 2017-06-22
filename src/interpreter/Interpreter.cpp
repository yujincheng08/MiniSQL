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
        setConsoleColor(0xC);
        cerr<<"Error occurs";
        if(!File.empty())
            cerr<<" at line " << LineNo;
        cerr<<" near \""<<Near<<"\" : "<<ErrorMsg<<endl;
        setConsoleColor(0xF);
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
    setConsoleColor(0xF);
    reset();
    while(int token = scanner->lex())
    {
        const string &text = scanner->matched();
        if(token == EXEC)
        {
            string filename;
            if(!File.empty())
                getline(*File.back(),filename);
            else
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
                ifstream * file = new ifstream(filename);
                if(!file->is_open())
                {
                    error("File \"" + filename + "\" not exists.");
                    delete file;
                    query();
                    continue;
                }
                File.push_back(file);
                scanner->switchStreams(*file);
                continue;
            }
        }
        if(token == QUIT)
        {
            if(!File.empty())
            {
                display(string("File execution complete."));
                delete File.back();
                File.pop_back();
                if(File.empty())
                    scanner->switchStreams(cin);
                else
                    scanner->switchStreams(*File.back());
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
    display(string("Good Bye!"));
}
