#include<iostream>
#include<string>
#include<fstream>
#include<cstring>

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

class catalogManager 
{
	private:
		ifstream fin;
		string Database;//数据库名字 
		string TableName;//目前找到的表名字 
		int RecordLength;//每条记录的长度 
		int AttrNum;//表属性个数
		string* Attribute;//表的属性
		string* type;//表属性的类型
		bool* IsUnique;//判断是否unique
		bool* HaveIndex;//判断是否有索引
		string* IndexName;//索引名字
		int PriIndex;//主键编号
		const char* DB;
		
		//判断catalogManager中是否存在表TableName
		bool FindTableName();
		//判断catalogManager中是否存在名字为Name的表 
		bool FindTableName(string Name);
		//设置类的属性 
		void SetAttrNum(int Num);
		void SetAttribute(string* Attr);
		void SetType(string *t);
		void SetIsUnique(bool* IsUni);
		void SetHaveIndex(bool* HavInd);
		void SetIndexName(string *IndName);
		void SetPriIndex(int PrimaryKey);
		string TableNameFromStr(string Str);
		
	public:
		//构造函数和析构函数 
		/***********************************************/ 
		catalogManager(string DBName);
		catalogManager(string DBName, string TableName);
		~catalogManager();
		/***********************************************/ 
		
		//删除数据库
		/***********************************************/ 
		void DropDatabase();
		/***********************************************/ 
		
		
		/*对catalog文件进行操作的函数*/ 
		/***********************************************/ 
		//从catalog中获取TableName的信息，放入到类的变量中 
		bool GetTableInfo();
		//从catalog中获取名字为Name的表的信息，放入到类的变量中 
		bool GetTableInfo(string Name); 
		//向catalog中添加表信息，Str为要写入的信息
		bool AddTableInfo(string Str);
		//向catalog中添加表信息，需要调用Set开头的函数，事先设置好类中的所有信息
		bool AddTableInfo(); 
		//在catalog中删除当前的表
		bool DropTable();
		//在catalog中删除名字为Name的表 
		bool DropTable(string Name);
		//在catalog中删除表Table中的名为Index的索引 
		bool DropIndex(string Table,string Index); 
		/***********************************************/ 
		
		
		
		//Set类函数，用于设置类内的信息
		/***********************************************/  
		//设置TableName
		void SetTableName(string Name);
		//设置RecordLength
		void SetRecordLength(int length);
		//设置Attribute等信息
		void SetAttributeInfo(int num,string* Attr,string *t,bool* IsUni,bool* HavInd,string *IndName,int PrimaryKey);
		/***********************************************/ 
		
		
		//以下函数用于获取类内的信息 
		/***********************************************/  
		//找到表中是否有某个属性，没有返回-1，有则返回属性数组下标
		int FindAttributeIndex(string AttrName);
		//找到根据Index名称找到数组下标，没有返回-1，有则返回属性数组下标
		int FindIndexAccordingToIndexName(string Index);
		//根据数组下标得到相应数据，数组下标可以用FindAttribute函数得到
		bool GetIsUnique(int i);
		string GetType(int i);
		bool GetHaveIndex(int i);
		string GetIndexName(int i);
		int GetRecordLength();
		int GetAttrNum();
		int GetPriIndex();
		//返回主键名称
		string GetPrimaryKey(); 
		/***********************************************/ 
		
		
		//一些其他函数 
		/***********************************************/ 
		//删除类里的所有信息
		void Clear();
		//从catalog中获取数据并且打印表信息 
		void PrintInfo();
		/***********************************************/ 
		
		
};

catalogManager::catalogManager(string DBName):
Database(DBName),AttrNum(0),Attribute(NULL),type(NULL),IsUnique(NULL),HaveIndex(NULL),IndexName(NULL) 
{
	DB = Database.c_str();
	fin.open(DB);
}

catalogManager::catalogManager(string DBName, string TableName):
Database(DBName),AttrNum(0),TableName(TableName),Attribute(NULL),type(NULL),IsUnique(NULL),HaveIndex(NULL),IndexName(NULL) 
{
	DB = Database.c_str();
	fin.open(DB);
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
	Attribute = NULL;
	type = NULL;
	IsUnique = NULL;
	HaveIndex = NULL;
	IndexName = NULL;
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
	remove(DB);
	rename("tmp.txt",DB);
	fin.open(DB);
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
	type = new string[AttrNum];
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
	type = new string[AttrNum];
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
	int j;
	Attribute = new string[AttrNum];
	for(int i = 0; i < AttrNum; i++)
	{
		j = 0;
		while(Attr[i][j])
		{
			Attribute[i] += Attr[i][j];
			j++;
		}
	}
}

void catalogManager::SetType(string* t)
{
	int j;
	type = new string[AttrNum];
	for(int i = 0; i < AttrNum; i++)
	{
		j = 0;
		while(t[i][j])
		{
			type[i] += t[i][j];
			j++;
		}
	}
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

void catalogManager::SetIndexName(string* IndName)
{
	int j;
	IndexName = new string[AttrNum];
	for(int i = 0; i < AttrNum; i++)
	{
		if(HaveIndex[i])
		{
			j = 0;
			while(IndName[i][j])
			{
				IndexName[i] += IndName[i][j];
				j++;
			}
		}
	}
}

void catalogManager::SetAttributeInfo(int Num,string* Attr,string *t,bool* IsUni,bool* HavInd,string *IndName,int PrimaryKey)
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
	fin.open(DB);
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
	
	ofstream fout(DB,ios::app);
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
	fin.open(DB);
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
	remove(DB);
	rename("tmp.txt",DB);
	fin.open(DB);
	cout<<"Query OK!"<<endl;
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
	remove(DB);
	rename("tmp.txt",DB);
	fin.open(DB);
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
}

bool catalogManager::GetIsUnique(int i)
{
	return IsUnique[i];
}
string catalogManager::GetType(int i)
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
	remove(DB);
	cout<<"Query OK!\n";
}

string catalogManager::TableNameFromStr(string Str)
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
	string type[2] = {"char(12)","int"};
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
