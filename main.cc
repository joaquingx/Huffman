#include <bits/stdc++.h>
// #include "auxiliar.h"
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
  char path[100],buffer[100];
  if(argv[1] == NULL)
    {
      cout << "Usage:  ./executable [path]";
      cout << "\n";
      return 0;
    }
  strcpy(path,argv[1]);
  int nToMemory=0;
  FILE * pFile ;
  memset(freq , 0 , sizeof freq);
  pFile = fopen(path, "r");
  if(pFile == NULL ) perror("Error opening file\n");
  else
    {
      while ( ! feof (pFile) )
        {
          if ( fgets (buffer , 100 , pFile) == NULL ) break;
          ++nToMemory;
        }
      pFile = fopen(path, "r");// Para regresar de EOF
      toMemory.resize(nToMemory);
      for(int i = 0 ; !feof(pFile) ; ++i)
        {
          memset(buffer,0,sizeof buffer);
          if ( fgets (buffer , 100 , pFile) == NULL ) break;
          for(int j = 0 ; buffer[j] != 0 ; ++j)
            {
              toMemory[i].push_back(j);
              ++freq[int(buffer[j])];
            }
        }
      fclose (pFile);
    }
#ifdef DEBUG
  getFrequencies();
#endif
  setNodesQueue(nodeQueue);
  node * root = buildingTree(nodeQueue);
  // cout << root->childs[0] << " " << root->childs[1] << "\n";
  cout << "Traversal del Huffman:\n";
  traversalTree(root);
  vector<uchar> encoding = getTree(root);
#ifdef DEBUG
  cout << "Encoding del Arbol:\n";
  for(int i = 0 ;i < encoding.size() ; ++i)
    cout << int(encoding[i]) << "\n";
  cout << "Fin Encoding\n";
#endif
  // completeByte(encoding); // debo hcaerlo dentro de huffman alparecer!
  // encoding.push_back(' ');
  // map<char, string>  tabla = getEncoding(root);
  // for(auto it = tabla.begin() ; it != tabla.end() ; ++it)
  //   cout << (it->first) << " " << (it->second) << "\n";
  return 0;
}
