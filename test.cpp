#include <iostream>
#include <string>

using namespace std;


int main() {
  int a = 100;
  // & lay dia chi tham khao
  cout << &a << endl;
  cout << *&a << endl; // *(&a)
  cout << *&*&a << endl; // *(&(*(&a))
  cout << *&*&*&a << endl;  // *(&(*(&(*(&a)))))
  return 0;
}