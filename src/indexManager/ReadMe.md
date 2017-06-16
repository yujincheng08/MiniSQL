# Index Manager

## Class Usage:

### bpTree Class
This class demonstrates a B+ Tree, which is an index manager.
``` C++
    bpTree();     This is the constructor. </br>
    ~bpTree();    This is the destructor.</br>
    void Insert_node(const T &, const pos_type &);           Insert a tuple into the B+ Tree</br>
    bool Del_data(const T & ckey);                           Delete a tuple from the B+ Tree</br>
    void Index(const string &);                   To create a index file out of the B+ Tree</br>
    void Buildtree(const string &);               Tp create a B+ Tree from the index file</br>
    void Show();                            show the B+ Tree (For test)</br>
```



