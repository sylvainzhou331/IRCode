#ifndef INDEXER_H
#define INDEXER_H

#include <cstring>
#include <string>
#include <map>
#include <queue>
#include "CompressedDict.h"
#include "IndexList.h"
using namespace std;
class Indexer
{
    public:
        Indexer();
        virtual ~Indexer();
        void readFromFile(string dictFile, string indexFile);
        vector<int> find(string word, int &df);
        int getItemNum();
    protected:
    private:
        CompressedDict cd;
        //索引列表是否读入了内存，如果在内存，取出
        map<int, IndexList> inMem;
        int maxNum;
        //假定索引很大，无法全部读入内存，
        //当内存中索引数量过多时，取出que队首的索引释放掉
        queue<int> que;
        string indexFile;
};

#endif // INDEXER_H
