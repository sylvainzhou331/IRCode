#ifndef INDEXLIST_H
#define INDEXLIST_H
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;
class IndexList
{
    public:
        IndexList();
        virtual ~IndexList();
        // add增加一个docID
        void push(int docID);
        long long gamma(int x);
        vector<int> decode();
        //获取gamma编码的倒排索引使用了多少个int
        int getOffset();
        int writeOffset(ofstream &out);
        void writeToFile(ofstream &out);
        void readFromFile(ifstream &in, int len);
    protected:
    private:
        //vector自动管理内存，动态申请。
        vector<int> buf;
        //bit存储最后一个int使用到了第几位
        int bit;
        //last记录最后一个docID是多少,初始为0，因为add时要做差
        int last;

};

#endif // INDEXLIST_H
