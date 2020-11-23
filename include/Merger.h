#ifndef MERGER_H
#define MERGER_H
#include <cstring>
#include <string>
#include <fstream>
#include "Util.h"
#include "IndexList.h"
#include <vector>
using namespace std;
class Merger
{
    public:
        Merger();
        virtual ~Merger();
        //合并所有索引文件
        string merge(string path);
        int getItemNum();
    protected:
    private:
        int itemNum;
        //写剩余部分的文件
        void writeRest(ofstream &out, ifstream &in, char *s);
        //读一个单词
        void readWord(ifstream &in, char *s);
        //将一个索引写入文件
        void writeToFile(ofstream &out, char *word, int df, IndexList &il);
        //合并两个文件
        void mergeTwo(const char *file1, const char* file2, char  *outfile);
};

#endif // MERGER_H
