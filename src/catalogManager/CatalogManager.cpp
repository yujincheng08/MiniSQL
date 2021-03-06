#include "CatalogManager.h"
#include<iostream>
#include<string>
#include<fstream>

using namespace std;
#ifdef TEST
void CreateDatabase(const char* DB)
{
	ifstream fin(DB);
	if(fin.is_open())
	{
		cout<<"Database exists!"<<endl;
		return;
	}
	ofstream fout(DB);
	fout.close();
	cout<<"Query OK!\n";
}

#endif

void catalogManager::Clear()
{
    Attribute.clear();
    type.clear();
    IsUnique.clear();
    HaveIndex.clear();
    IndexName.clear();
	TableName = "\0";
	AttrNum = 0;
	PriIndex = -1;
	RecordLength = 0;
}

bool catalogManager::DropIndex(const string &Table,const string &Index)
{
	//查找是否有表 
	if(FindTableName(Table) == false)
	{
        error("No such table!");
		return false;
	}
	
	bool exist = false;
	int num;
	int RLen;
	fin>>RLen>>num;
	
	string *AName;
	string *t;
	bool *IsUni;
	bool *HavInd;
	string *IndName;
	int Pri;
	int i;
	
	AName = new string[num];
	t = new string[num];
	IsUni = new bool[num];
	HavInd = new bool[num];
	IndName = new string[num];
	//读入表信息 
	for(i = 0; i < num; i++)
	{
		fin>>AName[i]>>t[i]>>IsUni[i]>>HavInd[i];
		if(HavInd[i])
			fin>>IndName[i];
	}
	fin>>Pri;
	//检查index是否存在 
	for(i = 0; i < num; i++)
	{
		if(HavInd[i] && IndName[i] == Index)
		{
			exist = true;
			break;
		}
	}
	//index不存在，提示错误信息 
	if(exist == false)
	{
		delete[] AName;
		delete[] t;
		delete[] IsUni;
		delete[] HavInd;
		delete[] IndName;
        error("No such index!");
		return false;
	}
	if(i == Pri)
	{
		delete[] AName;
		delete[] t;
		delete[] IsUni;
		delete[] HavInd;
		delete[] IndName;
        error("Cannot delete the index of primary key!");
		return false;
	}
	//修改信息 
	HavInd[i] = false;
	
    ofstream fout("tmp.cat");
	string tmp,Name;
	fin.seekg(0,ios::beg);
	while(fin>>Name)
	{
		if(Name == Table)
		{
			getline(fin,tmp);
		}
		else
		{
			getline(fin,tmp);
			fout<<Name<<tmp<<endl;
		}
	}
	fout<<Table<<" "<<RLen<<" "<<num<<" ";
	for(i = 0; i < num; i++)
	{
		fout<<AName[i]<<" "<<t[i]<<" "<<IsUni[i]<<" "<<HavInd[i]<<" ";
		if(HavInd[i])
			fout<<IndName[i]<<" ";
	}
	fout<<Pri<<endl;
	
	delete[] AName;
	delete[] t;
	delete[] IsUni;
	delete[] HavInd;
	delete[] IndName;
	
	fin.close();
	fout.close();
    remove(Database.c_str());
    rename("tmp.cat",Database.c_str());
    fin.open(Database);
    //cout<<"Query OK!"<<endl;
	return true;
}

bool catalogManager::FindTableName()
{
	string tmp,Table;
	fin.seekg(0,ios::beg);
	while(fin>>Table)
	{
		if(TableName == Table)
			return true;
		else
			getline(fin,tmp);
	}
	return false;
}

bool catalogManager::FindTableName(const string &Name)
{
	string tmp,Table;
	fin.seekg(0,ios::beg);
	while(fin>>Table)
	{
		if(Name == Table)
			return true;
		else
			getline(fin,tmp);
	}
	return false;
}

bool catalogManager::GetTableInfo()
{

    Attribute.clear();
    type.clear();
    IsUnique.clear();
    HaveIndex.clear();
    IndexName.clear();
    AttrNum = 0;
    PriIndex = -1;
    RecordLength = 0;

	if(FindTableName() == false)
	{
        error("No such table!");
		return false;
	}
	fin>>RecordLength;
	fin>>AttrNum;
    string Attr;
    unsigned int t;
    bool IsUni;
    bool HaveInd;
    string IndName;
    for(size_t i = 0; i < AttrNum; i++)
	{
        fin>>Attr>>t>>IsUni>>HaveInd;
        Attribute.push_back(Attr);
        type.push_back(t);
        IsUnique.push_back(IsUni);
        HaveIndex.push_back(HaveInd);
        if(HaveInd)
        {
            fin>>IndName;
            IndexName.push_back(IndName);
        }
        else
        {
            IndexName.push_back("\0");
        }
	}
	fin>>PriIndex;
	return true;
}

bool catalogManager::GetTableInfo(const string &Name)
{
    Attribute.clear();
    type.clear();
    IsUnique.clear();
    HaveIndex.clear();
    IndexName.clear();
    AttrNum = 0;
    PriIndex = -1;
    RecordLength = 0;

	SetTableName(Name);
    if(FindTableName() == false)
    {
        error("No such table!");
        return false;
    }
    fin>>RecordLength;
    fin>>AttrNum;
    string Attr;
    unsigned int t;
    bool IsUni;
    bool HaveInd;
    string IndName;
    for(size_t i = 0; i < AttrNum; i++)
    {
        fin>>Attr>>t>>IsUni>>HaveInd;
        Attribute.push_back(Attr);
        type.push_back(t);
        IsUnique.push_back(IsUni);
        HaveIndex.push_back(HaveInd);
        if(HaveInd)
        {
            fin>>IndName;
            IndexName.push_back(IndName);
        }
        else
        {
            IndexName.push_back("\0");
        }
    }
    fin>>PriIndex;
    return true;
}
#ifdef TEST
void catalogManager::PrintInfo()
{
	if(GetTableInfo() == true)
	{
		cout<<"TableName: "<<TableName<<endl;
		cout<<"Attribute Info: "<<endl;
		for(int i = 0; i < AttrNum; i++)
		{
			if(IsUnique[i])
				cout<<"\t"<<Attribute[i]<<"\t"<<type[i]<<"\tunique";
			else
				cout<<"\t"<<Attribute[i]<<"\t"<<type[i];
			if(HaveIndex[i])
				cout<<"\t"<<IndexName[i]<<endl;
			else
				cout<<"\t"<<endl;
		}
		cout<<"Primary key: "<<Attribute[PriIndex]<<endl;	
		cout<<"Record length: "<<RecordLength<<endl;
	}
}
#endif
/*
void catalogManager::SetAttributeInfo(const int Num,const string* Attr,const unsigned int* t,const bool* IsUni,const bool* HavInd,const string* IndName,const int PrimaryKey)
{
    SetAttrNum(Num);

    for(int i = 0; i < Num; i++)
    {
        Attribute.push_back(Attr[i]);
        type.push_back(t[i]);
        IsUnique.push_back(IsUni[i]);
        HaveIndex.push_back(HavInd[i]);
        if(HavInd[i])
            IndexName.push_back(IndName[i]);
        else
            IndexName.push_back("\0");

    }

    SetPriIndex(PrimaryKey);

    int RLen = 0;
    for(int i = 0; i < Num; i++)
    {
        if(t[i] == 256 || t[i] == 257)
            RLen += 4;
        else
            RLen += t[i];
    }
    SetRecordLength(RLen);
}
*/

void catalogManager::SetAttributeInfo(const int Num,const vector<string> &Attr,const vector<unsigned int> &t,const vector<bool> &IsUni,const vector<bool> &HavInd,const vector<string> &IndName,const int PrimaryKey)
{
	SetAttrNum(Num);
	SetAttribute(Attr);
	SetType(t);
	SetIsUnique(IsUni);
	SetHaveIndex(HavInd);
	SetIndexName(IndName);
	SetPriIndex(PrimaryKey);
    int RLen = 0;
    for(int i = 0; i < Num; i++)
    {
        if(t[i] == 256 || t[i] == 257)
            RLen += 4;
        else
            RLen += t[i];
    }
    SetRecordLength(RLen);
}

bool catalogManager::AddTableInfo(const string &Str)
{
	fin.seekg(0,ios::beg);
	string Name = TableNameFromStr(Str);
	if(FindTableName(Name) == true)
	{
        error("Table Exists!");
		return false;
	}
    ofstream fout("catalogManager.cat",ios::app);
	fout<<Str<<endl;
	fout.close();
	//update fin
	fin.close();
    fin.open(Database);
    //cout<<"Query OK!"<<endl;
	return true;
}

bool catalogManager::AddTableInfo()
{
	fin.seekg(0,ios::beg);
	if(FindTableName() == true)
	{
        error("Table Exists!");
		return false;
	}
	
    ofstream fout(Database,ios::app);
	fout<<TableName<<" "<<RecordLength<<" "<<AttrNum<<" ";
    for(size_t i = 0; i < AttrNum; i++)
	{
		fout<<Attribute[i]<<" "<<type[i]<<" "<<IsUnique[i]<<" "<<HaveIndex[i]<<" ";
		if(HaveIndex[i])
			fout<<IndexName[i]<<" ";
	}
	fout<<PriIndex<<endl;
	fout.close();
	//update fin
	fin.close();
    fin.open(Database);
    //cout<<"Query OK!"<<endl;
	return true;
} 

ssize_t catalogManager::FindAttributeIndex(const string &AttrName)
{
    for(size_t i = 0; i < AttrNum; i++)
		if(Attribute[i] == AttrName)
			return i;
	return -1;
}

ssize_t catalogManager::FindIndexAccordingToIndexName(const string &Index)
{
    for(size_t i = 0; i < AttrNum; i++)
	{
		if(HaveIndex[i]) 
		if(IndexName[i] == Index)
			return i;
	}
	return -1;
}

bool catalogManager::DropTable(const string &Name)
{
	if(FindTableName(Name) == false)
	{
        error("No such table!");
		return false;
	}
    ofstream fout("tmp.cat");
	
	string tmp,Table;
	fin.seekg(0,ios::beg);
	while(fin>>Table)
	{
		if(TableName == Table)
		{
			getline(fin,tmp);
		}
		else
		{
			getline(fin,tmp);
			fout<<Table<<tmp<<endl;
		}
	}
	fin.close();
	fout.close();
    remove(Database.c_str());
    rename("tmp.cat",Database.c_str());
    fin.open(Database);
    //error("Query OK!\n");
	return true;
}

bool catalogManager::DropTable()
{
	if(FindTableName() == false)
	{
        error("No such table!");
		return false;
	}
    ofstream fout("tmp.cat");
	
	string tmp,Table;
	fin.seekg(0,ios::beg);
	while(fin>>Table)
	{
		if(TableName == Table)
		{
			getline(fin,tmp);
		}
		else
		{
			getline(fin,tmp);
			fout<<Table<<tmp<<endl;
		}
	}
	fin.close();
	fout.close();
    remove(Database.c_str());
    rename("tmp.cat",Database.c_str());
    fin.open(Database);
    //cout<<"Query OK"<<endl;
	return true;
}
bool catalogManager::CreateIndex(const string& Table,const string& Attr, const string& Index)
{
    //查找是否有表
    if(FindTableName(Table) == false)
    {
        error("No such table!");
        return false;
    }

    int num;
    int RLen;
    fin>>RLen>>num;

    string *AName;
    string *t;
    bool *IsUni;
    bool *HavInd;
    string *IndName;
    int Pri;
    int i;

    AName = new string[num];
    t = new string[num];
    IsUni = new bool[num];
    HavInd = new bool[num];
    IndName = new string[num];
    //读入表信息
    for(i = 0; i < num; i++)
    {
        fin>>AName[i]>>t[i]>>IsUni[i]>>HavInd[i];
        if(HavInd[i])
            fin>>IndName[i];
    }
    fin>>Pri;

    int AttrInd = FindAttributeIndex(Attr);
    if(AttrInd == -1)
    {
        error("Create Index failed! No such Attribute!");
        delete[] AName;
        delete[] t;
        delete[] IsUni;
        delete[] HavInd;
        delete[] IndName;
        return false;
    }
    if(HavInd[AttrInd] == true)
    {
        error("Create Index failed! Index exists!");
        delete[] AName;
        delete[] t;
        delete[] IsUni;
        delete[] HavInd;
        delete[] IndName;
        return false;
    }

    //修改信息
    HavInd[AttrInd] = true;
    IndName[AttrInd] = Index;

    ofstream fout("tmp.cat");
    string tmp,Name;
    fin.seekg(0,ios::beg);
    while(fin>>Name)
    {
        if(Name == Table)
        {
            getline(fin,tmp);
        }
        else
        {
            getline(fin,tmp);
            fout<<Name<<tmp<<endl;
        }
    }
    fout<<Table<<" "<<RLen<<" "<<num<<" ";
    for(i = 0; i < num; i++)
    {
        fout<<AName[i]<<" "<<t[i]<<" "<<IsUni[i]<<" "<<HavInd[i]<<" ";
        if(HavInd[i])
            fout<<IndName[i]<<" ";
    }
    fout<<Pri<<endl;

    delete[] AName;
    delete[] t;
    delete[] IsUni;
    delete[] HavInd;
    delete[] IndName;

    fin.close();
    fout.close();
    remove(Database.c_str());
    rename("tmp.cat",Database.c_str());
    fin.open(Database);
    //cout<<"Query OK!"<<endl;
    return true;
}



void catalogManager::DropDatabase()
{
    remove(Database.c_str());
    //cout<<"Query OK!\n";
}

string catalogManager::TableNameFromStr(const string &Str)
{
	int i = 0;
	string tmp;
	while(Str[i] != ' ')
	{
		tmp += Str[i];
		i++;
	}
	return tmp;
}

#ifdef TEST
int main()
{
    //CreateDatabase("a.txt");
	catalogManager s("a.txt","Teacher");
    //插入信息例子1
    int AttrNum = 2;
	string Attribute[2] = {"Name","Age"};
    unsigned int type[2] = {12,256};
	bool HaveIndex[2] = {true,true};
	string IndexName[2] = {"NameIndex","AgeIndex"};
	bool IsUnique[2] = {true,true};
	int PrimaryKey = 0;
    //设置信息
    vector<string> Attr(Attribute, Attribute + 2);
    vector<unsigned int> t(type, type + 2);
    vector<bool> HavInd(HaveIndex, HaveIndex + 2);
    vector<bool> IsUni(IsUnique, IsUnique + 2);
    vector<string> IndName(IndexName, IndexName + 2);
    s.SetAttributeInfo(AttrNum,Attr,t,IsUni,HavInd,IndName,PrimaryKey);
    //也可以传入数组
    //s.SetAttributeInfo(AttrNum,Attribute,type,IsUnique,HaveIndex,IndexName,PrimaryKey);
    s.AddTableInfo();

	//插入信息例子2
	s.SetTableName("student");
    s.SetAttributeInfo(AttrNum,Attr,t,IsUni,HavInd,IndName,PrimaryKey);
	s.AddTableInfo();

    //获取表信息1
	s.GetTableInfo();
	s.PrintInfo();
    //获取表信息2
	s.GetTableInfo("Teacher");
	s.PrintInfo();
    //删除index
	s.DropIndex("Teacher","AgeIndex");
	s.SetTableName("Teacher");
	s.PrintInfo();
    //添加index
    s.CreateIndex("Teacher","Age","AgeIndex");
    s.SetTableName("Teacher");
    s.PrintInfo();

}

#endif
