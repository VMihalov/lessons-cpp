#include <iostream>

using namespace std;

int f(int n)
{
    if (n>100)
        return n-10;
    else 
        return f( f(n+11) );
}
 
int main() {
    //cout << "f(106) " << f(106) << endl;
    cout << "f(99) " << f(99) << endl;
    //cout << "f(85) " << f(85) << endl;

    return 0;
}