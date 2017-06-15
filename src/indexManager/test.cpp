#include "File.h"
#include "BufferManager.h"
#include "../BpTree.h"
#include <QCoreApplication>
#include <random>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc,argv);
    bpTree<int> A;

    for(int i = 0 ; i != 50; i++)
        A.Insert_node(i, i + 1000);


    for(int i = 0 ; i != 10; i++)
       A.Del_data(i);
    std::cout << A.Eqsearch(20) << std::endl <<std::endl;
    /*
    A.Insert_node(9, 127);
    A.Insert_node(5, 127);
    A.Insert_node(7, 127);
    A.Del_data(7);
    A.Insert_node(1, 127);
    A.Insert_node(11, 127);
    A.Insert_node(3, 127);
    A.Insert_node(15, 127);
    A.Insert_node(2, 127);
    A.Insert_node(16, 127);
    A.Insert_node(19, 127);
    A.Insert_node(22, 127);
    A.Insert_node(29, 127);
    //A.Del_data(11);
    */
    A.Show();
    //int aa = A.Del_data(10);
    //int bb = A.Del_data(30);
    //A.Index("test");
    //bpTree<int> B;
    //B.Buildtree("test");
    //B.Insert_node(60, 127);
     //B.Insert_node(61, 127);
    //B.Index("testB");
    //File &file = BufferManager::open("test");
    //pos_type tmp;
    //file.seekg(0);
    //file >> tmp;



    return 0;
}
