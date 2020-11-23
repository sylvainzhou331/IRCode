#include "../include/Util.h"

Util::Util()
{
    //ctor
}

Util::~Util()
{
    //dtor
}
vector<string> Util::getFiles(string path) {
    DIR *dp;
    struct dirent *dirp;
    vector<string> file_names;
    if((dp=opendir(path.c_str()))==NULL){
        perror("opendir error");
        exit(1);
    }
    while((dirp=readdir(dp))!=NULL){
        if((strcmp(dirp->d_name,".")==0)||(strcmp(dirp->d_name,"..")==0))
            continue;
        file_names.push_back(dirp->d_name);
    }
    return file_names;
}
void Util::delFile(string file) {
    file = "rm -f " + file;
    system(file.c_str());
}
