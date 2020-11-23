#ifndef UTIL_H
#define UTIL_H

#include <cstring>
#include <string>
#include <vector>
#include <dirent.h>
#include <cstdio>
#include <cstdlib>
using namespace std;
class Util
{
    public:
        Util();
        virtual ~Util();
        vector<string> getFiles(string path);
        void delFile(string file);
    protected:
    private:
};

#endif // UTIL_H
