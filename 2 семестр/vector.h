#include <math.h>

struct Vector {
  double x, y, z;

  Vector(double x, double y, double z): x(x), y(y), z(z) {} 
};

double parallelepipedVolume(Vector a, Vector b, Vector c);
double parallelogramArea(Vector a, Vector b);
double angleBetweenTwoVectors(Vector a, Vector b);
double vectorModule(Vector vector);
double scalarProductOfTwoVectors(Vector a, Vector b);
double matrixDeterminant(Vector a, Vector b, Vector c);
double crossProduct(Vector a, Vector b);
Vector crossProductCoordinates(Vector a, Vector b);

double parallelepipedVolume(Vector a, Vector b, Vector c) {
  return abs(matrixDeterminant(a, b, c));
}

double parallelogramArea(Vector a, Vector b) {
  return vectorModule(crossProductCoordinates(a, b));
}

double angleBetweenTwoVectors(Vector a, Vector b) {
  return scalarProductOfTwoVectors(a, b) / (vectorModule(a) * vectorModule(b));
}

double vectorModule(Vector vector) {
  return sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
}

double scalarProductOfTwoVectors(Vector a, Vector b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

double matrixDeterminant(Vector a, Vector b, Vector c) {
  return a.x * b.y * c.z + a.y * b.z * c.x + a.z * b.x * c.y - a.z * b.y * c.x - a.x * b.z * c.y - a.y * b.x * c.z;
}

double crossProduct(Vector a, Vector b) {
  return (a.y * b.z - a.z * b.y) + (-1) * (a.x * b.z - a.z * b.x) + (a.x * b.y - a.y * b.x);
}

Vector crossProductCoordinates(Vector a, Vector b) {
  return {a.y * b.z - a.z * b.y, -1 * (a.x * b.z - a.z * b.x), a.x * b.y - a.y * b.x};
}
