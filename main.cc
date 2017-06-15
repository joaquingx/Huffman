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
  map<uchar, string>  tabla;
  char ** options;
  if(!getOptions(options , argv))
    return 0;
  if(strcmp("-c",options[0]) == 0)
    {
      openFileCompression(toMemory,freq,options[1]);
      setNodesQueue(nodeQueue);
      node * root = buildingTree(nodeQueue);
      vector<uchar> encoding = getTree(root);
      completeByte(encoding);
      writeByte(uchar(SEPARATOR),encoding);
      tabla = getEncoding(root);
      setEncodingToText(toMemory ,tabla, encoding);
      completeByte(encoding);
      saveCompression(encoding,options[2]);
    }
  if(strcmp("-d",options[0]) == 0)
    {
      int offset=0;
      openFileDecompression(toMemory,options[1]);
      node * root = decodingTree(toMemory, offset);
      tabla = getEncoding(root);
      map<string,uchar> nTabla = inverseTable(tabla);
      vector<uchar> decoding = decodingText(toMemory,nTabla,offset+1);
      saveCompression(decoding,options[2]);
    }
  if(argv[4] != NULL and (strcmp("-v",argv[4])==0))
    printTable(tabla);
  return 0;
}
