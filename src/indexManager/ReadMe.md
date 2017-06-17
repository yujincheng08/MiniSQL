# Index Manager

## Class Usage:

### bpTree Class
This class demonstrates a B+ Tree, which is an index manager.
``` C++
    bpTree();     This is the constructor.
    ~bpTree();    This is the destructor.</br>
    void Insert_node(const T &, const pos_type &);           Insert a tuple into the B+ Tree
    bool Del_data(const T & ckey);                           Delete a tuple from the B+ Tree
    void Index(const string &);                   To create a index file out of the B+ Tree
    void Buildtree(const string &);               Tp create a B+ Tree from the index file
    void Show();                            show the B+ Tree (For test)
    
    // 以下是查询相关的函数，返回查询键值对应的文件位置
    vector<pos_type> Eqsearch(const T & key);  //等值查询   
    vector<pos_type> Neqsearch(const T & key); //不等查询
    vector<pos_type> Besearch(const T & key);  //大于等于
    vector<pos_type> Bsearch(const T & key);   //大于
    vector<pos_type> Ssearch(const T & key);   //小于等于
    vector<pos_type> Sesearch(const T & key);  //小于
```



