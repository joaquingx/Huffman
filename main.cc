#include <bits/stdc++.h>
using namespace std;
#define MAXN 255
int freq[MAXN];
vector< vector < int > > oraciones;


struct huffmanTree{
  struct node{
    int freq;
    node * childs[2];
    char letter;
    bool isTerminal;
    node(int freq, char letter)
      {
        this->freq = freq;
        this->letter = letter;
        this->isTerminal = true;
      }
  };
  node * root;
  void merge(node * a , node * b);
  void getAllLetters();
};


void getFrequencies()
{
  for(int i = 0 ;i < MAXN ; ++i)
    if(freq[i] > 0)
      cout << char(i) << ":" << freq[i] << "\n";
}

int main()
{
  char path[100];
  strcpy(path,"facil.txt");
  int nOraciones=0;
  FILE * pFile ;
  char buffer[100];
  memset(freq , 0 , sizeof freq);
  pFile = fopen(path, "r");
  if(pFile == NULL ) perror("Error opening file\n");
  else
    {
      while ( ! feof (pFile) )
        {
          if ( fgets (buffer , 100 , pFile) == NULL ) break;
          ++nOraciones;
        }
      pFile = fopen(path, "r");// Para regresar de EOF
      oraciones.resize(nOraciones);
      for(int i = 0 ; !feof(pFile) ; ++i)
        {
          memset(buffer,0,sizeof buffer);
          if ( fgets (buffer , 100 , pFile) == NULL ) break;
          for(int j = 0 ; buffer[j] != 0 ; ++j)
            {
              oraciones[i].push_back(j);
              ++freq[int(buffer[j])];
            }
        }
      fclose (pFile);
    }
  getFrequencies();
  return 0;
}
