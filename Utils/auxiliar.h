#ifndef AUXILIAR_H
#define AUXILIAR_H
#include <vector>
#include <iostream>
#include <map>
#include "huffman.h"
using namespace std;
typedef unsigned char uchar;
void writeArray(vector<uchar> & s);
void writeBit(int bit, vector<uchar> & s);
void writeByte(uchar c, vector<uchar> & s);
void completeByte(vector<uchar> &s);
void printBitxBit(vector<uchar> & s);
void saveCompression(vector<uchar> & s, char * dest);
void openFileCompression(vector< uchar > & s, int *freq , char * path);
void openFileDecompression(vector< uchar > & s, char * path);
int readBit(int offset, uchar & c);
map<string,uchar> inverseTable(map<uchar,string> s);
map<uchar,string> verboseMap();
void printTable(map<uchar, string> mapa, vector<int> freq);
bool getOptions(char **& options , char * argv[]);
void printInMemory(vector<uchar> & toMemory);
void printFile(char * path);
string getAllOptions(char * str);
void encode(vector<uchar> & toMemory, vector<uchar> & encoding, vector<int> & freq,
            node * & root, map<uchar,string> & tabla, char * inputFile, char * outputFile, huffmanQueue & nodeQueue );
void decode(vector<uchar> & toMemory, vector<uchar> & encoding, vector<int> & freq,
            node * & root, map<uchar,string> & tabla, char * inputFile, char * outputFile);
void setOptions(char **& options);

#endif
