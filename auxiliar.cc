#include <vector>
#include <iostream>
#include "auxiliar.h"
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

void writeByte(uchar c, vector<uchar> & s)
{
  unsigned char nuevo = 0;
  int nuevoCount=0;
  /* cout << "Que ya no quiero ni follar que estoy cansao : "<<int(c) << "\n"; */
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
      writeBit(0,s);
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

void saveCompression(vector<uchar> & s)
{
  FILE * saveFile;
  saveFile = fopen("compreso.txt","w");
  for(int i = 0 ;i < s.size() ; ++i)
    {
      fputc(s[i],saveFile);
    }
  fclose(saveFile);
}
