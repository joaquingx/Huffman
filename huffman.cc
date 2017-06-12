#include "auxiliar.h"
#include "huffman.h"
#include <vector>
#include <map>
#include <iostream>
using namespace std;
typedef unsigned char uchar;

node::node(int freq, uchar letter , bool isTerminal)
{
  this->freq = freq;
  this->letter = letter;
  this->isTerminal = isTerminal;
  childs[0] = 0;
  childs[1] = 0;
}

node::~node()
{
  delete childs[0];
  delete childs[1];
}

node * merge(node *& a , node *& b)
{
  node * c  = new node(a->freq + b->freq , 0, false);
  c->childs[0] = a;
  c->childs[1] = b;
  return c;
}

map<char, string> getEncoding(node * root)
{
  map<char,string> mapa;
  getEncodingR(root,0,mapa);
  return mapa;
}
int cnt = 0;
string actual="00000000000000000000000000000000000000000000000000";
void getEncodingR(node * root , node * parent , map<char,string> & mapa)
{
  //creo que siempre es full
  if(root != 0)
    {
      if(parent != 0)
        if(parent->childs[0] == root)
          actual[cnt++] = '0';
        else
          actual[cnt++] = '1';
      if(root->isTerminal) mapa[root->letter] = actual.substr(0,cnt);
      getEncodingR(root->childs[0],root,mapa);
      if(root->childs[0] != 0)
        --cnt;
      getEncodingR(root->childs[1],root,mapa);
      if(root->childs[1] != 0)
        --cnt;
    }

}

void traversalTree(node * root)
{
  if(root != 0)
    {
      cout << root->freq << " ";
      if(root->isTerminal)
        cout << int(root->letter);
      cout << "\n";
      traversalTree(root->childs[0]);
      traversalTree(root->childs[1]);
    }
}
vector<uchar> getTree(node * root)
{
  vector<uchar> compressTree;
  getTreeR(root,compressTree);
  completeByte(compressTree);
  return compressTree;
}


void getTreeR(node * root, vector<uchar> & s)
{
  if(root != 0)
    {
      if(!root->isTerminal)
        writeBit(0,s);
      else
        {
          // cout << bitCount << "\n";
          writeBit(1,s);
          writeByte(root->letter,s);
        }
      getTreeR(root->childs[0],s);
      getTreeR(root->childs[1],s);
    }
}


