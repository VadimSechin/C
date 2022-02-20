/*
int inp(int a[]);
void func (int a[], int b[], int n);
void out (int b[], int n);


int main()
{
    int n;
    int a[100];
    int b[100];

    n = inp(a);
    func(a, b, n);
    out(b, n);
    return 0;
}


int inp(int a[])
{
    int c;
    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> c;
        a[i] = c;
    }
    return n;
}


void func (int a[], int b[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        if (i == 0) {
            b[i] = (a[n-1]+a[0]+a[1])/3;
        } else if (i == n-1) {
            b[i] = (a[n-2]+a[n-1]+a[0])/3;
        } else {
            b[i] = (a[i-1]+a[i]+a[i+1])/3;
        }
    }
}


void out (int b[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        std::cout<< b[i] <<  " ";
    }
}
*/
