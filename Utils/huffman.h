#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP
#include <vector>
#include <map>
#include <set>
using namespace std;
/* #define SEPARATOR 233 */
#define SBYTE 8

typedef unsigned char uchar;
struct node{
  int freq;
  node * childs[2];
  uchar letter;
  bool isTerminal;
  node(int freq, uchar letter , bool isTerminal);
  ~node();
};

node * merge(node *& a , node *& b);
vector<uchar> getTree(node * root);
void getTreeR(node * root, vector<uchar> &s);
void setTree();
map<uchar, string> getEncoding(node * root);
void getEncodingR(node * root , node * parent , map<uchar,string> & mapa);
void traversalTree(node * root);
node * decodingTree( vector<uchar> & s, int &offset);
vector<uchar> decodingText(vector<uchar> & s, map<string,uchar> tabla, int offset);
void setEncodingToText(vector<uchar> & toMemory ,  map<uchar,string> & tabla, vector<uchar> & encoding);
uchar getSeparator(vector<uchar> & toMemory);

struct nodeCompare{
  bool operator() (const node * a , const node * b)
  {
    if(a->freq != b->freq)
      return a->freq < b->freq;
    else
      return a < b;
  }
};
typedef set< node * , nodeCompare >  huffmanQueue;
void getFrequencies(vector<int> & freq, map<uchar,string> & vMap);
void setNodesQueue(huffmanQueue & S, vector<int>  & freq);
node * buildingTree(huffmanQueue & S);
#endif
