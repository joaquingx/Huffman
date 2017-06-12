#ifndef AUXILIAR_H
#define AUXILIAR_H
#include <vector>
#include <iostream>
using namespace std;
typedef unsigned char uchar;
void writeArray(vector<uchar> & s);
void writeBit(int bit, vector<uchar> & s);
void writeByte(uchar c, vector<uchar> & s);
void completeByte(vector<uchar> &s);
void printBitxBit(vector<uchar> & s);
void saveCompression(vector<uchar> & s);
#endif
