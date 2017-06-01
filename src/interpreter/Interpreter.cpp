#include "Interpreter.h"
#include "scanner/Scanner.h"
#include <iostream>
extern "C" {
#include "parser/miniSqlDef.h"
}
using namespace std;
Interpreter::Interpreter(QObject *parent) : QObject(parent)
{
    parser = miniSqlParserAlloc(malloc);
    scanner = new Scanner;
}

void Interpreter::run()
{
    while(int token = scanner->lex())
    {
        const string &text = scanner->matched();
        cout<<"Get "<<token<<" with "<<text<<endl;
    }
    cout<<"Good Bye!"<<endl;
}
