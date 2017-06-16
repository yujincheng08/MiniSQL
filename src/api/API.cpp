#include "API.h"
#include "../catalogManager/CatalogManager.h"
#include "../recordManager/RecordManager.h"
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include <set>
#include <stack>


API::API(QObject *parent) : QObject(parent)
{

}

void API::execute(const Action& action)
{
    //Change presentName
    if (catalog == nullptr) {
        presentName = *(*(action.tableName()->begin()));
        catalog = std::make_shared<catalogManager>(
                    string("myDB"),
                    presentName
                    );
    }
    else {
        if (presentName != *(*(action.tableName()->begin()))) {
            flushTable();
            presentName = *(*(action.tableName()->begin()));
            catalog->SetTableName(presentName);
        }
    }
    //Check flush table or not
    if(manipulateCount > 0){
        if(action.actionType() != Action::Delete && action.actionType() != Action::Insert){
            flushTable();
        }
        else if(manipulateCount >= 1000){
            flushTable();
        }
    }
    //execute
    if (action.actionType() == Action::CreateTable) {
        createTable(action);
    }
    else {
        if (catalog->GetTableInfo()) {
            switch (action.actionType()) {
            case Action::Undefined:
                //do something
                break;
                /******************DDL****************/
            case Action::DropTable:
                dropTable(action);
                break;
            case Action::CreateIndex:
                createIndex(action);
                break;
            case Action::DropIndex:
                dropIndex(action);
                break;
                /*****************DML****************/
            case Action::Insert:
                insertTuple(action);
                manipulateCount++;
                break;
            case Action::Select:
                select(action);
                break;
            case Action::Delete:
                deleteTuples(action);
                manipulateCount++;
                break;
            default://@@##
                break;
            }
        }
        else {
            displayMsg(string("No such table!"));
        }
    }
}
/*************************DDL**********************/
void API::createTable(const Action& action)
{
    assert(action.actionType() == Action::CreateTable);
    //@@##
    //@@##Create a string array?

    if (!catalog->FindTableName()) {//@@##Use another function?
        size_t AttrNum = (action.columns()->size());
        std::vector<string> Attr;
        std::vector<unsigned int> t;
        std::vector<bool> Isuni;
        std::vector<bool> HavInd;
        std::vector<string> IndName;
        std::set<string> Dict;
        int primaryKey;

        //Copy information to arrays
        string priName;
        list<string> uniqueNames;
        if (action.constraints() != nullptr) {
            if (action.constraints()->primaryKey() == nullptr) {
                primaryKey = -1;
            }
            else {
                priName = *(action.constraints()->primaryKey()->name());
            }
            if (action.constraints()->uniques() != nullptr && action.constraints()->uniques()->size() != 0) {
                auto uniColumns = action.constraints()->uniques();
                for (auto pcolumn : *(uniColumns)) {
                    uniqueNames.push_back(*(pcolumn->name()));
                }
            }
        }
        for (auto columnp : *(action.columns())) {//For each column
            auto begin = uniqueNames.begin();
            auto end = uniqueNames.end();
            auto found = find(begin, end, *(columnp->name()));
            bool isuni = (uniqueNames.size() > 0 && found != end);
            if (priName.size() > 0)
                isuni = isuni || *(columnp->name()) == priName;
            if (isuni) {
                uniqueNames.erase(found);
            }
            Isuni.push_back(isuni);
            Attr.push_back(*(columnp->name()));
            if (Dict.find(*(columnp->name())) != Dict.end()) {
                displayMsg(string("Two columns' name repeat!"));
                return;
            }
            else {
                Dict.insert(*(columnp->name()));
            }
            Dict.insert(*(columnp->name()));
            t.push_back(columnp->type());
            if (priName.size()>0 && *(columnp->name()) == priName) {
                primaryKey = (int)Attr.size() - 1;//@@##
                HavInd.push_back(true);
                IndName.push_back(priName + "_index");//@@##
                //Call index manager
            }
            else {
                HavInd.push_back(false);
            }
        }
        catalog->SetAttributeInfo(AttrNum, Attr, t, Isuni, HavInd, IndName, primaryKey);
        if (catalog->AddTableInfo()) {
            displayMsg(string("Create table successfully"));
        }
        else {
            //displayMsg;
        }
    }
    else {
        displayMsg(string("Table already exists"));//@@##
    }
}

/************************DML************************/
void API::select(const Action& action)
{
    assert(action.actionType() == Action::Select);
    vector<string> attrNames;
    vector<Record> records;
    if (action.columns() != nullptr) {
        for (auto column : *action.columns()) {
            string name = *column->name();
            if (catalog->FindAttributeIndex(name) != -1)
                attrNames.push_back(name);
            else {
                displayMsg(string("Attribute") + name + string(" does not exist"));
                return;
            }
        }
    }
    else {
        attrNames = catalog->GetAttrName();
    }
    auto offsets = queryByCondition(action);
    if (offsets.size() != 0) {
        records = RecordManager::queryRecordsByOffsets(presentName, offsets, getTemplateRecord());
    }
    displaySelect(attrNames, records);
}

void API::insertTuple(const Action& action)
{
    assert(action.actionType() == Action::Insert);
    int attrNum = catalog->GetAttrNum();
    size_t coNum = action.columns()->size();
    if (coNum < attrNum) {
        displayMsg(string("Too few values"));
    }
    else if (coNum > attrNum) {
        displayMsg(string("Too many values"));
    }
    else {
        bool varified = true;
        vector<Column> tuple;
        tuple.reserve(coNum);
        int i = 0;
        for (list<ptr<const Column>>::const_iterator iter = action.columns()->begin();
             iter != action.columns()->end(); iter++, i++) {
            Column column;
            if ((*iter)->type() == catalog->GetType(i)) {
                column = **iter;
                tuple.push_back(column);
            }
            //Change the type from interpreter to type from catalog
            else if (convertible((*iter)->type(), catalog->GetType(i))) {
                //Column column;
                if (isChar((*iter)->type())) {
                    size_t blank = catalog->GetType(i) - (*iter)->type();
                    column.Name = std::make_shared<string>(*(*iter)->name() + string(blank, ' '));
                }
                else {
                    column.Name = (*iter)->Name;
                }
                column.ColumnType = catalog->GetType(i);
                tuple.push_back(column);
            }
            else {
                displayMsg(getTypeName((*iter)->type()) +
                           string(" cannot be converted to ") +
                           getTypeName(catalog->GetType(i)));
                varified = false;
                break;
            }
        }
        if (varified) {
            bool hasUnique = false;
            vector<ptr<list<Predication>>> testSet;
            vector<string> attrName = catalog->GetAttrName();
            //Create a testSet
            i = 0;
            for (list<ptr<const Column>>::const_iterator iter = action.columns()->begin();
                 iter != action.columns()->end(); iter++, i++) {
                if (catalog->GetIsUnique(i)) {
                    auto test = std::make_shared<list<Predication>>();
                    Predication predicator;
                    //New a Condition object
                    auto condNode = new Condition;
                    condNode->Op = Condition::Equal;
                    Column Value1;
                    Value1.Name = std::make_shared<string>(attrName[i]);
                    Value1.ColumnType = catalog->GetType(i);
                    Condition FirstOperand, SecondOperand;
                    //The first operand is from catalog
                    FirstOperand.Op = Condition::Node;
                    FirstOperand.Value = std::make_shared<Column>(Value1);
                    //The second operand is from user
                    SecondOperand.Op = Condition::Node;
                    SecondOperand.Value = std::make_shared<Column>(tuple[i]);
                    condNode->FirstOperand = std::make_shared<Condition>(FirstOperand);
                    condNode->SecondOperand = std::make_shared<Condition>(SecondOperand);
                    //Set the predicator
                    predicator.condNode = ptr<Condition>(condNode);
                    predicator.haveIndex = catalog->GetHaveIndex(i);
                    test->push_back(predicator);
                    testSet.push_back(test);
                    hasUnique = true;
                }
            }
            if (hasUnique) {
                auto offsets = RecordManager::queryRecordsOffsets(presentName);
                auto records = RecordManager::queryRecordsByOffsets(presentName, offsets, getTemplateRecord());
                for (auto test : testSet) {
                    auto resOffsets = checkTuples(test, offsets, records);
                    if (resOffsets.size() != 0) {
                        varified = false;
                        break;
                    }
                }
            }
        }
        if (varified) {
            RecordManager::InsertRecord(presentName, tuple);
        }
        else {
            displayMsg(string("Insert failed"));
        }
    }
}

void API::deleteTuples(const Action& action)
{
    assert(action.actionType() == Action::Delete);
    //call record manager
    auto offsets = queryByCondition(action);
    if(offsets.size() != 0){
        RecordManager::DeleteRecords(presentName, offsets);
    }
}

API::vector<File::pos_type> API::queryByCondition(const Action& action)
{
    assert(action.tableName()->size() == 1);
    auto offsets = RecordManager::queryRecordsOffsets(presentName);
    if (action.conditions() == nullptr) {
        //select all
        displayMsg(string("Select all"));
        return offsets;
    }
    else if (checkSyn(action.conditions())) {

        displayMsg(string("Select by conditions"));
        auto predicators = optimization(action.conditions());
        auto templateRecord = getTemplateRecord();
        auto records = RecordManager::queryRecordsByOffsets(presentName, offsets, templateRecord);
        return checkTuples(predicators, offsets, records);
    }
    else{
        return vector<pos_type>();
    }
}

API::vector<API::pos_type> API::checkTuples(
        const ptr<list<Predication>> predicators,
        const vector<pos_type>& offsets,
        const vector<Record>& records
)
{

    auto predicator = predicators->begin();
    while (predicator != predicators->end() && predicator->haveIndex) {
        //get offsets from indexManager
        predicator++;
    }
    list<pos_type> offsetList;
    //Copy to list
    for (auto pos : offsets) {
        offsetList.push_back(pos);
    }
    list<Record> recordList;
    for (auto record : records) {
        recordList.push_back(record);
    }
    bool nullFlag = false;
    while (predicator != predicators->end()) {
        //Get type
        Condition::Type opType = predicator->condNode->op();
        //Get operand
        auto operand1 = predicator->condNode->firstOperand();
        auto operand2 = predicator->condNode->secondOperand();
        //Get operand type
        Column::Type operandType1 = getColumnType(operand1->value());
        Column::Type operandType2 = getColumnType(operand2->value());
        Column::Type operandType = convertible(operandType1, operandType2) ? operandType2 : operandType1;
        //Get name or value
        string name1 = *operand1->value()->name();
        string name2 = *operand2->value()->name();
        //If it is a column name
        bool isColumn1 = operand1->value()->type() == Column::Undefined;
        bool isColumn2 = operand2->value()->type() == Column::Undefined;
        int index1 = 0, index2 = 0;
        index1 = catalog->FindAttributeIndex(name1);
        index2 = catalog->FindAttributeIndex(name2);
        //Get records
        auto riterator = recordList.begin();
        auto piterator = offsetList.begin();
        //@@##for each tuple, check if consistent, get a vector of tuples
        if (isChar(operandType)) {
            float value1 = 0, value2 = 0;
            if (!isColumn1)	value1 = std::stof(name1);
            if (!isColumn2) value2 = std::stof(name2);
            //Main recursion
            if (isColumn1 || isColumn2) {
                while (riterator != recordList.end() && piterator != offsetList.end()) {
                    if (isColumn1) value1 = std::stoi(*(riterator->begin() + index1)->name());
                    if (isColumn2) value2 = std::stoi(*(riterator->begin() + index2)->name());
                    if (consistent(opType, value1, value2)) {
                        riterator++;
                        piterator++;
                    }
                    else {
                        riterator = recordList.erase(riterator);
                        piterator = offsetList.erase(piterator);
                    }
                }
            }
        }
        else if (operandType == Column::Int) {
            int value1 = 0, value2 = 0;
            if (!isColumn1) value1 = std::stoi(name1);
            if (!isColumn2) value2 = std::stoi(name2);
            //Main recursion
            if (isColumn1 || isColumn2) {
                while (riterator != recordList.end() && piterator != offsetList.end()) {
                    if (isColumn1) value1 = std::stoi(*(riterator->begin() + index1)->name());
                    if (isColumn2) value2 = std::stoi(*(riterator->begin() + index2)->name());
                    if (consistent(opType, value1, value2)) {
                        riterator++;
                        piterator++;
                    }
                    else {
                        riterator = recordList.erase(riterator);
                        piterator = offsetList.erase(piterator);
                    }
                }
            }
        }
        else if (operandType == Column::Float) {
            float value1 = 0, value2 = 0;
            if (!isColumn1) value1 = std::stoi(name1);
            if (!isColumn2) value2 = std::stoi(name2);
            //Main recursion
            if (isColumn1 || isColumn2) {
                while (riterator != recordList.end() && piterator != offsetList.end()) {
                    if (isColumn1) value1 = std::stoi(*(riterator->begin() + index1)->name());
                    if (isColumn2) value2 = std::stoi(*(riterator->begin() + index2)->name());
                    if (consistent(opType, value1, value2)) {
                        riterator++;
                        piterator++;
                    }
                    else {
                        riterator = recordList.erase(riterator);
                        piterator = offsetList.erase(piterator);
                    }
                }
            }
        }
        //Skip when satisfy the condition
        if (offsetList.empty() || recordList.empty()) {
            nullFlag = true;
            break;
        }
        predicator++;
    }
    vector<pos_type> resOffsets;
    if (!nullFlag) {
        for (auto offset : offsetList) {
            resOffsets.push_back(offset);
        }
    }
    return resOffsets;
}

API::ptr<API::list<Predication>> API::optimization(ptr<const Condition> cRoot)
{
    assert(cRoot != nullptr);
    auto preOrder = std::make_shared< list<Predication> >();//New an object
    //Traverse the grammar tree
    postOrderTrav(cRoot, preOrder);
    return preOrder;
}

void API::postOrderTrav(const ptr<const Condition> cNode,
                        ptr<list<Predication>> preOrder)
{
    if (cNode->firstOperand() && cNode->firstOperand()->op() != Condition::Node) {
        postOrderTrav(cNode->firstOperand(), preOrder);
    }
    if (cNode->secondOperand() && cNode->secondOperand()->op() != Condition::Node) {
        postOrderTrav(cNode->secondOperand(), preOrder);
    }
    if (isPredication(cNode->op())) {
        bool haveIndex1 = false;
        bool haveIndex2 = false;
        auto operand1 = cNode->firstOperand();
        auto operand2 = cNode->secondOperand();
        if (operand1->value()->type() == Column::Undefined) {
            int index = catalog->FindAttributeIndex(*(operand1->value()->name()));
            haveIndex1 = catalog->GetHaveIndex(index);
        }
        if (operand2->value()->type() == Column::Undefined) {
            int index = catalog->FindAttributeIndex(*(operand2->value()->name()));
            haveIndex2 = catalog->GetHaveIndex(index);
        }
        bool haveIndex = haveIndex1 && operand2->value()->type() != Column::Undefined ||
                haveIndex2 && operand1->value()->type() != Column::Undefined;//@@##May change
        Predication preNode(haveIndex, cNode);
        if (preNode.haveIndex) {
            preOrder->push_front(preNode);
        }
        else {
            preOrder->push_back(preNode);
        }
    }
}
auto API::queryByIndex(ptr<list<ptr<const Condition>>>)
{
    //assert one node is constant(type is not undefine) and there are two operand
    //Get offset by index
    //query recordManager by offset
    //return vector<vector<string>>
}

void API::displaySelect(const vector<string>& attrNames,const vector<RecordManager::Record>& tuples)
{	//@@##If the struture of Record should change, this function is invalid
    assert(attrNames.size() == tuples.begin()->size());
    if (tuples.size() == 0) {
        displayMsg(string("Empty set"));
    }
    else {
        size_t attrNum = attrNames.size();
        list<string> messages;
        vector<size_t> columnWidth;//he length of each attribute
        columnWidth.reserve(attrNum);
        for (int i = 0; i < attrNum; i++) {
            columnWidth.push_back((attrNames)[i].size());
        }
        for (auto record : tuples) {
            //ptr<vector<string>> line = std::make_shared<vector<string>>();
            for (int i = 0; i < attrNum; i++) {
                if (record[i].name()->size() > columnWidth[i]) {
                    columnWidth[i] = record[i].name()->size();
                }
            }
        }
        string title = "| ";
        for (int i = 0; i != attrNum; i++) {
            //@@##
            title += attrNames[i] + string(columnWidth[i]
                                           - attrNames[i].size(), ' ') + " | ";
        }
        messages.push_back(title);
        string ceiling = "+";
        if (attrNum > 0) {
            ceiling += string((messages.begin())->size() - 3, '-') + string("+ ");
        }
        messages.push_front(ceiling);
        messages.push_back(ceiling);
        for (auto record : tuples) {
            string message = "| ";//left side bar
            for (int i = 0; i != attrNum; i++) {
                //@@##
                message += *record[i].name() + string(columnWidth[i]
                                                      - record[i].name()->size(), ' ') + " | ";
            }
            messages.push_back(message);
        }
        messages.push_back(ceiling);
        string message = std::to_string(tuples.size()) + string(" tuples in set");
        messages.push_back(message);
        displayMsg(messages);
    }
}

bool API::checkSyn(ptr <const Condition> cRoot)
{
    assert(cRoot != nullptr);
    if (cRoot->op() == Condition::Node) {
        displayMsg(*(cRoot->value()->name()) + string(" is not boolean type"));
        return false;
    }
    bool ret = true;
    std::stack <ptr< const Condition >> conditionStack;
    ptr<const Condition> c = cRoot;
    //Traverse the grammar tree
    do {
        if (c) {
            conditionStack.push(c);
            c = c->firstOperand();
        }
        else {
            c = conditionStack.top();
            conditionStack.pop();
            //Do something
            if (c->op() == Condition::Node && c->value()->type() == Column::Undefined) {
                if (catalog->FindAttributeIndex(*(c->value()->name())) == -1) {
                    ret = false;
                    string missColumn = *(c->value()->name());
                    displayMsg(missColumn + string(" is not in this table"));
                    break;
                }
            }
            else if (isConjunction(c->op())) {
                if (c->op() == Condition::And || c->op() == Condition::Or) {
                    ret = false;
                    displayMsg(string("No ") + opName(c->op()) + string(" allowed"));
                    break;
                }
                if (!(c->secondOperand() && c->firstOperand())) {
                    ret = false;
                    displayMsg(string("Near ") + opName(c->op()) + string(" systax error"));
                    break;
                }
                else if (c->firstOperand()->op() == Condition::Node) {
                    ret = false;
                    string missColumn = *(c->firstOperand()->value()->name());
                    displayMsg(missColumn + string(" is not boolean type"));
                    break;
                }
                else if (c->secondOperand()->op() == Condition::Node) {
                    ret = false;
                    string missColumn = *(c->secondOperand()->value()->name());
                    displayMsg(missColumn + string(" is not boolean type"));
                    break;
                }
            }
            else if (isPredication(c->op())) {
                if (!(c->secondOperand() && c->firstOperand())) {
                    ret = false;
                    displayMsg(string("Near ") + opName(c->op()) + string(" systax error"));
                    break;
                }
                else if (!convertible(c->firstOperand()->value()->type(), c->secondOperand()->value()->type())
                         && !convertible(c->secondOperand()->value()->type(), c->firstOperand()->value()->type())) {
                    ret = false;
                    Column::Type type1 = c->firstOperand()->value()->type();
                    Column::Type type2 = c->secondOperand()->value()->type();
                    displayMsg(getTypeName(type1) + string(" is not comparable with ") + getTypeName(type2));
                    break;
                }
            }
            c = c->secondOperand();
            if (c) {
                conditionStack.push(c);
                c = c->firstOperand();
            }
        }
    } while (!conditionStack.empty());
    return ret;
}

RecordManager::Record API::getTemplateRecord()
{
    assert(catalog != nullptr);
    RecordManager::Record templateRecord;
    int attrNum = catalog->GetAttrNum();
    templateRecord.reserve(attrNum);
    for (int i = 0; i < attrNum; i++) {
        Column column;
        column.ColumnType = catalog->GetType(i);
        templateRecord.push_back(column);
    }
    return templateRecord;
}



