#include "../include/IndexList.h"

IndexList::IndexList()
{
    //ctor
    bit = 31;
    last = 0;
}

IndexList::~IndexList()
{
    //dtor
}
long long IndexList::gamma(int x) {
    long long ret = 0;
    int l = 31;
    for (;l >= 0; l--) {
        if (x & (1 << l)) break;
    }
    x = (x ^ (1 << l));
    ret = ((1LL << l) - 1) << (l + 1);
    ret |= x;
    return ret;
}
vector<int> IndexList::decode() {
    vector<int> v;
    int b = -1, i = 0, x, pre = 0;
    int l = buf.size();
    //cout<<"bufsize"<<l<<endl;
    //cout<<buf[0]<<endl;
    //cout<<bit<<endl;
    while(true) {
        if (b == -1) {
            if (i == l) break;
            x = buf[i++];
            b = 31;
        }
        int len = 0;
        while((x & (1<<b))) {
            len++, b--;
            if (b == -1) {
                if (i == l) break;
                x = buf[i++];
                b = 31;
            }
        }
        if (i == l && b <= bit) break;
        //cout<<"b ="<<b<<endl;
        int docID = 1, j = 0;
        for(b--;j < len; j++, b--) {
            docID <<= 1;
            if (b == -1) {
                if (i == l)break;
                x = buf[i++];
                b = 31;
            }
            docID |= (x & (1<<b)) ? 1 : 0;
        }
        v.push_back(docID + pre);
        pre = docID + pre;
        //cout<<"b="<<b<<endl;
        if (i == l && b <= bit) break;
    }
    return v;
}
void IndexList::push(int docID) {
    //cout<<last<<endl;
    int c = docID - last;
    long long g = gamma(c);
    //cout<<g<<"<--"<<c<<endl;
    int i;
    for (i = 63; i >= 0; i--) {
        if (g & (1LL<<i)) break;
    }
    if (i < 0) i = 0;
    int x;
    if (buf.size() == 0) {
        x = 0;
    }else {
        x = buf[buf.size() - 1];
    }
    do {
        for (; bit >= 0 && i >= 0; bit--, i--) {
            x |= ((g & (1LL<<i)) ? 1 : 0) << bit;
        }
        if (buf.size() == 0) buf.push_back(x);
        else buf[buf.size() - 1] = x;
        if (bit >= 0) break;
        x = 0;
        bit = 31;
        buf.push_back(0);
    } while(true);
    last = docID;
}
int IndexList::getOffset() {
    int offset = buf.size();
    return offset;
}
int IndexList::writeOffset(ofstream &out) {
    int offset = buf.size();
    out.write((char*)&offset, sizeof(int));
    return offset;
}
void IndexList::writeToFile(ofstream &out) {
    int len = buf.size();
    for (int i = 0; i < len; i++) {
        int x = buf[i];
        out.write((char *)(&x), sizeof(int));
    }
    char c = bit;
    out.write(&c, sizeof(char));
    out.write((char *)&last, sizeof(int));
}
void IndexList::readFromFile(ifstream &in, int len) {
    buf.clear();
    for (int i = 0; i < len; i++) {
        int x;
        in.read((char *)&x, sizeof(int));
        buf.push_back(x);
    }
    char c;
    in.read(&c, sizeof(char));
    bit = c;
    int a;
    in.read((char *)&a, sizeof(int));
    last = a;
}
