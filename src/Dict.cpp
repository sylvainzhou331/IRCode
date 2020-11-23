#include "../include/Dict.h"

Dict::Dict()
{
    //ctor
}

Dict::~Dict()
{
    //dtor
}
void Dict::reset() {
    itemNum = 0;
    list.clear();
    mp.clear();
    df.clear();
}
void Dict::output(string s) {
    int id = find(s);
    vector<int> v = list[id].decode();
    int l = v.size();
    //cout<<l<<endl;
    for (int i = 0; i < l; i++) {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}
void Dict::push(int id, int docID) {
    //cout<<id<<" "<<docID<<endl;
    if (id == (int)list.size()) {
        IndexList il;
        list.push_back(il);
        df.push_back(0);
    }
    list[id].push(docID);
    df[id] = df[id] + 1;
}
int Dict::find(string s) {
    map<string, int>::iterator it = mp.find(s);
    if (it != mp.end()) return it->second;
    else return -1;
}
void Dict::insert(string s, int docID) {
    int id;
    if ((id = find(s)) != -1) {
        push(id, docID);
    } else {
        mp[s] = itemNum++;
        push(itemNum - 1, docID);
    }
}
void Dict::writeToFile(char *indexName) {

    ofstream out(indexName, ios::binary|ios::out);
    map<string, int>::iterator it = mp.begin();

    for (;it != mp.end(); it++) {
        const char* str = it->first.c_str();
        char l = strlen(str);
        //写单词
        out.write(&l, sizeof(char));
        out.write(str, l);
        //写文档频率
        out.write((char *)&df[it->second], sizeof(int));
        list[it->second].writeOffset(out);
        list[it->second].writeToFile(out);
    }

    out.close();
}
