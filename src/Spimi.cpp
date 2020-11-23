#include "../include/Spimi.h"

Spimi::Spimi()
{
    //ctor
}

Spimi::~Spimi()
{
    //dtor
}
int Spimi::getItemNum() {
    return itemNum;
}
int Spimi::getDocNum() {
    return docID;
}
int Spimi::getTokenNum() {
    return tokenNum;
}
double Spimi::getAveLen() {
    return tokenNum * 1.0 / docID;
}
void Spimi::updateDict(set<string> &s) {
    //cout<<"updateDict"<<endl;
    set<string>::iterator it = s.begin();
    for (; it != s.end(); it++) {
        dict.insert(*it, docID);
    }
}
string Spimi::trim(string& str) {
    int st;
    if ((st = str.find("<title>")) != -1)  {
        str = str.substr(st + 7);
    }
    if ((st = str.find("<speaker>")) != -1)  {
        str = str.substr(st + 9);
    }
    if ((st = str.find("</title>")) != -1)  {
        str = str.substr(0, st);
    }
    if ((st = str.find("</speaker>")) != -1)  {
        str = str.substr(0, st);
    }
    int i = 0, j = str.size() - 1, t;
    while(!isalpha(str[i]) && i <= j) {
        i++;
    }
    while(!isalpha(str[j]) && i <= j) {
        j--;
    }
    t = j;
    while(str[t] != '\'' && t >= 0) {
        t--;
    }
    if (t >= 0) j = t - 1;
    str = str.substr(i, j - i + 1);
    j = str.size();
    for (i = 0; i < j; i++)
        str[i] = tolower(str[i]);
    return str;
}
void Spimi::processDoc() {
    set<string> s;
    string str;
    while(in>>str) {
        if (str.find("</DOC>") != -1) {
            updateDict(s);
            return;
        }
        if (str.find("<!--") != -1) {
            while(in>>str) {
                if (str.find("</DOC>") != -1) {
                    break;
                }
            }
            updateDict(s);
            return;
        }
        str = trim(str);
        if (str == "") continue;
        tokenNum++;
        s.insert(str);
    }
}
void Spimi::processFile() {
    string str;
    while(in>>str) {
        if (str.find("<DOC>") != -1) {
            docID++;
            in>>str;
            cout<<str<<endl;
            processDoc();
        } else {
            cout<<"发生错误:"<<docID<<endl;
        }
        //printf("%d\n", docID);
        if (docID % splitNum == 0) {
            char name[100];
            sprintf(name, "./tmp/b%d", docID / splitNum);
            dict.writeToFile(name);
            dict.reset();
        }
    }
}
void Spimi::start(string path, int splitNum, string dictFile, string indexFile) {
    dict.reset();
    this->splitNum = splitNum;
    vector<string> v = util.getFiles(path);
    int size = v.size();
    docID = 0;
    tokenNum = 0;
    for (int i = size - 1; i >= 0; i--) {
        in.open((path + "/" + v[i]).c_str(),ios::in);
        cout<<"处理文件: "<<path + "/" + v[i]<<endl;
        processFile();
        cout<<"文件处理完成"<<endl;
        in.close();
    }
    if (docID % splitNum) {
        char name[100];
        sprintf(name, "./tmp/b%d", docID / splitNum + 1);
        dict.writeToFile(name);
    }
    string name = merge();
    cout<<name<<endl;
    generateDictIndex(name, dictFile, indexFile);
    util.delFile(name);
}
string Spimi::merge() {
    return merger.merge("./tmp");
}
void Spimi::generateDictIndex(string file, string dictFile, string indexFile) {
    in.open(file.c_str(), ios::binary|ios::in);
    ofstream out2(indexFile.c_str(), ios::binary|ios::out);
    map<string, pair<int, int> > mp;
    char s[100], c;
    int offset = 0, len, t, df;
    while(!in.eof()) {
        c = -1;
        in.read(&c, sizeof(char));
        if (c == -1) break;
        in.read(s, c);
        s[c] = 0;
        in.read((char *)&df, sizeof(df));
        in.read((char *)&len, sizeof(int));
        //记录文档频率和词条在文件起始的字节位置
        mp[s] = make_pair<int, int>(df, offset);
        t = (len * 4) + 1 + 4;
        offset += t;
        char *buf = new char[t];
        in.read(buf, sizeof(char) * t);
        out2.write(buf, sizeof(char) * t);
        delete[] buf;
    }
    cd.generateDict(mp, offset);
    cd.writeToFile(dictFile);
    in.close();
    out2.close();
}


