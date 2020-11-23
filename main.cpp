#include <iostream>
#include "include/Spimi.h"
#include <fstream>
#include <vector>
#include "include/Indexer.h"
using namespace std;

int main()
{
    Spimi spimi;
    string path = "shakespeare-merchant.trec";
    spimi.start(path, 10, "dict", "index");

    cout<<"文档数量:"<<spimi.getDocNum()<<endl;
    cout<<"词条数量:"<<spimi.getTokenNum()<<endl;
    cout<<"文档平均长度:"<<spimi.getAveLen()<<endl;

    Indexer indexer;
    indexer.readFromFile("dict", "index");
    cout<<"词项数目:"<<indexer.getItemNum()<<endl;
    int df;
    cout<<"小写字母单词: 输出倒排索引\n例如输入balabala"<<endl;
    while(true) {
        string s;
        cin>>s;
        vector<int> v = indexer.find(s, df);
        cout<<"df:"<<df<<" docID:";
        for (int i = 0; i < v.size(); i++) {
            cout<<" "<<v[i];
        }
        cout<<endl;
    }
    return 0;
}
/*
    ifstream in("tmp/m1", ios::binary|ios::in);
    char c;
    char s[100];
    while(!in.eof()) {
        c = -1;
        in.read(&c, sizeof(char));
        if (c == -1)break;
       // if (c == 0) break;
        in.read(s, c);

        s[c] = 0;
       // if (s[0] == 0) break;
        cout<<"<"<<s<<">"<<endl;
        int len = -1, df;
        in.read((char*)&df, sizeof(int));
        cout<<"df:"<<df<<endl;
        in.read((char*)&len, sizeof(int));
        if (len >= 10) cout<<"error"<<endl;
        IndexList il;
        il.readFromFile(in, len);
        vector<int> v = il.decode();
        for (int i = 0; i < v.size(); i++) {
            cout<<v[i]<<" ";
        }
        cout<<endl;
        //getchar();
    }
    cout<<"end"<<endl;
    */
