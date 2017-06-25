#include <bits/stdc++.h>
#include "auxiliar.h"
#include "huffman.h"
#define MAXN 1000
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
  cout << "Binary Representation:\n";
  for(int i = 0 ;i < s.size() ; ++i)
    {
      for(int j = 7 ; j >= 0;--j)
        cout << ((s[i]>>j) & 1) << " ";
    }
  cout << "\n\n";
}

void saveCompression(vector<uchar> & s, char * dest)
{
  FILE * saveFile;
  saveFile = fopen(dest,"wb");
  for(int i = 0 ;i < s.size() ; ++i)
    {
      // cout << int(s[i]) << " ";
      fputc(s[i],saveFile);
    }
  fclose(saveFile);
}

void openFileCompression(vector< uchar > & s, vector<int> & freq , char * path)
{
  FILE * pFile ;
  pFile = fopen(path, "rb");
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
  FILE * pFile ;
  pFile = fopen(path, "rb");
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

void printFile(char * path)
{
  FILE * pFile ;
  pFile = fopen(path, "r");
  if(pFile == NULL ) perror("Error opening file\n");
  else
    {
      while(1)
        {
          int x = getc(pFile);
          if(x != -1)
            {
              cout << char(x);
            }
          else
            break;
        }
      fclose (pFile);
    }
  cout << "\n";
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

map<uchar,string> verboseMap()
{
  map<uchar,string> vMap;
  for(int i = 0 ; i <= 255 ; ++i)
    {
      vMap[uchar(i)] = uchar(i);
    }
  vMap[uchar(10)] = "ENT";
  vMap[uchar(32)] = "SPC";
  return vMap;
}


void printTable(map<uchar, string> mapa, vector<int> freq)
{
  map<uchar,string> vMap = verboseMap();
  int acc=0;
  for(int i = 0 ; i < freq.size() ; ++i)
    acc+=freq[i];
  cout << "Conversion Table [ Character| Redundancy | Representation ] : \n";
  for(auto it = mapa.begin() ; it != mapa.end() ; ++it)
    printf("%3s : %.5f %s\n",vMap[it->first].c_str(), float(freq[it->first])/float(acc),(it->second).c_str());
  cout << "\n";
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
      string nuevo(argv[1]);
      if(nuevo.find("c") != string::npos )
        strcpy(options[2],"compress.huffman");
      else
        strcpy(options[2],"decompress.txt");
      for(int i = 0 ;i < 2 ; ++i)
        {
          strcpy(options[i],argv[i+1]);
        }
    }
  else if(argv[1] == NULL or argv[2] == NULL or argv[3] == NULL)
    {
      string pathMan = "../man.txt";
      printFile((char*)pathMan.c_str());
      return 0;
    }
  return 1;
}

void printInMemory(vector<uchar> & toMemory)
{
  cout << "In Memory:\n";
  for(int i = 0 ;i < toMemory.size() ; ++i)
    cout << int(toMemory[i]) << " ";
}

uchar getSeparator(vector<uchar> & toMemory)
{
  int exist[256];
  memset(exist, 0 ,sizeof exist);
  for(int i = 0 ; i < toMemory.size() ; ++i)
    {
      ++exist[int(toMemory[i])];
    }
  for(int j = 1 ; j < 256 ; ++j)
    if(exist[j] == 0)
      return uchar(j);
}

string getAllOptions(char * str)
{
  return string(str).substr(1);
}


void encode(vector<uchar> & toMemory, vector<uchar> & encoding, vector<int> & freq,
            node * & root, map<uchar,string> & tabla, char * inputFile, char * outputFile, huffmanQueue & nodeQueue )
{
  openFileCompression(toMemory,freq,inputFile);
  setNodesQueue(nodeQueue,freq);
  root = buildingTree(nodeQueue);
  encoding = getTree(root);
  completeByte(encoding);
  uchar separator = getSeparator(encoding);
  writeByte(separator,encoding);
  encoding.insert(encoding.begin(),separator);
  tabla = getEncoding(root);
  setEncodingToText(toMemory ,tabla, encoding);
  completeByte(encoding);
  saveCompression(encoding,outputFile);
}

void decode(vector<uchar> & toMemory, vector<uchar> & encoding, vector<int> & freq,
            node * & root, map<uchar,string>&  tabla, char * inputFile, char * outputFile)
{
  int offset=0;
  openFileDecompression(toMemory,inputFile);
  root = decodingTree(toMemory, offset);
  tabla = getEncoding(root);
  map<string,uchar> nTabla = inverseTable(tabla);
  encoding = decodingText(toMemory,nTabla,offset+1);
  saveCompression(encoding,outputFile);
}

void setOptions(char **& options)
{
  vector<uchar> toMemory,encoding;
  vector<int> freq(256,0);
  node * root; // Huffman Tree.
  string aOptions = getAllOptions(options[0]);
  map<uchar,string> tabla,vMap;
  huffmanQueue nodeQueue;
  string pathHow = "../How.txt";
  for(int i = 0 ;i < aOptions.size() ; ++i)
    {
      switch(aOptions[i])
        {
        case 'c':
          encode(toMemory,encoding,freq,root,tabla,options[1],options[2],nodeQueue);
          break;
        case 'd':
          decode(toMemory,encoding,freq,root,tabla,options[1],options[2]);
          break;
        case 't':
          printTable(tabla,freq);
          break;
        case 'b':
          printBitxBit(encoding);
          break;
        // case 'p':
        //   printProgress();
        //   break;
        case 'h':
          printFile((char*)pathHow.c_str());
          break;
        }
    }
}
