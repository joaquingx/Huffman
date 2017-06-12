#include <bits/stdc++.h>
using namespace std;

int main()
{
  FILE * file;
  file = fopen("escrito.txt","w");
  fputs("a",file);
  fputs("b",file);
  fclose(file);
  unsigned char b;
  b |= (1<<6);
  b |= (0<<7);
  cout << int(b) << "\n";
}
