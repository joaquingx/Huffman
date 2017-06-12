#include <bits/stdc++.h>
#include "auxiliar.h"
#include "huffman.h"
using namespace std;
#define MAXN 256
int freq[MAXN];
vector< vector < int > > toMemory;
typedef unsigned char uchar;

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
huffmanQueue nodeQueue;

void getFrequencies()
{
  for(int i = 0 ;i < MAXN ; ++i)
    if(freq[i] > 0)
      cout << uchar(i) << ":" << freq[i] << "\n";
}
void setNodesQueue(huffmanQueue & S)
{
  node * aux;
  for(int  i = 0 ; i < MAXN ; ++i)
    {
      if(freq[i] > 0)
        {
          aux = new node (freq[i],uchar(i),true);
          S.insert(aux);
        }
    }
}

node * buildingTree(huffmanQueue & S)
{
#ifdef DEBUG
  cout << "Orden de los nodos\n";
  for(auto it = S.begin(); it != S.end() ; ++it)
    cout << (*it)->letter << " ";
  cout << "\n";
#endif
  while(S.size() > 1)
    {
      node * first = (*S.begin());
      S.erase(S.begin());
      node * second = (*S.begin());
      S.erase(S.begin());
      node * fusion = merge(first,second);
      S.insert(fusion);
    }
  return (*S.begin());
}

int main(int argc, char * argv[])
{
  if(argv[1] == NULL or argv[2] == NULL or argv[3] == NULL)
    {
      cout << "Usage:  ./executable  [-c/-d] [Origin file path] [Dest file path]\n";
      cout << "-c : compress\n";
      cout << "-d : decompress\n";
      return 0;
    }
  if(strcmp("-c",argv[1]) == 0)
    {
      openFile(toMemory,freq,argv[2]);
#ifdef DEBUG
      getFrequencies();
#endif
      setNodesQueue(nodeQueue);
      node * root = buildingTree(nodeQueue);
      // cout << root->childs[0] << " " << root->childs[1] << "\n";
#ifdef DEBUG
      cout << "Traversal del Huffman:\n";
      traversalTree(root);
#endif
      vector<uchar> encoding = getTree(root);
#ifdef DEBUG
      cout << "Encoding del Arbol:\n";
      for(int i = 0 ;i < encoding.size() ; ++i)
        cout << encoding[i] << "\n";
      cout << "Fin Encoding\n";
      printBitxBit(encoding);
#endif
      encoding.push_back(' ');
      map<char, string>  tabla = getEncoding(root);
#ifdef DEBUG
      for(auto it = tabla.begin() ; it != tabla.end() ; ++it)
        cout << (it->first) << ":" << (it->second) << "\n";
#endif
      for(int i = 0 ;i < toMemory.size() ; ++i)
        for(int j = 0 ; j < toMemory[i].size() ; ++j)
          {
            string k = tabla[char(toMemory[i][j])];
            for(int l = 0 ; l < k.size() ; ++l)
              writeBit(int(k[l]-'0'),encoding);
          }
      completeByte(encoding);
      saveCompression(encoding,argv[3]);
    }
  return 0;
}
