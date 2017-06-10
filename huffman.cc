#include "auxiliar.h"
#include "huffman.h"
#include <vector>
#include <map>
typedef unsigned char uchar;

node::node(int freq, uchar letter , bool isTerminal)
{
  this->freq = freq;
  this->letter = letter;
  this->isTerminal = isTerminal;

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

map<char, string> getEncoding(node * root,vector<uchar> & s,vector<uchar> v)
{
  map<char,string> mapa;
  getEncodingR(root,s,v,mapa,0);
}
string actual;
void getEncodingR(node * root, vector<uchar> & s , vector<uchar> v , map<char,string> & mapa, uchar lado)
{
  if(root != 0)
    {
      if(lado  == '0' or lado == '1')
        actual += lado;
      getEncodingR(root->childs[0],s,v,mapa,'0');
      getEncodingR(root->childs[1],s,v,mapa,'1');
    }

}

vector<uchar> getTree(node * root)
{
  vector<uchar> compressTree;
  getTreeR(root,compressTree);
}


void getTreeR(node * root, vector<uchar> & s)
{
  if(root != 0)
    {
      if(!root->isTerminal)
        writeBit(0,s);
      else
        {
          writeBit(1,s);
          writeByte(root->letter,s);
        }
      getTreeR(root->childs[0],s);
      getTreeR(root->childs[1],s);
    }
}

