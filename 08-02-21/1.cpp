#include <iostream>

int func (int n, int m)
{
    while (n != 0)
    {
        std::cin >> n;
        if (n % 2 ==0 && n > m)  {
            m = n;
        }
    }
    std::cout << "Наибольшее чётное число:" << std::endl;
    std::cout << m;
}

int main()
{
    int n = 1;
    int m = 0;
    func (n, m);
    return 0;
}






