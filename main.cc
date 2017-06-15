#include <bits/stdc++.h>
#include "Utils/auxiliar.h"
#include "Utils/huffman.h"
using namespace std;
#define MAXN 256
int freq[MAXN];
vector <uchar> toMemory;
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
// #ifdef DEBUG
//   cout << "Orden de los nodos\n";
//   for(auto it = S.begin(); it != S.end() ; ++it)
//     cout << (*it)->letter << " ";
//   cout << "\n";
// #endif
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
      cout << "Usage:  ./Huffman  [-c/-d] [Origin file path] [Dest file path]\n";
      cout << "-c : compress\n";
      cout << "-d : decompress\n";
      return 0;
    }
  if(strcmp("-c",argv[1]) == 0)
    {
      openFileCompression(toMemory,freq,argv[2]);
      setNodesQueue(nodeQueue);
      node * root = buildingTree(nodeQueue);
      vector<uchar> encoding = getTree(root);
      completeByte(encoding);
      writeByte(uchar(SEPARATOR),encoding);
      // encoding.push_back(uchar(SEPARATOR));
      map<uchar, string>  tabla = getEncoding(root);
      setEncodingToText(toMemory ,tabla, encoding);
      completeByte(encoding);
      saveCompression(encoding,argv[3]);
      printTable(tabla);
    }
  if(strcmp("-d",argv[1]) == 0)
    {
      int offset=0;
      openFileDecompression(toMemory,argv[2]);
      node * root = decodingTree(toMemory, offset);
      map<uchar,string> tabla = getEncoding(root);
      map<string,uchar> nTabla = inverseTable(tabla);
      vector<uchar> decoding = decodingText(toMemory,nTabla,offset+1);
      printTable(tabla);
      saveCompression(decoding,argv[3]);
    }
  return 0;
}
