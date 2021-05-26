#include <iostream>
#include <math.h>

using namespace std;

double mixed(double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz){
  return (ax*by*cz)+(ay*bz*cx)+(az*bx*cy)-(az*by*cx)-(ay*bx*cz)-(ax*bz*cy);   // Формула смешаного произведения, если = 0, то одна плоскость
}
 
bool collinear(double ax, double bx, double ay, double by, double az, double bz){
  return ((ax/bx) == (ay/by) && (ay/by) == (az/bz)) ? true:false;   // Коллинеарность
}
 
bool equation(double x, double x0, double y, double y0, double z, double z0, double Vx, double Vy, double Vz){
  return  (x - x0)/Vx == (y - y0)/Vy && (y - y0)/Vy == (z - z0)/Vz ? true:false;   // уравнение прямой в пространстве 
}
 
double min(double X1, double X2){
  return X1 < X2 ? X1:X2;
}
double max(double X1, double X2){
  return X1 > X2 ? X1:X2;
}
bool CollinearforPerp(double ax, double ay, double az, double bx, double by, double bz){    // Условие коллинеарности при bx,by,bz=0
  return ((ay*bz-az*by == 0) && (az*bx-ax*by == 0) && (ax*by-ay*bx == 0)) ? true:false;
}
