/*#include <iostream>
int func (int n)
{
   int q1 = 0;
   int q2 = 0;
   int q3 = 0;
   int q4 = 0;
   int a;
   int b;

   while (n !=0){
   std::cout<< "введите координатную пару:"<< std::endl;
   std::cin >> a;
   std::cin >> b;

   if(a>0){
       if(b>0){
       q1 = q1 + 1;
       }
       if(b<0){
       q4 = q4 +1;
       }
   }

   if(a<0){
       if(b>0){
       q2 = q2 +1;
       }
       if(b<0){
       q3 = q3 +1;
       }
   }
   n = n-1;
   }

   int M = q1;
   if(q2 > M){
       M = q2;
   }
   if(q3 > M){
       M = q3;
   }
   if(q4 > M){
       M = q4;
   }


   if (M == q1){
       std::cout<< "больше всего точек в 1 четверти"<< std::endl;
       std::cout<< "в 1 четверти  "<< q1 << " точек "<<  std::endl;
   }
   if (M == q2){
       std::cout<< "больше всего точек в 2 четверти"<< std::endl;
       std::cout<< "в 1 четверти  "<< q2 << "т очек "<<  std::endl;
   }
   if (M == q4){
       std::cout<< "больше всего точек в 3 четверти"<< std::endl;
       std::cout<< "в 1 четверти  "<< q3 << " точек "<<  std::endl;
   }
   if (M == q4){
       std::cout<< "больше всего точек в 4 четверти"<< std::endl;
       std::cout<< "в 1 четверти  "<< q4 << " точек "<<  std::endl;
   }

}

int main()
{
    int n = 0;
    std::cin >> n;
    func (n);
    return 0;
}*/
