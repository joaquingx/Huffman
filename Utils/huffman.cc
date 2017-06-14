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
  childs[0] = NULL;
  childs[1] = NULL;
}

node::~node()
{
  // delete childs[0];
  // delete childs[1];
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
string actualString="00000000000000000000000000000000000000000000000000";
void getEncodingR(node * root , node * parent , map<uchar,string> & mapa)
{
  //creo que siempre es full
  // cout << cnt << " ";
  if(root != NULL)
    {
      // cout << root->isTerminal << "\n";
      if(parent != NULL)
        if(parent->childs[0] == root)
          actualString[cnt++] = '0';
        else
          actualString[cnt++] = '1';
      if(root->isTerminal) mapa[root->letter] = actualString.substr(0,cnt);
      if(!root->isTerminal)
        getEncodingR(root->childs[0],root,mapa);
      if(root->childs[0] != NULL and !root->isTerminal)
        --cnt;
      if(!root->isTerminal)
        getEncodingR(root->childs[1],root,mapa);
      if(root->childs[1] != NULL and !root->isTerminal)
        --cnt;
    }

}

void traversalTree(node * root)
{
  if(root != 0)
    {
      cout << root->freq << " " << root->isTerminal << " ";
      if(root->childs[0])
        cout << root->childs[0] << " ";
      if(root->childs[1])
        cout << root->childs[1] << " ";
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
  // cout << "-------------------------\n";
  int cnt = 0;
  while(actual->isTerminal)
    {
      // cout << actual<< " " << parent[actual] << "--" << "\n";
      if(cnt == 10)
        break;
      ++cnt;
      actual = parent[actual];
    }
  // cout << "ahora soy : " << actual << "\n";
  if(mapa.count(actual))
    {
      while(mapa[actual] == 2)
        actual = parent[actual];
      if(actual == 0)
        {
          // cout << "chaval\n";
          return;
        }
    }
  node * nuevo = new node(0,0,isTerminal);
  if(!mapa.count(actual))
    {
      // cout << "con 0\n";
      actual->childs[0] = nuevo;
      mapa[actual] = 1;
      parent[actual->childs[0]] = actual;
      actual = actual->childs[0];
      // cout << "entre a izquierda\n";
    }
  else if(mapa[actual] == 1)
    {
      // cout << "con 1\n";
      actual->childs[1] = nuevo;
      mapa[actual] = 2;
      parent[actual->childs[1]] = actual;
      actual = actual->childs[1];
      // cout << "entre a derecha\n";
    }
  // cout << actual << " " << parent[actual] << "\n";
  // cout << "-------------------------\n";
}


node * decodingTree( vector<uchar> & s, int &offset)
{
#ifdef DEBUG
  cout << "Impresion de compresion de arbol:\n";
  for(int i = 0 ; i < s.size() and int(s[i]) != SEPARATOR ; ++i)
    {
      cout << int(s[i]) << " ";
    }
  cout << "\n";
#endif
  int cc=0;
  for(; cc < s.size() and int(s[cc]) != SEPARATOR ; ++cc);
  uchar nuevaLetra=0;
  int byteCounter=7, totalSize = SBYTE * cc, actualSize=0;
  bool flag=0;
  node * root= new node(0,0,0);
  node * guardame =  root;
  map<node * , int> mapa;
  map<node * , node * > parent;
  parent[root] = 0;
  // cout << totalSize << " el total size es\n";
  for(int i = 0; i < s.size() and int(s[i]) != SEPARATOR ; ++i)
    {
      offset=i;
      // cout <<"rooteame:"<< root << " " << root->childs[0] << " " << root->childs[1] << "\n";
      for(int j = SBYTE-1; j >= 0; --j )
        {
          int saveBit=readBit(j,s[i]);
          if(flag)
            {
              nuevaLetra |= (saveBit << byteCounter);
              --byteCounter;
              if(byteCounter < 0)
                {
                  pushLetter(root,nuevaLetra);
                  flag=0;
                }
            }
          else
            {
              actualSize = (SBYTE-j) + i*SBYTE ;
              // cout << "tam actual :" << actualSize << "\n";
              if(totalSize - actualSize < SBYTE)
                break;
              generatingTree(root,parent,mapa,saveBit);
              if(saveBit == 1)
                {
                  flag = 1;
                  byteCounter=7;
                  nuevaLetra=0;
                }
            }
        }
    }
  return guardame->childs[0];
}


vector<uchar> decodingText(vector<uchar> & s, map<string,uchar> tabla, int offset)
{
  vector<uchar> res;
  // int cnt = 0;
  string act = "";
  for(int i = offset+1 ;i < s.size() ; ++i) // uno mas alla del espacio
    {
      for(int j = SBYTE-1 ; j >= 0 ; --j)
        {
          int saveBit=readBit(j,s[i]);
          act += char(saveBit+'0');
          if(tabla.count(act))
            {
              res.push_back(tabla[act]);
              act = "";
            }
        }
    }
  return res;
}
