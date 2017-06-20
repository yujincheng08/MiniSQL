#include "BpTreeCtrl.h"

BpTreeCtrl::BpTreeCtrl(ptr<catalogManager> inCatalog)
{
    catalog = inCatalog;
    auto attrNum = catalog->GetAttrNum();
    auto attrName = catalog->GetAttrName();
    vector<string> indName;
    for(size_t i=0U;i<attrNum;i++){
        indName.push_back(tableName+string("_")+attrName[i]+string("_index"));
    }
    for(size_t i = 0U;i<attrNum;i++){
        if(catalog->GetIsUnique(i)){
            if(isChar(catalog->GetType(i))){
                auto tree = std::make_shared<bpTree<FixString>>();
                tree->Buildtree(indName[i],catalog->GetType(i));
                strTree.insert(make_pair(indName[i],tree));
            }
            else if(catalog->GetType(i) == Column::Int){
                auto tree = std::make_shared<bpTree<int>>();
                tree->Buildtree(indName[i]);
                intTree.insert(make_pair(indName[i],tree));
            }
            else if(catalog->GetType(i) == Column::Float){
                auto tree = std::make_shared<bpTree<float>>();
                tree->Buildtree(indName[i]);
                floatTree.insert(make_pair(indName[i],tree));
            }
        }
    }
}

BpTreeCtrl::~BpTreeCtrl()
{
    for(auto treeMap:strTree){
        treeMap.second->Index(treeMap.first);
    }
    for(auto treeMap:intTree){
        treeMap.second->Index(treeMap.first);
    }
    for(auto treeMap:floatTree){
        treeMap.second->Index(treeMap.first);
    }
}


bool BpTreeCtrl::checkViolate(const Record& tuple)
{
    auto attrNum = catalog->GetAttrNum();
    auto attrName = catalog->GetAttrName();
    bool violate;
    for (size_t i = 0U; i < attrNum;i++){
        if(catalog->GetIsUnique(i)){
            string indTempName = tableName+string("_")+attrName[i]+string("_index");
            auto type = catalog->GetType(i);
            auto set = queryByIndex(indTempName,*(tuple[i].name()),type, Condition::Equal);
            violate = set.size() > 0;
        }
    }
    return violate;
}

void BpTreeCtrl::dropIndices()
{//Call when drop table
    for(auto tree:strTree)
        bpTree<FixString>::DropIndex(tree.first);
    for(auto tree:intTree)
        bpTree<int>::DropIndex(tree.first);
    for(auto tree:floatTree)
        bpTree<float>::DropIndex(tree.first);
}

std::vector<File::pos_type> BpTreeCtrl::queryByIndex(const string& indName, const string& value, Column::Type type, Condition::Type opType)
{
    vector<File::pos_type> offsets;
    if (isChar(type)) {
        auto value2 = FixString(value);
        value2.resize(type);
        offsets = query(strTree[indName],value2,opType);
    }
    else if (type == Column::Float) {
        float value2 = std::stof(value);
        offsets = query(floatTree[indName],value2,opType);
    }
    else if (type == Column::Int) {
        int value2 = std::stoi(value);
        offsets = query(intTree[indName],value2,opType);
    }
    return offsets;
}

template <typename T>
vector<File::pos_type> BpTreeCtrl::query(ptr<bpTree<T>> tree,T value2,Condition::Type opType)
{
    switch (opType)
    {
    case Condition::NotEqual:
        return tree->Neqsearch(value2);
        break;
    case Condition::Equal:
        return tree->Eqsearch(value2);
        break;
    case Condition::GreaterThan:
        return tree->Bsearch(value2);
        break;
    case Condition::LessThan:
        return tree->Ssearch(value2);
        break;
    case Condition::LessEqual:
        return tree->Sesearch(value2);
        break;
    case Condition::GreaterEqual:
        return tree->Besearch(value2);
    default:
        return vector<File::pos_type>();
        break;
    }
}

void BpTreeCtrl::delData(const Record& record)
{
    auto attrNum = catalog->GetAttrNum();
    auto attrName = catalog->GetAttrName();
    for(size_t i =0U;i<attrNum;i++){
        if(catalog->GetIsUnique(i)){
            string indName = tableName+string("_")+attrName[i]+string("_index");
            auto type = catalog->GetType(i);
            if(isChar(type)){
                strTree[indName]->Del_data(FixString(formalize(*record[i].name(),type)));
            }
            else if(type == Column::Float){
                float value = std::stof(*record[i].name());
                floatTree[indName]->Del_data(value);
            }
            else if(type == Column::Int){
                int value = std::stoi(*record[i].name());
                intTree[indName]->Del_data(value);
            }
        }
    }
}

void BpTreeCtrl::insData(File::pos_type pos, const Record& tuple)
{
    auto attrNum = catalog->GetAttrNum();
    auto attrName = catalog->GetAttrName();
    for (size_t i = 0U; i < attrNum; i++) {
        //bool haveInd = catalog->GetHaveIndex(i);
        bool isuni = catalog->GetIsUnique(i);
        if (isuni) {
            string indName = tableName+string("_")+attrName[i]+string("_index");
            auto type = catalog->GetType(i);
            if (isChar(type)) {
                strTree[indName]->Insert_node(FixString(formalize(*tuple[i].name(),type)), pos);
            }
            else if (type == Column::Int) {
                intTree[indName]->Insert_node(std::stoi(*tuple[i].name()), pos);
            }
            else if (type == Column::Float) {
                floatTree[indName]->Insert_node(std::stof(*tuple[i].name()), pos);
            }
        }
    }
}

void BpTreeCtrl::index(Column::Type type, const string& indTempName)
{
    if(isChar(type)){
        bpTree<FixString> tree;
        tree.Index(indTempName);
    }
    else if(type == Column::Float){
        bpTree<float> tree;
        tree.Index(indTempName);
    }
    else if(type == Column::Int){
        bpTree<int> tree;
        tree.Index(indTempName);
    }
}
