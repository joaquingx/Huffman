#include "auxiliar.h"
#include "huffman.h"
#include <vector>
#include <map>
#include <iostream>
#define SEPARATOR 32
#define SBYTE 8
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

map<uchar, string> getEncoding(node * root)
{
  map<uchar,string> mapa;
  getEncodingR(root,0,mapa);
  return mapa;
}
int cnt = 0;
string actual="00000000000000000000000000000000000000000000000000";
void getEncodingR(node * root , node * parent , map<uchar,string> & mapa)
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

void pushLetter(node *& actual, uchar c)
{
  actual->letter = c;
}

void generatingTree(node *& actual, map<node * , node * > & parent, map<node * , int > &mapa, bool isTerminal)
{
  if(mapa.count(actual))
    {
      cout << mapa[actual] << "\n";
      while(mapa[actual] == 2 or (actual->isTerminal))
        {
          cout << "con2\n";
          actual = parent[actual];
        }
      if(actual == 0)
        {
          cout << "chaval\n";
          return;
        }
    }
  node * nuevo = new node(0,0,isTerminal);
  if(!mapa.count(actual) or mapa[actual] == 0)
    {
      cout << "con 0\n";
      actual->childs[0] = nuevo;
      mapa[actual] = 1;
      parent[actual->childs[0]] = actual;
      actual = actual->childs[0];
      // cout << "El hijo tiene direccion :" << (*actual)->childs[0];
      // actual = &((*actual)->childs[0]);
      // (*actual) = (*actual)->childs[0];
    }
  if(mapa[actual] == 1)
    {
      cout << "con 1\n";
      actual->childs[1] = nuevo;
      mapa[actual] = 2;
      parent[actual->childs[1]] = actual;
      actual = actual->childs[1];
      // actual = &((*actual)->childs[1]);
      // (*actual) = (*actual)->childs[1];
    }
}


node * decodingTree( vector<uchar> & s, int &offset)
{
#ifdef DEBUG
  cout << "Impresion de compresion de arbol:\n";
  for(int i = 0 ; i < s.size() and int(s[i]) != SEPARATOR ; ++i)
    {
      cout << int(s[i]) << " ";
    }
#endif
  uchar nuevaLetra=0;
  int byteCounter=7, totalSize = SBYTE * int(s.size()), actualSize=0;
  bool flag=0;
  node * root= new node(0,0,0);
  node * guardame =  root;
  map<node * , int> mapa;
  map<node * , node * > parent;
  for(int i = 0; i < s.size() and int(s[i]) != SEPARATOR ; ++i)
    {
      offset=i;
      cout <<"rooteame:"<< root << " " << root->childs[0] << " " << root->childs[1] << "\n";
      for(int j = SBYTE-1; j >= 0; --j )
        {
          int saveBit=readBit(j,s[i]);
          if(flag)
            {
              cout << saveBit << " ";
              nuevaLetra |= (saveBit << byteCounter);
              --byteCounter;
              if(byteCounter < 0)
                {
                  cout <<"esta es la nueva letra:"<< char(nuevaLetra) << "\n";
                  pushLetter(root,nuevaLetra);
                  flag=0;
                  cout << "\n";
                }
            }
          else
            {
              actualSize = j + i*SBYTE;
              if(totalSize - actualSize < SBYTE)
                break;
              generatingTree(root,parent,mapa,saveBit);
              if(saveBit == 1)
                {
                  cout << "Binario de la letra:\n";
                  flag = 1;
                  byteCounter=7;
                  nuevaLetra=0;
                }
            }
        }
    }
  return guardame;
}


vector<uchar> decodingText(vector<uchar> & s, map<string,uchar> tabla, int offset)
{
  vector<uchar> res;
  int cnt = 0;
  string act = "";
  for(int i = offset ;i < s.size() ; ++i)
    {
      for(int j = 0; j < SBYTE ; ++cnt)
        {
          int saveBit=readBit(j,s[i]);
          act += char(saveBit+'0');
          if(tabla.count(act))
            {
              res.push_back(tabla[act]);
              act.clear();
            }
        }
    }
  return res;
}
