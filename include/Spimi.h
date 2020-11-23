#ifndef SPIMI_H
#define SPIMI_H

#include <cstring>
#include <string>
#include <set>
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
#include <cstdlib>
#include "Dict.h"
#include "Util.h"
#include "Merger.h"
#include "CompressedDict.h"
using namespace std;
/**
 * 适用范围：文档数不超过4字节，单词长度不超过1字节
**/
class Spimi
{
    public:
        Spimi();
        virtual ~Spimi();
        string merge();
        int getDocNum();
        int getTokenNum();
        int getItemNum();
        double getAveLen();
        void generateDictIndex(string file, string dictFile, string indexFile);
        void start(string path, int splitNum, string dictFile, string indexFile);
    protected:
    private:
        ifstream in;
        Dict dict;
        CompressedDict cd;
        Util util;
        Merger merger;
        int docID;
        int splitNum;
        void processFile();
        void processDoc();
        void updateDict(set<string>& s);
        string trim(string& str);
        int ave_len;
        int itemNum, tokenNum;
};

#endif // SPIMI_H
