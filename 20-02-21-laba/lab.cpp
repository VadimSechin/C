#include <iostream>
#include <cmath>
#include <random>

int rndint(int min, int max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

int model_1(int width, int height, int num, int x_coord[], int y_coord[]) {
    int time = 0, rnd_number;
    bool stopped[num] = {false};
    bool all_unmobile = true;
    for (int i = 0; i < num; i++) {
        if ((x_coord[i] == 0) or (y_coord[i] == 0) or (x_coord[i] == width) or (y_coord[i] == height)) {
            stopped[i] = true;
        } else all_unmobile = false;
    }

    while (not all_unmobile) {
        all_unmobile = true;
        time++;
        for (int i = 0; i < num; i++) {
            if (not stopped[i]) {
                rnd_number = rndint(1, 4);
                if (rnd_number == 1) { x_coord[i]++; }
                if (rnd_number == 2) { y_coord[i]++; }
                if (rnd_number == 3) { x_coord[i]--; }
                if (rnd_number == 4) { y_coord[i]--; }
                if ((x_coord[i] == 0) or (y_coord[i] == 0) or (x_coord[i] == width) or (y_coord[i] == height)) {
                    stopped[i] = true;
                } else all_unmobile = false;
            }
        }
    }
    return time;
}


void show_1(){

    int num = 1, time_sum = 0, accuracy = 1000;
    int x_coord[num];
    int y_coord[num];
    for (int i = 0; i <= 10; i += 2) {
        for (int k = 0; k < 5; k++) {
            for (int j = 0; j < accuracy; j++) {
                x_coord[0] = i / 2;
                y_coord[0] = i / 2;
                time_sum += model_1(i, i, num, x_coord, y_coord);
            }
            std::cout << (float)time_sum / (float)accuracy << ' ';
            time_sum = 0;
        }
        std::cout << std::endl;
    }
}

//
void create_coords(int n , int s){

    int x_coord[n];
    int y_coord[n];
    int a;
    int b;
    bool f;


    for (int i = 0; i <= n-1; i += 1) {

        bool F = true;

        while(F){

            f = false;
            a = rndint(0, s-1);
            b = rndint(0, s-1);

            for (int ii = 0; ii <= n-1; ii +=1){
                if ((x_coord[ii] == a) and (y_coord[ii] == b)){
                f = true;
                }
                if(f){
                    F = true;
                }
                else{
                    F = false;
                }
            }
        }


        x_coord[i] = a;
        y_coord[i] = b;

     }


    for (int i = 0; i <= n-1; ++i){
        std::cout << x_coord[i] << ' ';
    }

    std::cout  << std::endl;

    for (int i = 0; i <= n-1; ++i){
        std::cout << y_coord[i] << ' ';
    }

    std::cout  << std::endl;


}
//

int main() {
    /*show_1();*/
    create_coords(4, 2);
    return 0;
}
