#include <iostream>
int func (int a, int b)
{
    int err = 0;
    while (b != 0)
    {
        if (a > b)  {
            err = err + 1;
        }
        a = b;
        std::cin >> b;
    }
    std::cout << "Количество пар не по росту:" << std::endl;
    std::cout << err;
}
int main()
{
    int a = 0;
    int b = 0;
    std::cin >> a;
    std::cin >> b;
    func(a, b);
    return 0;

}
