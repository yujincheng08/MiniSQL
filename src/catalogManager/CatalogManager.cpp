#include "CatalogManager.h"
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

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

catalogManager::catalogManager(string DBName, string TableName):
Database(DBName),TableName(TableName)
{
    fin.open(Database);
}

catalogManager::~catalogManager()
{
	fin.close();
	if(Attribute)
		delete[] Attribute;
	if(type)
		delete[] type;
	if(IsUnique)
		delete[] IsUnique;
	if(HaveIndex)
		delete[] HaveIndex;
	if(IndexName)
		delete[] IndexName;
}	

void catalogManager::Clear()
{
	if(Attribute)
		delete[] Attribute;
	if(type)
		delete[] type;
	if(IsUnique)
		delete[] IsUnique;
	if(HaveIndex)
		delete[] HaveIndex;
	if(IndexName)
		delete[] IndexName;
    Attribute = nullptr;
    type = nullptr;
    IsUnique = nullptr;
    HaveIndex = nullptr;
    IndexName = nullptr;
	Database = "\0";
	TableName = "\0";
	AttrNum = 0;
	PriIndex = -1;
	RecordLength = 0;
}

bool catalogManager::DropIndex(string Table,string Index)
{
	//查找是否有表 
	if(FindTableName(Table) == false)
	{
		cout<<"No such table!"<<endl;
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
		cout<<"No such index!"<<endl;
		return false;
	}
	if(i == Pri)
	{
		delete[] AName;
		delete[] t;
		delete[] IsUni;
		delete[] HavInd;
		delete[] IndName;
		cout<<"Cannot delete the index of primary key!"<<endl;
		return false;
	}
	//修改信息 
	HavInd[i] = false;
	
	ofstream fout("tmp.txt");
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
    rename("tmp.txt",Database.c_str());
    fin.open(Database);
	cout<<"Query OK!"<<endl;
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

bool catalogManager::FindTableName(string Name)
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
	if(FindTableName() == false)
	{
		cout<<"No such table!"<<endl;
		return false;
	}
	fin>>RecordLength;
	fin>>AttrNum;
	Attribute = new string[AttrNum];
	type = new unsigned int[AttrNum];
	IsUnique = new bool[AttrNum];
	HaveIndex = new bool[AttrNum];
	IndexName = new string[AttrNum]; 
	for(int i = 0; i < AttrNum; i++)
	{
		fin>>Attribute[i]>>type[i]>>IsUnique[i]>>HaveIndex[i];
		if(HaveIndex[i])
			fin>>IndexName[i];
	}
	fin>>PriIndex;
	return true;
}

bool catalogManager::GetTableInfo(string Name)
{
	SetTableName(Name);
	if(FindTableName() == false)
	{
		cout<<"No such table!"<<endl;
		return false;
	}
	fin>>RecordLength;
	fin>>AttrNum;
	Attribute = new string[AttrNum];
	type = new unsigned int[AttrNum];
	IsUnique = new bool[AttrNum];
	HaveIndex = new bool[AttrNum];
	IndexName = new string[AttrNum]; 
	for(int i = 0; i < AttrNum; i++)
	{
		fin>>Attribute[i]>>type[i]>>IsUnique[i]>>HaveIndex[i];
		if(HaveIndex[i])
			fin>>IndexName[i];
	}
	fin>>PriIndex;
	return true;
}

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

void catalogManager::SetTableName(string Name)
{
	TableName = Name;
}

void catalogManager::SetRecordLength(int length)
{
	RecordLength = length;
}

void catalogManager::SetAttrNum(int Num)
{
	AttrNum = Num;
}

void catalogManager::SetPriIndex(int PrimaryKey)
{
	PriIndex = PrimaryKey;
}

void catalogManager::SetAttribute(string* Attr)
{
    Attribute = new string[AttrNum];
	for(int i = 0; i < AttrNum; i++)
        Attribute[i] = Attr[i];
}

void catalogManager::SetType(const unsigned int* t)
{
	type = new unsigned int[AttrNum];
	for(int i = 0; i < AttrNum; i++)
        type[i] = t[i];
}

void catalogManager::SetIsUnique(bool* IsUni)
{
	IsUnique = new bool[AttrNum];
	for(int i = 0; i < AttrNum; i++)
	{
		IsUnique[i] = IsUni[i];
	}
}

void catalogManager::SetHaveIndex(bool* HavInd)
{
	HaveIndex = new bool[AttrNum];
	for(int i = 0; i < AttrNum; i++)
	{
		HaveIndex[i] = HavInd[i];
	}
}

void catalogManager::SetIndexName(const string *IndName)
{
	IndexName = new string[AttrNum];
    for(int i = 0; i < AttrNum; i++)
        if(HaveIndex[i])
            IndexName[i] = IndName[i];
}

void catalogManager::SetAttributeInfo(int Num,string* Attr,unsigned int *t,bool* IsUni,bool* HavInd,string *IndName,int PrimaryKey)
{
	SetAttrNum(Num);
	SetAttribute(Attr);
	SetType(t);
	SetIsUnique(IsUni);
	SetHaveIndex(HavInd);
	SetIndexName(IndName);
	SetPriIndex(PrimaryKey);
}

bool catalogManager::AddTableInfo(string Str)
{
	fin.seekg(0,ios::beg);
	string Name = TableNameFromStr(Str);
	if(FindTableName(Name) == true)
	{
		cout<<"Table Exists!"<<endl;
		return false;
	}
	ofstream fout("catalogManager.txt",ios::app);
	fout<<Str<<endl;
	fout.close();
	//update fin
	fin.close();
    fin.open(Database);
	cout<<"Query OK!"<<endl;
	return true;
}

bool catalogManager::AddTableInfo()
{
	fin.seekg(0,ios::beg);
	if(FindTableName() == true)
	{
		cout<<"Table Exists!"<<endl;
		return false;
	}
	
    ofstream fout(Database,ios::app);
	fout<<TableName<<" "<<RecordLength<<" "<<AttrNum<<" ";
	for(int i = 0; i < AttrNum; i++)
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
	cout<<"Query OK!"<<endl;
	return true;
} 

int catalogManager::FindAttributeIndex(string AttrName)
{
	for(int i = 0; i < AttrNum; i++)
	{
		if(Attribute[i] == AttrName)
			return i;
	}
	return -1;
}

int catalogManager::FindIndexAccordingToIndexName(string Index)
{
	for(int i = 0; i < AttrNum; i++)
	{
		if(HaveIndex[i]) 
		if(IndexName[i] == Index)
			return i;
	}
	return -1;
}

bool catalogManager::DropTable(string Name)
{
	if(FindTableName(Name) == false)
	{
		cout<<"No such table!"<<endl;
		return false;
	}
	ofstream fout("tmp.txt");
	
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
    rename("tmp.txt",Database.c_str());
    fin.open(Database);
    error("Query OK!\n");
	return true;
}

bool catalogManager::DropTable()
{
	if(FindTableName() == false)
	{
		cout<<"No such table!"<<endl;
		return false;
	}
	ofstream fout("tmp.txt");
	
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
    rename("tmp.txt",Database.c_str());
    fin.open(Database);
	cout<<"Query OK"<<endl;
	return true;
}


string catalogManager::GetPrimaryKey()
{
	for(int i = 0; i < AttrNum; i++)
	{
		if(i == PriIndex)
			return Attribute[i];
	}
    return string();
}

bool catalogManager::GetIsUnique(int i)
{
	return IsUnique[i];
}
int catalogManager::GetType(int i)
{
	return type[i];
}
bool catalogManager::GetHaveIndex(int i)
{
	return HaveIndex[i];
}
string catalogManager::GetIndexName(int i)
{
	return IndexName[i];
}
int catalogManager::GetRecordLength()
{
	return RecordLength;
}
int catalogManager::GetAttrNum()
{
	return AttrNum;
}
int catalogManager::GetPriIndex()
{
	return PriIndex;
}

void catalogManager::DropDatabase()
{
    remove(Database.c_str());
	cout<<"Query OK!\n";
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

int main()
{
	CreateDatabase("a.txt");
	catalogManager s("a.txt","Teacher");
	//插入信息例子1
	int AttrNum = 2;
	string Attribute[2] = {"Name","Age"};
	string type[2] = {12,256};
	bool HaveIndex[2] = {true,true};
	string IndexName[2] = {"NameIndex","AgeIndex"};
	bool IsUnique[2] = {true,true};
	int PrimaryKey = 0;
	int RecordLen = 16; 
	s.SetAttributeInfo(AttrNum,Attribute,type,IsUnique,HaveIndex,IndexName,PrimaryKey);
	s.SetRecordLength(RecordLen);
	s.AddTableInfo();
	//插入信息例子2
	s.SetTableName("student");
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
	 
}
