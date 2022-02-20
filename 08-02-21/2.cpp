#include <iostream>
int func (int n, int a)
{
    int m = 0;
    int r = 1;
    m = a;
    n = n - 1;
    while (n != 0)
    {
        std::cin >> a;
        if (a < m)  {
            m = a;
            r = 0;
        }
        if (a == m){
            r = r + 1;
        }
        n = n - 1;
    }
    std::cout << "Минимальное число:" << std::endl;
    std::cout << m << std::endl;
    std::cout << "Количество повторов минимального числа:" << std::endl;
    std::cout << r;
}

 int main()
{
    int n = 0;
    int a = 0;
    std::cin >> n;
    std::cin >> a;
    func(n, a);
    return 0;
}
