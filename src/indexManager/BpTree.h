#ifndef BPTREE_H_
#define BPTREE_H_

#include <vector>
#include <string>
#include <type_traits>
#include "../BufferManager/BufferManager.h"
#include "../BufferManager/File.h"

template<class T>
class bpTree
{
    using string = std::string;
    template<typename K>
    using vector = std::vector<K>;
    using pos_type = File::pos_type;
    constexpr static int N = 7;
    class pri
    {
        friend class bpTree;
        pri(){}
    };
public:
    struct node
    {
        int no;                         //本节点的数据个数
        int isLeaf;                     //叶节点的标志
        pos_type dataPos[N];            //叶节点存放纵向地址
        T key[N];                       //存放关键字
        node* childNode[N + 1];             //非叶节点存放纵向地址
        node* fatherNode;               //存放父节点地址
        node* nextNode;                 //节点存放横向地址
        node* brother;                  //删除时用到的兄弟节点

        node()
        {
            nextNode = nullptr;
            brother = nullptr;
            fatherNode = nullptr;
            no = 0;
            isLeaf = 0;
            for (int i = 0; i < N; i++)
            {
                childNode[i] = nullptr;
                dataPos[i] = 0;
            }
            childNode[N] = nullptr;
        }
    };

    struct tnode
    {
        int no;                     //本节点的数据个数
        pos_type dataPos[N];         //叶节点存放纵向地址
        T key[N];                   //存放关键字
    };

    //constructor
    bpTree();
    ~bpTree();

    //others
    bool Isleaf(node* & node) const;                      //检测是否叶节点
    bool Isroot(node* & nodeposition) const;        //检测是否根结点
    void findLeaf(const T & the_key);                   //叶结点查找函数

    vector<pos_type> Eqsearch(const T & key);
    vector<pos_type> Neqsearch(const T & key);
    vector<pos_type> Besearch(const T & key);
    vector<pos_type> Bsearch(const T & key);
    vector<pos_type> Ssearch(const T & key);
    vector<pos_type> Sesearch(const T & key);

    bool Insert_node(const T &, const pos_type &);            //数据插入
    void Resize_leaf();                             //分裂叶节点
    void Resize_nleaf();                            //分裂非叶节点

    bool Del_data(const T & ckey);                        //删除
    void del(const T & k);                                //
    void Merge();                                   //删除中调整合并
    void MergeLeaf();

    template <typename It> int compare(const It &, const It &);

    void Index(const string &);                   //建立索引文件

    static void DropIndex (const string &);         //删除索引文件

    template<typename Q=T>
    void Buildtree(const string &, typename std::enable_if<!std::is_same<Q, FixString>::value, pri>::type = pri());               //建立b＋树

    template<typename Q=T>
    void Buildtree(const string &, typename std::enable_if<std::is_same<Q, FixString>::value, size_t>::type size);               //建立b＋树

    void resetKey(const node *);

#ifdef TEST
    void Show();
#endif
private:
    node* headNode;
    node* treeRoot;                               //实例的根结点
    node* posNode;
    int totalData;                                    //记录数据的总数
    bool opFlag;                                     //标志是否操作过
};




//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
//－－－－－－－－－－－模板类的成员函数声明－－－－－－－－－－－－－－－－－－－－－
//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－


//－－－－－－－－－－－构造函数－－－－－－－－－－－－－

template<class T>
bpTree<T>::bpTree()
{
    totalData = 0;
    headNode = new node;
    opFlag = false;
    headNode->isLeaf = 1;
    treeRoot = headNode;
    posNode = headNode;
}

//－－－－－－－－－－－析构函数－－－－－－－－－－－－－

template<class T>
bpTree<T>::~bpTree()
{
    node* temp = treeRoot;
    node* temp1; node* temp2;
    for (; Isleaf(temp) == 0;)
    {
        temp1 = temp;
        temp = temp->childNode[0];
        for (; temp1->nextNode != nullptr;)
        {
            temp2 = temp1;
            temp1 = temp1->nextNode;
            delete temp2;
        }
        delete temp1;
    }
    for (; temp->nextNode != nullptr;)
    {
        temp1 = temp;
        temp = temp->nextNode;
        delete temp1;
    }
    delete temp;
    temp = nullptr;
}


//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
//－－－－－－－－－－－模板类的其他成员函数－－－－－－－－－－－－－－－－－
//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－

//－－－－－－－－－－－－处理比较大小－－－－－－－－－－－－－－－－－－－－
template <class T>
template <typename It>
int bpTree<T>::compare(const It & a, const It & b)
{
    if (a == b)         return 0;
    else if (a > b)     return 1;
    else                return -1;
}

//－－－－－－－－－－－－－－－根节点判断－－－－－－－－－－－－－－－－－－

template<class T>
bool bpTree<T>::Isroot(node* & nodeposition) const
{
    if (nodeposition->fatherNode == nullptr)
        return 1;
    else
        return 0;
}

//－－－－－－－－－－－－－－－－叶节点判断－－－－－－－－－－－－－－－－－

template<class T>
bool bpTree<T>::Isleaf(node* & cnode) const
{
    if (cnode->isLeaf == 0)
        return false;
    else
        return true;
}

//－－－－－－－－－－－－－－寻找叶节点－－－－－－－－－－－－－－－

template<class T>
void bpTree<T>::findLeaf(const T & the_key)
{
    int i;
    posNode = treeRoot;

    while (Isleaf(posNode) == 0)                     //还没到叶节点则继续向下找到叶节点就中止
    {
        for (i = 0; i < posNode->no; i++)              //在各层节点中寻找相应的位置
            if (compare(the_key, posNode->key[i]) == -1)//找到后跳出循环
                break;
        posNode = posNode->childNode[i];
    }
}


//－－－－－－－－－－－－－－寻找相等的值－－－－－－－－－－－－－－－－


template<class T>
auto bpTree<T>::Eqsearch(const T & key) -> vector<pos_type>
{
    vector<pos_type> pos;

    findLeaf(key);
    for (int i = 0; i < posNode->no; i++)              //找到在节点中的位置
    {
        if (compare(key, posNode->key[i]) == 0)
        {
            pos.push_back(posNode->dataPos[i]);
            break;
        }
    }
    return pos;
}


//－－－－－－－－－－－－－－寻找不相等－－－－－－－－－－－－－－－－－


template<class T>
auto bpTree<T>::Neqsearch(const T & key) -> vector<pos_type>
{
    vector<pos_type> pos;
    for(headNode = treeRoot; headNode != nullptr; headNode = headNode->childNode[0])
        posNode = headNode;
    for(; posNode != nullptr; posNode = posNode->nextNode)
    {
        for(int i = 0; i < posNode->no; i++)
        {
            if(posNode->key[i] != key)
                pos.push_back(posNode->dataPos[i]);
        }
    }
    return pos;
}


//－－－－－－－－－－－－寻找>=－－－－－－－－－－－－－－－－－－－－－－


template<class T>
auto bpTree<T>::Besearch(const T & key) -> vector<pos_type>
{
    int i;
    vector<pos_type> pos;
    findLeaf(key);
    for(i = 0; i < posNode->no; i++)				//找到在节点中的位置
    {
        if(compare(posNode->key[i], key) >= 0)
        {
            break;
        }
    }
    for(; i < posNode->no; i++)
    {
        pos.push_back(posNode->dataPos[i]);
    }
    for(posNode = posNode->nextNode; posNode != nullptr; posNode = posNode->nextNode)
    {
        for(int j = 0; j < posNode->no; j++)
            pos.push_back(posNode->dataPos[j]);
    }
    return pos;
}


//－－－－－－－－－－－－－寻找>－－－－－－－－－－－－－－－－－－－

template<class T>
auto bpTree<T>::Bsearch(const T & key) -> vector<pos_type>
{
    int i;
    vector<pos_type> pos;
    findLeaf(key);
    for(i = 0; i < posNode->no; i++)				//找到在节点中的位置
    {
        if(compare(posNode->key[i], key) > 0)
        {
            break;
        }
    }
    for(; i < posNode->no; i++)
    {
        pos.push_back(posNode->dataPos[i]);
    }
    for(posNode = posNode->nextNode; posNode != nullptr; posNode = posNode->nextNode)
    {
        for(int j = 0; j < posNode->no; j++)
            pos.push_back(posNode->dataPos[j]);
    }
    return pos;
}


//－－－－－－－－－－－－－－－－寻找<－－－－－－－－－－－－－－－－－

template<class T>
auto bpTree<T>::Ssearch(const T & key) -> vector<pos_type>
{
    vector<pos_type> pos;
    findLeaf(key);
    node *tmp = posNode;

    for(headNode = treeRoot; headNode != nullptr; headNode = headNode->childNode[0])
        posNode = headNode;

    while(posNode != tmp)
    {
        for(int i = 0; i < posNode->no; i++)
            pos.push_back(posNode->dataPos[i]);
        posNode = posNode->nextNode;
    }

    for(int i = 0; compare(posNode->key[i], key) < 0; i++)
        pos.push_back(posNode->dataPos[i]);
    return pos;
}


//－－－－－－－－－－－－－－－－寻找<=－－－－－－－－－－－－－－－－－

template<class T>
auto bpTree<T>::Sesearch(const T & key) -> vector<pos_type>
{
    vector<pos_type> pos;
    findLeaf(key);
    node *tmp = posNode;

    for(headNode = treeRoot; headNode != nullptr; headNode = headNode->childNode[0])
        posNode = headNode;

    while(posNode != tmp)
    {
        for(int i = 0; i < posNode->no; i++)
            pos.push_back(posNode->dataPos[i]);
        posNode = posNode->nextNode;
    }

    for(int i = 0; compare(posNode->key[i], key) <= 0; i++)
        pos.push_back(posNode->dataPos[i]);
    return pos;
}



//－－－－－－－－－－－－－－－数据插入函数－－－－－－－－－－－－－－－

template<class T>
bool bpTree<T>::Insert_node(const T & key, const pos_type & n)
{
    findLeaf(key);
    bool f = false;

    if (totalData == 0)                                       //当数据被删完时的情况
    {
        treeRoot->key[0] = key;
        treeRoot->dataPos[0] = n;
        treeRoot->no = 1;
        totalData = 1;
    }
    else                                                //还有数据
    {
        for (int i = 0; i < posNode->no; i++)          //插入数据比最大值小，找到在叶节点中的位置
        {
            if(compare(key, posNode->key[i]) == 0)
            {
                return false;
            }
            if (compare(key, posNode->key[i]) == -1)   //找到后，后面的数据后移
            {
                for (int j = posNode->no; j > i; j--)
                {
                    posNode->key[j] = posNode->key[j - 1];
                    posNode->dataPos[j] = posNode->dataPos[j - 1];
                }
                posNode->key[i] = key;
                posNode->dataPos[i] = n;
                f = true;
                break;
            }
        }
        if (f == false)                                     //数据比最大值大，直接插到最后
        {
            posNode->key[posNode->no] = key;
            posNode->dataPos[posNode->no] = n;
        }
        if (posNode->no < N - 1)                           //节点未满，节点的数据个数＋1后退出
            posNode->no += 1;
        else                                                //节点已满，进行节点分裂
            Resize_leaf();
        totalData++;
    }
    opFlag = true;
    return true;
}


//－－－－－－－－－－－－－－分裂叶节点－－－－－－－－－－－－－－－－
template<class T>
void bpTree<T>::Resize_leaf()
{
    node* new_node = new node;

    //分为两个叶节点
    for (int i = N / 2; i < N; i++)
    {
        new_node->key[i - N / 2] = posNode->key[i];
        new_node->dataPos[i - N / 2] = posNode->dataPos[i];
    }

    //处理横向连接及其他数值
    if (posNode->nextNode != nullptr)
    {
        if (posNode->nextNode->nextNode != nullptr)
        {
            new_node->brother = posNode->brother;
            posNode->brother = new_node;
        }
        else
        {
            new_node->brother = posNode->brother;
            posNode->brother = new_node;
            posNode->nextNode->brother = new_node;
        }
    }
    else
    {
        posNode->brother = new_node;
        new_node->brother = posNode;
    }
    new_node->nextNode = posNode->nextNode;
    posNode->nextNode = new_node;
    new_node->isLeaf = 1;
    posNode->no = N / 2;
    new_node->no = N - N / 2;
    new_node->fatherNode = posNode->fatherNode;

    for (int i = N / 2; i < N; i++)     //数据复位
    {
        //posNode->key[i] = 0;
        posNode->dataPos[i] = 0;
    }
    // 接下来处理其上一层的非叶节点的值和孩子指针

    // 自己是根结点的情况
    int i = 0;
    if (Isroot(posNode) == 1)
    {
        node* root = new node;
        root->key[0] = new_node->key[0];
        root->childNode[0] = posNode;
        root->childNode[1] = new_node;
        root->no = 1;
        posNode->fatherNode = new_node->fatherNode = root;
        treeRoot = root;
    }
    //非根结点的情况
    else
    {
        node* po = posNode->fatherNode;
        for (i = 0; i < po->no; i++)
        {// 找到父节点指向新叶节点的指针
            if (compare(new_node->key[0], po->key[i]) == -1)
                break;
        }
        // 后面的索引键值和孩子指针都后移，为新节点腾出位置
        for (int j = po->no; j > i; j--)
            po->key[j] = po->key[j - 1];

        for (int j = po->no + 1; j > i + 1; j--)
            po->childNode[j] = po->childNode[j - 1];
        // 让i + 1处指针指向新的节点
        po->key[i] = new_node->key[0];
        po->childNode[i] = posNode;
        po->childNode[i + 1] = new_node;

        //父节点数据未满，no数加一
        if (posNode->fatherNode->no < N - 1)
            posNode->fatherNode->no++;

        //父节点数据已满
        else
        {
            posNode = posNode->fatherNode;
            Resize_nleaf();//分裂非叶节点（涉及递归）
        }
    }
}

//－－－－－－－－－－－－－－分裂非叶节点－－－－－－－－－－－－－－－
template<class T>
void bpTree<T>::Resize_nleaf()
{
    node* new_node = new node;

    //把节点分开
    for (int i = (N + 1) / 2; i < N; i++)
    {
        new_node->key[i - (N + 1) / 2] = posNode->key[i];
        new_node->childNode[i - (N + 1) / 2] = posNode->childNode[i];
    }
    new_node->childNode[N / 2] = posNode->childNode[N];

    //处理横向连接问题及其他数值

    if (posNode->nextNode != nullptr)
    {
        if (posNode->nextNode->nextNode != nullptr)
        {
            new_node->brother = posNode->brother;
            posNode->brother = new_node;
        }
        else
        {
            new_node->brother = posNode->brother;
            posNode->brother = new_node;
            posNode->nextNode->brother = new_node;
        }
    }
    else
    {
        posNode->brother = new_node;
        new_node->brother = posNode;
    }
    new_node->nextNode = posNode->nextNode;
    posNode->nextNode = new_node;
    posNode->no = (N - 1) / 2;
    new_node->no = N / 2;
    new_node->fatherNode = posNode->fatherNode;


    for ( int i = 0; i < N - (N - 1) / 2; i++) //移动后复位
    {
        //posNode->key[N - 1 - i] = 0;
        posNode->childNode[N - i] = nullptr;
    }

    for (int x = 0; x < new_node->no + 1; x++)
    {//把新节点的子节点的父节点改过来
        new_node->childNode[x]->fatherNode = new_node;
    }

    //根据自己是不是根结点
    if (Isroot(posNode) == 1)          //是根结点情况
    {
        node* root = new node;
        node* pos = new_node;
        while (Isleaf(pos) != 1)
            pos = pos->childNode[0];
        root->key[0] = pos->key[0];
        root->childNode[0] = posNode;
        root->childNode[1] = new_node;
        root->no = 1;
        posNode->fatherNode = new_node->fatherNode = root;
        treeRoot = root;
    }

    else   //非根结点的情况
    {
        int i;
        node* po = posNode->fatherNode;
        for (i = 0; i < po->no; i++)
        {// 找到父节点指向新叶节点的指针
            if (compare(new_node->key[0], po->key[i]) == -1)
                break;
        }
        // 后面的索引键值和孩子指针都后移，为新节点腾出位置
        for (int j = po->no; j > i; j--)/////////////////////////////////////////
            po->key[j] = po->key[j - 1];

        for (int j = po->no + 1; j > i + 1; j--)
            po->childNode[j] = po->childNode[j - 1];
        // 让i + 1处指针指向新的节点
        node* pos = new_node;
        while (Isleaf(pos) != 1)
            pos = pos->childNode[0];
        po->key[i] = pos->key[0];
        po->childNode[i] = posNode;
        po->childNode[i + 1] = new_node;

        //父节点数据未满，no数加一
        if (posNode->fatherNode->no < N - 1)
            posNode->fatherNode->no++;

        //父节点数据已满
        else
        {
            posNode = posNode->fatherNode;
            Resize_nleaf();//分裂非叶节点（涉及递归）
        }
    }
}


//－－－－－－－－－－－－－－删除叶节点数据－－－－－－－－－－－－－－－


template<class T>
bool bpTree<T>::Del_data(const T & ckey)
{
    bool f = false;

    findLeaf(ckey);                                   //所在的叶节点
    for (int i = 0; i < posNode->no; i++)              //找到在节点中的位置
    {
        if (compare(ckey, posNode->key[i]) == 0)
        {
            f = true; break;
        }
    }
    if (f == true)    //数据存在
    {
        del(ckey);
        opFlag = true;
        return true;
    }
    else            return false;
}


//－－－－－－－－－－－－－－－－删除－－－－－－－－－－－－－－－－


template<class T>
void bpTree<T>::del(const T & k)
{
    int i;
    for (i = 0; i < posNode->no; i++)          //找到在节点中的位置
    {
        if (compare(k, posNode->key[i]) == 0)break;
    }

    if (Isroot(posNode) == 1)                    //根结点情况
    {
        for (; i < posNode->no - 1; i++)
        {
            posNode->key[i] = posNode->key[i + 1];
            posNode->dataPos[i] = posNode->dataPos[i + 1];
        }
        //posNode->key[i] = 0;
        posNode->dataPos[i] = 0;
        posNode->no--;
        totalData--;
    }
    else                                         //叶节点非根结点
    {
        for (; i<posNode->no - 1; i++)
        {
            posNode->key[i] = posNode->key[i + 1];
            posNode->dataPos[i] = posNode->dataPos[i + 1];
        }
        //posNode->key[i] = 0;
        posNode->dataPos[i] = 0;
        totalData--;
        posNode->no--;

        if (posNode->no < N / 2)                   //需要调整的
            MergeLeaf();
    }
}

//－－－－－－－－－－－－－－－合并leaf节点－－－－－－－－－－－－－－－－

template<class T>
void bpTree<T>::MergeLeaf()
{
    node* brother = posNode->brother;
    int i;
    if (brother->no < N - posNode->no)           //两节点可以合并
    {
        if (posNode->nextNode != nullptr)         //不是最右边的节点
        {
            for (i = posNode->no; i < posNode->no + brother->no; i++)
            {
                posNode->key[i] = brother->key[i - posNode->no];
                posNode->dataPos[i] = brother->dataPos[i - posNode->no];
            }
            //处理合并后节点的其他数值

            // no
            posNode->no += brother->no;

            // brother
            if (brother->nextNode != nullptr)
            {
                if (brother->nextNode->nextNode != nullptr)posNode->brother = brother->brother;
                else
                {
                    posNode->brother = brother->brother;
                    brother->brother->brother = posNode;
                }
            }
            else
            {
                if (posNode->fatherNode->no < 2)
                    posNode->brother = nullptr;
                else
                    posNode->brother = posNode->fatherNode->childNode[posNode->fatherNode->no - 2];
            }

            posNode->nextNode = brother->nextNode;

            //重置上级节点中的数值

            node* tp = brother->fatherNode;

            i = 0;
            while(i < tp->no && compare(tp->key[i], brother->key[0]) <= 0)
                i++;
            if(i == 0)
            {
                for(; i < tp->no - 1; i++)
                {
                    tp->key[i] = tp->key[i + 1];
                    tp->childNode[i] = tp->childNode[i + 1];
                }
                tp->childNode[i] = tp->childNode[i + 1];
            }
            else
            {
                i--;
                for(; i < tp->no - 1; i++)
                {
                    tp->key[i] = tp->key[i + 1];
                    tp->childNode[i + 1] = tp->childNode[i + 2];
                }
            }

            /*
            if(tp->key[i] == brother->key[0])
            {
                for (; i < tp->no - 1; i++)
                {
                    tp->key[i] = tp->key[i + 1];
                    tp->childNode[i + 1] = tp->childNode[i + 2];
                }
                //tp->key[i] = 0;
                tp->childNode[i + 1] = nullptr;
            }
            else    // fatherNodes are different
            {
                for (; i < tp->no; i++)
                {
                    tp->key[i] = tp->key[i + 1];
                    tp->childNode[i] = tp->childNode[i + 1];
                }
                //tp->key[i - 1] = 0;
                tp->childNode[i] = nullptr;

            }
            */
            delete brother;
            brother = nullptr;

            posNode = tp;
            posNode->no--;
            if (posNode->no < (N + 1) / 2 - 1)   //需要调整的
            {
                Merge();
            }
            resetKey(posNode);
        }
        else                                     //最右边的节点
        {
            //合并
            for (i = brother->no; i < brother->no + posNode->no; i++)
            {
                brother->key[i] = posNode->key[i - brother->no];
                brother->dataPos[i] = posNode->dataPos[i - brother->no];
            }

            //合并后其他数据处理
            brother->no += posNode->no;
            brother->nextNode = nullptr;
            brother->brother = brother->fatherNode->childNode[brother->fatherNode->no - 2];

            //替换上级节点中的数据
            node* tp = posNode->fatherNode;
            //tp->key[tp->no - 1] = 0;
            tp->childNode[tp->no] = nullptr;

            delete posNode;
            posNode = tp;

            posNode->no--;
            if (posNode->no < (N + 1) / 2 - 1)   //需要调整的
            {
                Merge();
            }
            resetKey(posNode);
        }
    }
    else                                          //两节点不可以合并
    {
        if (posNode->nextNode != nullptr)            //不是最右边的节点
        {
            //调整两个节点的数据个数

            int w = posNode->no;
            posNode->key[w] = brother->key[0];
            posNode->dataPos[w] = brother->dataPos[0];

            posNode->no++;
            brother->no--;

            //数据前移

            for (i = 0; i < brother->no; i++)
            {
                brother->key[i] = brother->key[i + 1];
                brother->dataPos[i] = brother->dataPos[i + 1];
            }

            //数据转移后空位零
            brother->dataPos[i] = 0;
            resetKey(brother);
            //brother->key[i] = 0;
        }
        else             //最右边的节点
        {
            //调整数据个数
            for (i = posNode->no; i>0; i--)         //数据后移
            {
                posNode->key[i] = posNode->key[i - 1];
                posNode->dataPos[i] = posNode->dataPos[i - 1];
            }
            posNode->dataPos[0] = brother->dataPos[brother->no - 1];
            posNode->key[0] = brother->key[brother->no - 1];

            brother->no--;
            posNode->no++;

            //数据转移后空位付零
            brother->dataPos[brother->no] = 0;
            resetKey(posNode);
            //brother->key[brother->no] = 0;
        }
    }
}

//－－－－－－－－－－－－－－－合并non-leaf节点－－－－－－－－－－－－－－－－

template<class T>
void bpTree<T>::Merge()
{
    node* brother = posNode->brother;
    int i;

    if(Isroot(posNode))
    {
        if(posNode->no == 0)
        {
            node *tp = posNode;
            posNode = posNode->childNode[0];
            delete tp;
            posNode->fatherNode = nullptr;
            treeRoot = posNode;
        }
    }
    else if (brother->no < N - 1 - posNode->no)   //两节点可以合并
    {
        if (posNode->nextNode != nullptr)         //不是最右边的节点
        {
            for (i = posNode->no; i < posNode->no + brother->no; i++)
            {

                posNode->key[i + 1] = brother->key[i - posNode->no];
                posNode->childNode[i + 1] = brother->childNode[i - posNode->no];
                brother->childNode[i - posNode->no]->fatherNode = posNode;
            }
            posNode->childNode[i + 1] = brother->childNode[i - posNode->no];
            brother->childNode[i - posNode->no]->fatherNode = posNode;

            node *temp = posNode->childNode[posNode->no + 1];
            while(Isleaf(temp) != 1)
                temp = temp->childNode[0];
            posNode->key[posNode->no] = temp->key[0];
            //处理合并后节点的其他数值
            // no
            posNode->no += brother->no + 1;

            // brother
            if (brother->nextNode != nullptr)
            {
                if (brother->nextNode->nextNode != nullptr)posNode->brother = brother->brother;
                else
                {
                    posNode->brother = brother->brother;
                    brother->brother->brother = posNode;
                }
            }
            else
            {
                if (posNode->fatherNode->no < 2)
                    posNode->brother = nullptr;
                else
                    posNode->brother = posNode->fatherNode->childNode[posNode->fatherNode->no - 2];
            }

            posNode->nextNode = brother->nextNode;

            //重置上级节点中的数值

            node* tp = brother->fatherNode;

            i = 0;
            while(i < tp->no && compare(tp->key[i], brother->key[0]) < 0)
                i++;
            if(i == 0)
            {
                for(; i < tp->no - 1; i++)
                {
                    tp->key[i] = tp->key[i + 1];
                    tp->childNode[i] = tp->childNode[i + 1];
                }
                tp->childNode[i] = tp->childNode[i + 1];
            }
            else
            {
                i--;
                for(; i < tp->no - 1; i++)
                {
                    tp->key[i] = tp->key[i + 1];
                    tp->childNode[i + 1] = tp->childNode[i + 2];
                }
            }
            resetKey(brother);

            delete brother;
            brother = nullptr;

            posNode = tp;
            posNode->no--;
            if (posNode->no < (N + 1) / 2 - 1)   //需要调整的
            {
                Merge();
            }
        }
        else                 //最右边的节点
        {
            //合并
            for (i = brother->no; i < brother->no + posNode->no; i++)
            {
                brother->key[i + 1] = posNode->key[i - brother->no];
                brother->childNode[i + 1] = posNode->childNode[i - brother->no];
                posNode->childNode[i - brother->no]->fatherNode = brother;
            }
            brother->childNode[i + 1] = posNode->childNode[i - brother->no];
            posNode->childNode[i - brother->no]->fatherNode = brother;

            node *temp = brother->childNode[brother->no + 1];
            while(Isleaf(temp) != 1)
                temp = temp->childNode[0];
            brother->key[brother->no] = temp->key[0];

            //合并后其他数据处理
            brother->no += posNode->no + 1;
            brother->nextNode = nullptr;
            brother->brother = brother->fatherNode->childNode[brother->fatherNode->no - 2];

            //替换上级节点中的数据
            node* tp = posNode->fatherNode;
            //tp->key[tp->no - 1] = 0;
            tp->childNode[tp->no] = nullptr;

            delete posNode;
            posNode = tp;

            posNode->no--;
            if (posNode->no < (N + 1) / 2 - 1)   //需要调整的
            {
                Merge();
            }
            resetKey(posNode);
        }
    }
    else                                          //两节点不可以合并
    {
        if (posNode->nextNode != nullptr)            //不是最右边的节点
        {
            //调整两个节点的数据个数
            int w = posNode->no;

            posNode->childNode[w + 1] = brother->childNode[0];
            posNode->childNode[w + 1]->fatherNode = posNode;

            node *temp = posNode->childNode[w + 1];
            while(Isleaf(temp) != 1)
                temp = temp->childNode[0];
            posNode->key[posNode->no] = temp->key[0];

            posNode->no++;
            brother->no--;

            //数据前移
            for (i = 0; i < brother->no; i++)
            {
                brother->key[i] = brother->key[i + 1];
                brother->childNode[i] = brother->childNode[i + 1];
            }
            //数据转移后空位付零
            brother->childNode[i] = brother->childNode[i + 1];
            brother->childNode[i + 1] = nullptr;
            resetKey(brother);
            //brother->key[i - 1] = 0;
        }
        else           //最右边的节点
        {
            //调整数据个数
            for (i = posNode->no; i > 0; i--)              //数据后移
            {
                posNode->key[i] = posNode->key[i - 1];
                posNode->childNode[i + 1] = posNode->childNode[i];
            }
            posNode->childNode[1] = posNode->childNode[0];
            posNode->childNode[0] = brother->childNode[brother->no];
            posNode->childNode[0]->fatherNode = posNode;


            node *temp = posNode->childNode[1];
            while(Isleaf(temp) != 1)
                temp = temp->childNode[0];
            posNode->key[0] = temp->key[0];
            //posNode->key[0] = brother->key[brother->no];

            brother->no--;
            posNode->no++;

            //数据转移后空位付零
            brother->childNode[brother->no + 1] = nullptr;
            resetKey(posNode);
            //brother->key[brother->no] = 0;
        }
    }
}

template<class T>
void bpTree<T>::resetKey(const node *n)
{
    node *curPos = n->fatherNode;
    while(curPos)
    {
        for(int i = 0; i < curPos->no; i++)
        {
            node *temp = curPos->childNode[i + 1];
            while(Isleaf(temp) != 1)
                temp = temp->childNode[0];
            curPos->key[i] = temp->key[0];
        }
        curPos = curPos->fatherNode;
    }
}

template<class T>
void bpTree<T>::Index(const string & indexName)               //建立索引文件
{
    File &file = BufferManager::open(indexName);

    pos_type total = 0;
    for (headNode = treeRoot; headNode->isLeaf == 0; headNode = headNode->childNode[0])
        ;
    node* next = headNode;
    file.seekp(sizeof(pos_type));
    for (; next != nullptr;)
    {
        file << next->no;
        for (int i = 0; i < next->no; i++)
        {
            file << next->key[i];
            file << next->dataPos[i];
        }
        //file.flush();
        next = next->nextNode;
        total++;
    }
    file.seekp(0);
    file << total;
    file.flush();
}

template<class T>
void bpTree<T>::DropIndex(const bpTree::string &name)
{
    File &file = BufferManager::open(name);
    file.remove();
}

//#include <iostream>
template<class T>
template<typename Q>
void bpTree<T>::Buildtree(const string &indexName, typename std::enable_if<!std::is_same<Q, FixString>::value, pri>::type)
{
    File &file = BufferManager::open(indexName);

    pos_type total;
    pos_type pos;
    T key;
    int i, num;
    file.seekg(0);
    file >> total;

    for (i = 0; i < total; i++)
    {
        file >> num;
        for (int j = 0; j < num; j++)
        {
            file >> key; file >> pos;
            Insert_node(key, pos);
        }

    }
}

template<class T>
template<typename Q>
void bpTree<T>::Buildtree(const string &indexName, typename std::enable_if<std::is_same<Q, FixString>::value, size_t>::type size)
{
    File &file = BufferManager::open(indexName);

    pos_type total;
    pos_type pos;
    T key;
    int i, num;
    file.seekg(0);
    file >> total;
    key.resize(size);
    for (i = 0; i < total; i++)
    {
        file >> num;
        for (int j = 0; j < num; j++)
        {
            file >> key;
            file >> pos;
            Insert_node(key, pos);
        }

    }
}

//template<class T>
//void bpTree<T>::Buildtree(const string & indexName, size_t x)           //从索引文件中导出建立b+树
//{
//    File &file = BufferManager::open(indexName);

//    pos_type total;
//    pos_type pos;
//    T key;
//    int i, num;
//    file.seekg(0);
//    file >> total;

//    for (i = 0; i < total; i++)
//    {
//        file >> num;
//        for (int j = 0; j < num; j++)
//        {
//            file >> key; file >> pos;
//            Insert_node(key, pos);
//        }

//    }
//}


#ifdef TEST
template<class T>
void bpTree<T>::Show()
{
    for (headNode = treeRoot; headNode->isLeaf == 0; headNode = headNode->childNode[0])
        ;
    node* p=headNode;
    if(p!=nullptr)
    {

        for(;Isleaf(p)==0;)
            p=p->childNode[0];
        int j=0;
        headNode = p->fatherNode;
        for(;;)
        {
            j=0;
            if(p != nullptr)
            {
                while(p->nextNode!=nullptr)
                {
                    for(int i = 0; i < p->no;i++)
                    {
                        std::cout<<p->key[i];
                        std::cout<<"    ";
                        j++;
                    }
                    p=p->nextNode;
                    std::cout<<"\n"<<"\n";
                }
                for(int i = 0; i < p->no; i++)
                {
                    std::cout<<p->key[i];
                    std::cout<<"    ";
                    j++;
                }
                std::cout<<"\n"<<"\n";
                std::cout<<j<<"\n";
                p=headNode;
                std::cout<<"-------------------------------------"<<"\n";
            }
            if(p != nullptr)
            {
                if(p->fatherNode!=nullptr)
                    headNode=p->fatherNode;
                else
                    break;
            }
            if(p==nullptr)break;
        }


        for(int i = 0;i < p->no; i++)
        {
            std::cout<<p->key[i];
            std::cout<<"    ";
            j++;
        }
        std::cout<<"\n"<<"\n";

    }
    else
        std::cout<<"no data is exist";
}
#endif

#endif //BPTREE_H_
