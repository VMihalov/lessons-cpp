#include <iostream>
#include "vector.h"

using namespace std;

int main() {
  Vector a(7, -3, -4),
         b(3, -4, 2),
         c(1, 0, 3);

  cout << "Vectors " 
       << "a(" << a.x << "," << a.y << "," << a.z << "), "
       << "b(" << b.x << "," << b.y << "," << b.z << "), "
       << "c(" << c.x << "," << c.y << "," << c.z << ")" << endl
       << "Volume: " << parallelepipedVolume(a, b, c) << endl
       << "Area (a and b): " << parallelogramArea(a, b) << endl
       << "Area (b and c): " << parallelogramArea(b, c) << endl
       << "Area (a and c): " << parallelogramArea(a, c) << endl
       << "Angle (a and b): " << angleBetweenTwoVectors(a, b) << endl
       << "Angle (b and c): " << angleBetweenTwoVectors(b, c) << endl
       << "Angle (a and c): " << angleBetweenTwoVectors(a, c) << endl;

  return 0;
}
