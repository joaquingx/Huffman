#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP
#include <vector>
#include <map>
using namespace std;
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
map<char, string> getEncoding(node * root);
void getEncodingR(node * root , node * parent , map<char,string> & mapa);
void traversalTree(node * root);

#endif
