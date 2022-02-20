#include <iostream>
int func (double a1, double b1, double c1, double a2, double b2, double c2)
{
   if(b1*b2 == 0){
       std::cout << "Нет точек пересечения" << std::endl;
   }
   else{
       if(a1/b1 == a2/b2){
           std::cout << "Нет точек пересечения" << std::endl;
       }
       else{
           double x = 0;
           double y = 0;

           x = (-c1+b1/b2*c2)/(a1-b1/b2*a2);
           y = (-c2-a2*x)/b2;

           std::cout << "Точка пересечения:" << std::endl;
           std::cout << "x:" << x << "    "<< "y:" <<  y << std::endl;
       }
   }
}

int main()
{
    double a1 = 0;
    double b1 = 0;
    double c1 = 0;
    double a2 = 0;
    double b2 = 0;
    double c2 = 0;
    std::cin >> a1;
    std::cin >> b1;
    std::cin >> c1;
    std::cin >> a2;
    std::cin >> b2;
    std::cin >> c2;
    func (a1, b1, c1, a2, b2, c2);
    return 0;
}
