#include <iostream>

using namespace std;

int fib(int n)
{
    if (n <= 1) return n;
    else return fib(n-1) + fib(n-2);
}



int main () {
    int a[30];
    int cnt = 0;
    int x = -1;
    int y = 0;
    while (x != 0){
        cin >> x;
        a[cnt++] = x;
        y = fib(x);
        a[cnt++] = y;
        cout << "The fib of " << x << " is " << y << endl;
    }
    int i = 0;
    cnt--;
    while (cnt > i){
        cout << a[i++]<< " " << a[cnt--] << " ";
    }
}
