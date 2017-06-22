#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "BaseInterpreter.h"
#include <QObject>
#include <iostream>
#include <fstream>
#include <list>
class Scanner;
class Interpreter : public QObject, protected BaseInterpreter
{
    friend class Main;
    friend class Parser;
private:
    size_t LineNo = 0U;
    string ErrorMsg;
    string Near;
    bool Error = false;
    std::list<std::ifstream*> File;
    void *parser = nullptr;
    Scanner *scanner = nullptr;
private:
    Q_OBJECT
    explicit Interpreter(QObject *parent = 0);
    void query();
public:
    virtual ~Interpreter() override final;
protected:
    virtual void error(const string &msg) override final;
    virtual void reset() override final;
signals:
    void parsered(Action);
public slots:
    void run();
    //void display(const QString &result);
    void display(const string &result);
    void displayError(const string &result);

};

inline void Interpreter::reset()
{
    ErrorMsg = "";
    Error = false;
    BaseInterpreter::reset();
    if(File.empty())
    {
        setConsoleColor(0xE);
        std::cout<<"MiniSQL > "<<std::endl;
        setConsoleColor(0xF);
    }
}

//inline void Interpreter::display(const QString &result)
//{
//    std::cout<<result.toStdString()<<std::endl;
//}

inline void Interpreter::display(const string &result)
{
    std::cout<<result<<std::endl;
}

inline void Interpreter::displayError(const string &result)
{
    setConsoleColor(0xC);
    std::cerr<<"Error occurs";
    if(!File.empty())
        std::cerr<<" at line " << LineNo;
    std::cerr<<": "<<result<<std::endl;
    setConsoleColor(0xF);
}

#endif // INTERPRETER_H
