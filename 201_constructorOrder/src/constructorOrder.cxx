#include <iostream>

using namespace std;

struct V {
  V() { cout << "V()" << endl; }
};

struct V2 {
  V2() { cout << "V2()" << endl; }
};

struct A {
  A() { cout << "A()" << endl; }
};

struct B : virtual V {
  B() { cout << "B()" << endl; }
};

struct C : B, virtual V2 {
  C() { cout << "C()" << endl; }
};

struct D : C, virtual V {
  A obj_A;
  D()
{ cout << "D()" << endl; }
};

int main() {
  D c;
}
