#include <iostream>
int func (double x, double y, double a, double b, double r)
{
   if((x-a)*(x-a)+(y-b)*(y-b) <= r*r){
       std::cout << "Лежит в круге" << std::endl;
   }
   else{
       std::cout << "Не лежит в круге" << std::endl;
   }
}

int main()
{
    double x = 0;
    double y = 0;
    double a = 0;
    double b = 0;
    double r = 0;
    std::cin >> x;
    std::cin >> y;
    std::cin >> a;
    std::cin >> b;
    std::cin >> r;
    func (x, y, a, b, r);
    return 0;
}
