#include "../include/Indexer.h"

Indexer::Indexer()
{
    //ctor
    maxNum = 1000;
}

Indexer::~Indexer()
{
    //dtor
}
void Indexer::readFromFile(string dictFile, string indexFile) {
    cd.reset();
    cd.readFromFile(dictFile);
    this->indexFile = indexFile;
    inMem.clear();
    while(!que.empty()) que.pop();
}
vector<int> Indexer::find(string word, int &df) {
    int id, offset, len;
    cd.find(word, id, df, offset, len);
    vector<int> v;
    if (id == -1) return v;
    map<int, IndexList>::iterator it = inMem.find(id);
    if (it == inMem.end()) {
        ifstream in(indexFile.c_str(), ios::binary|ios::in);
        in.seekg(offset, ios::beg);
        if ((int)que.size() >= maxNum) {
            int x = que.front();
            que.pop();
            inMem.erase(x);
        }
        que.push(id);
        IndexList il;
        il.readFromFile(in, len);
        v = il.decode();
        inMem[id] = il;

        in.close();
    } else {
        v = it->second.decode();
    }
    return v;
}
int Indexer::getItemNum() {
    return cd.getItemNum();
}
