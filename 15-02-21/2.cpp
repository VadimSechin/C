#include <iostream>

int inp();
void cut (int a[], int n);
int make_num(int a[], int n);
void out(int m);


int main()
{
    int n;
    int m;
    int a[10];
    n = inp();
    cut(a, n);
    m = make_num(a, n);
    out(m);
    return 0;
}


int inp()
{
    int n;
    std::cin >> n;
    return n;

}


void cut (int a[], int n)
{
    int i;

    for (i = 0; i <= 9; i++){
        a[i] = 0;
    }

    while (n > 0){
        a[n % 10] = a[n % 10]+1;
        n /= 10;
    }
}


int make_num (int a[], int n)
{
    int m = 0;
    int i;

    for (i = 1; i <= 9; i++){
        if(a[i] != 0){
            m = m + i;
            a[i]--;
            break;
        }
    }

    for (i = 0; i <= 9; i++){
        while(a[i] != 0)
        {
            m = m*10 + i;
            a[i]--;
        }
    }

    return m;
}


void out (int m)
{
    std::cout<< m;
}


