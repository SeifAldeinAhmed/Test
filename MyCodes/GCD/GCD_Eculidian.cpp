#include <iostream>

int gcd_eculidian(int a, int b) {
  if(b==0)
  {
     return a;
  }
  else{
   return gcd_eculidian(b, a%b);
  }
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << gcd_eculidian(a, b) << std::endl;
  return 0;
}
