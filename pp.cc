#include <bits/stdc++.h>
using namespace std;
struct node{
  int freq;
  node * childs[2];
  char letter;
  bool isTerminal;
  node(int freq, char letter , bool isTerminal)
    {
      this->freq = freq;
      this->letter = letter;
      this->isTerminal=isTerminal;
    }
  ~node();
};

void caca(node *& ll)
{
  cout << ll << "\n";
  ll = new node(0,0,0);
  cout << "despues:" << ll << "\n";
  ll->childs[0] = new node(0,0,0);
  cout << "para hijos:" << ll->childs[0] << "\n";
}

int main()
{
  node * x = new node(0,0,0);
  cout << x << "\n";
  caca(x);
  cout << "despues para x:"  << x << "\n";
  cout << "para hijos de :" << x->childs[0] << "\n";
  return 0;
}
