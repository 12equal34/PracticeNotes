#include <iostream>

using namespace std;
int main()
{

    int a = 123;
    int b = -123;

    cout << true << '\n';
    cout << a << '\n';
    cout << b << '\n';
    cout << (size_t)a << '\n';
    cout << (size_t)b << '\n';
    cout << (size_t)a + (size_t)b << '\n';

    return 0;
}