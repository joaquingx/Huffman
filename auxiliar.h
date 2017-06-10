#ifndef AUXILIAR_H
#define AUXILIAR_H
#include <vector>
using namespace std;
typedef unsigned char uchar;
uchar acc = 0;
int bitCount = 0;

void writeArray(vector<uchar> & s)
{
  if (++bitCount == 8)
    {
      s.push_back(acc);
      acc = 0;
      bitCount = 0;
    }
}

void writeBit(int bit, vector<uchar> & s)
{
  acc |= (bit << bitCount);
  writeArray(s);
}

void writeByte(uchar c, vector<uchar> & s)
{
  while(int(c) > 0)
    {
      if(c%2==0)
        acc |= (0 << bitCount);
      else
        acc |= (1 << bitCount);
      c /= 2;
      writeArray(s); // writing reverse
    }
}

void completeByte(vector<uchar> &s)
{
  while(bitCount < 8)
    {
      acc |= (1 << bitCount);
      ++bitCount;
    }
  s.push_back(acc);
  acc=0;
  bitCount=0;
}
#endif
