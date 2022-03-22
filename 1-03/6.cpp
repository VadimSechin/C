/*#include <iostream>
using namespace std;

int male(int n);

int female(int n){
    if (n == 0)
        return 1;
    else
        return n - male(female(n - 1));
}

int male(int n) {
    if (n == 0)
        return 0;
    else
        return n - female(male(n - 1));
}

int main()
{
    int n;
    cin >> n;
    cout << female(n)<< endl;
    cout << male(n);
    return 0;
}*/
