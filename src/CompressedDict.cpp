#include "../include/CompressedDict.h"

CompressedDict::CompressedDict()
{
    buf = NULL;
    //ctor
}

CompressedDict::~CompressedDict()
{
    if (buf) delete[] buf;
    //dtor
}
void CompressedDict::reset() {
    if (buf) delete[] buf;
    buf = NULL;
    dict.clear();
    len = 0;
}
void CompressedDict::generateDict(map<string, pair<int, int> > mp, int l) {
    map<string, pair<int, int> >::iterator it = mp.begin();
    int len = 0;
    vector<string> v;
    dict.clear();
    for (; it != mp.end(); it++) {
        v.push_back(it->first);
        dict.push_back(dictNode(it->second.first, len, it->second.second));
        len += it->first.size();
    }
    //加一个结束标兵
    dict.push_back(dictNode(0, len, l));
    if (buf) delete[] buf;
    buf = new char[len];
    int size = v.size(), st = 0;
    printf("len%d\n", len);
    for (int i = 0; i < size; i++) {
        strcpy(buf + st, v[i].c_str());
        st += v[i].size();
    }
    this->len = len;
}
void CompressedDict::writeToFile(string file) {
    ofstream out(file.c_str(), ios::binary|ios::out);
    out.write((char *)&len, sizeof(int));
    out.write(buf, sizeof(char) * len);
    int size = dict.size();
    for (int i = 0; i < size; i++) {
        out.write((char *)&dict[i].df, sizeof(int));
        out.write((char *)&dict[i].st, sizeof(int));
        out.write((char *)&dict[i].offset, sizeof(int));
    }
    out.close();
}
void CompressedDict::readFromFile(string file) {
    ifstream in(file.c_str(), ios::binary|ios::in);
    int len;
    in.read((char *)&len, sizeof(int));
    if (buf) delete[] buf;
    buf = new char[len];
    in.read(buf, sizeof(char) * len);
    this->len = len;
    dict.clear();
    int a, b, c;
    while(!in.eof()) {
        in.read((char *)&a, sizeof(int));
        in.read((char *)&b, sizeof(int));
        in.read((char *)&c, sizeof(int));
        if (a == -1) break;
        dict.push_back(dictNode(a, b, c));
    }
    in.close();
}
int CompressedDict::cmp(int x, const char *s) {
    int st = dict[x].st, ed = dict[x + 1].st;
    int l = strlen(s);
    for (int i = st; i < ed && i - st < l; i++) {
        if (buf[i] < s[i - st]) return -1;
        else if (buf[i] > s[i - st]) return 1;
    }
    if (ed - st > l) return 1;
    if (ed - st < l) return -1;
    return 0;
}
void CompressedDict::find(string word, int &id, int &df, int &offset, int &l) {
    int lef = 0, rig = dict.size(), mid;
    while(lef <= rig) {
        mid = (lef + rig) >> 1;
        int x = cmp(mid, word.c_str());
        if (x == 0) {
            id = mid;
            df = dict[mid].df;
            offset = dict[mid].offset;
            l = (dict[mid + 1].offset - offset - 1 - 4 ) / sizeof(int);
            return;
        } else if (x < 0) {
            lef = mid + 1;
        } else {
            rig = mid - 1;
        }
    }
    id = -1;
    df = 0;
}
int CompressedDict::getItemNum() {
    return dict.size() - 1;
}
