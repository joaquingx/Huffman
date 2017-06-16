#include <bits/stdc++.h>
#include "auxiliar.h"
#define MAXN 10000
using namespace std;
typedef unsigned char uchar;
uchar acc = 0;
int bitCount = 7;

void writeArray(vector<uchar> & s)
{
  if (--bitCount < 0)
    {
      s.push_back(acc);
      acc = 0;
      bitCount = 7;
    }
}

void writeBit(int bit, vector<uchar> & s)
{
  acc |= (bit << bitCount);
  writeArray(s);
}

int readBit(int offset, uchar & c)
{
  return ((c>>offset ) & 1);
}

void writeByte(uchar c, vector<uchar> & s)
{
  uchar nuevo = 0;
  int nuevoCount=0;
  while(int(c) > 0)
    {
      if(c % 2 ==0)
        nuevo |= (0 << nuevoCount);
      else
        nuevo |= (1 << nuevoCount);
      c /= 2;
      ++nuevoCount;
    }
  while(nuevoCount < 8)
    {
      ++nuevoCount;
      nuevo |= (0 << nuevoCount);
    }
  for(int counter = 7; counter >= 0 ; --counter)
    {
      writeBit( ((nuevo >> counter) & 1) , s);
    }
}

void completeByte(vector<uchar> &s)
{
  while(bitCount != 7)
    {
      writeBit(1,s);
    }
}

void printBitxBit(vector<uchar> & s)
{
  for(int i = 0 ;i < s.size() ; ++i)
    {
      for(int j = 7 ; j >= 0;--j)
        cout << ((s[i]>>j) & 1) << " ";
    }
  cout << "\n";
}

void saveCompression(vector<uchar> & s, char * dest)
{
  FILE * saveFile;
  saveFile = fopen(dest,"w");
  for(int i = 0 ;i < s.size() ; ++i)
    {
      // cout << int(s[i]) << " ";
      fputc(s[i],saveFile);
    }
  fclose(saveFile);
}

void openFileCompression(vector< uchar > & s, int *freq , char * path)
{
  char buffer[MAXN];
  FILE * pFile ;
  memset(freq , 0 , sizeof freq);
  pFile = fopen(path, "r");
  if(pFile == NULL ) perror("Error opening file\n");
  else
    {
      while(1)
        {
          int x = getc(pFile);
          if(x != -1)
            {
              s.push_back(uchar(x));
              ++freq[int(uchar(x))];
            }
          else
            break;
        }
      fclose (pFile);
    }
}

void openFileDecompression(vector< uchar > & s, char * path)
{
  char buffer[MAXN];
  FILE * pFile ;
  pFile = fopen("compress.txt", "rb");
  if(pFile == NULL ) perror("Error opening file\n");
  else
    {
      while(1)
        {
          int x = getc(pFile);
          if(x != -1)
            s.push_back(uchar(x));
          else
            break;
        }
      fclose(pFile);
    }
}

map<string,uchar> inverseTable(map<uchar,string> s)
{
  map<string,uchar> nuevo;
  for(auto it = s.begin() ; it != s.end() ; ++it)
    {
      nuevo[it->second] = it->first;
    }
  return nuevo;
}

map<uchar,string> vMap;
void verboseMap()
{
  for(int i = 0 ; i <= 255 ; ++i)
    {
      vMap[uchar(i)] += "0x";
      vMap[uchar(i)] += uchar(i);
    }
  vMap[uchar(10)] = "ENT";
  vMap[uchar(32)] = "SPC";
}

void printTable(map<uchar, string> mapa)
{
  verboseMap();
  cout << "Conversion Table: \n";
  for(auto it = mapa.begin() ; it != mapa.end() ; ++it)
    cout << vMap[(it->first)] << ":" << (it->second) << "\n";
}

bool getOptions(char **& options , char * argv[])
{
  options = (char **)malloc(3*sizeof(char*));
  options[0] = (char *)malloc(100 * sizeof(char));
  options[1] = (char *)malloc(100 * sizeof(char));
  options[2] = (char *)malloc(100 * sizeof(char));
  if(argv[3] != NULL and argv[2] != NULL and argv[1] != NULL)
    {
      for(int i = 0 ;i < 3 ; ++i)
        {
          strcpy(options[i],argv[i+1]);
        }
    }
  else if(argv[3]== NULL and argv[2] != NULL and argv[1] != NULL)
    {
      if(strcmp(argv[1],"-c") == 0)
        strcpy(options[2],"compress.txt");
      else
        strcpy(options[2],"decompress.txt");
      for(int i = 0 ;i < 2 ; ++i)
        {
          strcpy(options[i],argv[i+1]);
        }
    }
  else if(argv[1] == NULL or argv[2] == NULL or argv[3] == NULL)
    {
      cout << "Usage:  ./Huffman  -c|-d input-file [output-file]\n";
      cout << "-c : compress\n";
      cout << "-d : decompress\n";
      return 0;
    }
  return 1;
}

void printInMemory(vector<uchar> & toMemory)
{
  cout << "In Memory:\n";
  for(int i = 0 ;i < toMemory.size() ; ++i)
    cout << toMemory[i] << " ";
}
