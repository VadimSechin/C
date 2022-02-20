#include <iostream>
int func (int n, int a)
{
    int mm = 0;
    int m = 0;
    int MM = 0;
    int M = 0;
    mm = a;
    m = a + 1;
    MM = a;
    M = a - 1 ;
    n = n - 1;
    while (n != 0)
    {
        std::cin >> a;
        if (a < m)  {
            if (a < mm)  {
            m = mm;
            mm = a;
            }
            if (a > mm)  {
            m = a;
            }
        }
        if (a > M)  {
            if (a > MM)  {
            M = MM;
            MM = a;
            }
            if (a < MM)  {
            M = a;
            }
        }
        n = n -1;
    }
    std::cout << "Cумма двух минимумов:" << std::endl;
    std::cout << mm + m << std::endl;
    std::cout << "Сумма двух максимуморв:" << std::endl;
    std::cout << MM + M << std::endl;
}

int main()
{
    int n = 0;
    int a = 0;
    std::cin >> n;
    std::cin >> a;
    func (n, a);
    return 0;
}
