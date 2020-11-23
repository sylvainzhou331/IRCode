#ifndef COMPRESSEDDICT_H
#define COMPRESSEDDICT_H
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <fstream>
using namespace std;
struct dictNode {
    int df;
    int st;
    int offset;
    dictNode(int a, int b, int c) {
        df = a;
        st = b;
        offset = c;
    }
    dictNode() {}
};
class CompressedDict
{
    public:
        CompressedDict();
        virtual ~CompressedDict();
        void generateDict(map<string, pair<int, int> > mp, int l);
        void writeToFile(string file);
        void readFromFile(string file);
        void find(string word, int &id, int &df, int &offset, int &l);
        void reset();
        int getItemNum();
    protected:
    private:
        vector<dictNode> dict;
        char *buf;
        int len;
        int cmp(int x, const char *s);
};

#endif // COMPRESSEDDICT_H
