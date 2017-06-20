#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <string>
#include "../interpreter/Condition.h"
#include "../interpreter/Column.h"

inline std::string getTypeName(const Column::Type& type)
{//@@##Using a map or function?
    std::string ret;
    if (type > 0U && type < 256U) {
        ret = std::string("char(") + std::to_string(type) + std::string(")");
    }
    else if (type == 0 || type == 256 || type == 257) {
        switch (type)
        {
        case Column::Int:
            ret = "int";
            break;
        case Column::Float:
            ret = "float";
            break;
        case Column::Undefined:
            ret = "Undefined";
            break;
        }
    }
    return ret;
}

inline bool isChar(Column::Type type)
{
    return type < 256U && type > 0U;
}

inline bool convertible(Column::Type type1, Column::Type type2)
{//Verify if type1 can be inverted to type2
    bool ret = false;
    ret = type1 == type2;
    if (!ret) {
        ret = isChar(type1) && isChar(type2) && type1 < type2;
    }
    if (!ret) {
        ret = type1 == Column::Int && type2 == Column::Float;
    }
    return ret;
}

inline std::string formalize(const std::string& value, Column::Type type)
{
    if(type > value.size())
        return value+std::string(type-value.size(),'\0');
    else
        return value;
}

template<typename T>
inline bool consistent(Condition::Type operand, T leftValue, T rightValue)
{
    switch (operand) {
    case Condition::Equal:
        return leftValue == rightValue;
    case Condition::GreaterThan:
        return leftValue > rightValue;
    case Condition::GreaterEqual:
        return leftValue >= rightValue;
    case Condition::LessEqual:
        return leftValue <= rightValue;
    case Condition::LessThan:
        return leftValue < rightValue;
    case Condition::NotEqual:
        return leftValue != rightValue;
    default:return false;
    }
}

inline bool isConjunction(Condition::Type type)
{
    return
            type == Condition::And ||
            type == Condition::Or;
}



inline std::string opName(Condition::Type type)
{
    switch (type) {
    case Condition::NotEqual:
        return "not equal";
    case Condition::Equal:
        return "\'=\'";
    case Condition::GreaterThan:
        return "\'>\'";
    case Condition::LessThan:
        return "\'<\'";
    case Condition::LessEqual:
        return "\'<=\'";
    case Condition::GreaterEqual:
        return "\'>=\'";
    case Condition::And:
        return "\'and\'";
    case Condition::Or:
        return "\'or\'";
    case Condition::Not:
        return "\'not\'";
    default:
        return "";
    };
}

inline bool isPredication(Condition::Type type)
{
    return
        type == Condition::NotEqual ||
        type == Condition::Equal ||
        type == Condition::GreaterThan ||
        type == Condition::LessThan ||
        type == Condition::LessEqual ||
        type == Condition::GreaterEqual;
}


#endif // TYPES_H
