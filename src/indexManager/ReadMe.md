# Index Manager

## Class Usage:

### bpTree Class
This class demonstrates a B+ Tree, which is an index manager.

>   bpTree();     This is the constructor.
    ~bpTree();    This is the destructor.
    void Insert_node(const T &, const pos_type &);           Insert a tuple into the B+ Tree
    bool Del_data(const T & ckey);                           Delete a tuple from the B+ Tree
    void Index(const string &);                   To create a index file out of the B+ Tree
    void Buildtree(const string &);               Tp create a B+ Tree from the index file
    void Show();                            show the B+ Tree (For test)



