#ifndef DICT_H
#define DICT_H
#include <map>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include "IndexList.h"
using namespace std;
class Dict
{
    public:
        Dict();
        virtual ~Dict();
        //查找是否包含s词
        int find(string s);
        //插入一个新词
        void insert(string s, int docID);
        void push(int id, int docID);
        //将词典和索引写入文件。
        void writeToFile(char *indexName);
        //重置
        void reset();
        void output(string s);
    protected:
    private:
        //词项数目
        int itemNum;
        //单词映射
        map<string, int> mp;
        //存每一个单词的索引列表
        vector<IndexList> list;
        //每个词的文档频率
        vector<int> df;
};

#endif // DICT_H
