#include <iostream>
#include <cmath>
#include <random>


const int ACCURACY1 = 100;
const int ACCURACY2 = 100;
const int ACCURACY3 = 100;
const int ACCURACY4 = 10;
const int MAX_DIM = 45;


const int DEM_BEGIN = 5;
const int DEM_STEP = 2;
const int STEPS = 5;
const int MAX_DOTS = 20;


int rndint(int min, int max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}


void Check(int width, int height, int num, int x_coord[], int y_coord[], int x_mem[], int y_mem[], bool stopped[]) {
    for (int i = 0; i < num; i++) {
        for (int j = i + 1; j < num; j++) {
            if ((abs(x_coord[i] - x_coord[j]) + abs(y_coord[i] - y_coord[j]) <= 1)) {
                if ((x_coord[i] == x_coord[j]) and (y_coord[i] == y_coord[j])) {
                    x_coord[j] = x_mem[j];
                    y_coord[j] = y_mem[j];
                }
                stopped[i] = true;
                stopped[j] = true;
            }
        }
        if ((x_coord[i] == 0) or (x_coord[i] == width - 1) or (y_coord[i] == 0) or (y_coord[i] == height - 1)) {
            stopped[i] = true;
        }
    }
}

void Check_one_dim(int width, int height, int num, int x_coord[], int x_mem[], bool stopped[]) {
    for (int i = 0; i < num; i++) {
        for (int j = i + 1; j < num; j++) {
            if (abs(x_coord[i] - x_coord[j]) <= 1) {
                if (x_coord[i] == x_coord[j]) {
                    x_coord[j] = x_mem[j];
                }
                stopped[i] = true;
                stopped[j] = true;
            }
        }
        if ((x_coord[i] == 0) or (x_coord[i] == width - 1)) {
            stopped[i] = true;
        }
    }
}

void Check_tor(int width, int height, int num, int x_coord[], int y_coord[], int x_mem[], int y_mem[], bool stopped[]) {

    for (int i = 0; i < num; i++) {

        if(x_coord[i] == -1){
            x_coord[i] = height-1;
        }
        else if(x_coord[i] == height){
            x_coord[i] = 0;
        }
        else if(y_coord[i] == -1){
            y_coord[i] = width-1;
        }
        else if(y_coord[i] == width){
            y_coord[i] = 0;
        }
    }

    for (int i = 0; i < num; i++) {
        for (int j = i + 1; j < num; j++) {
            if ((abs(x_coord[i] - x_coord[j]) + abs(y_coord[i] - y_coord[j]) <= 1)) {
                if ((x_coord[i] == x_coord[j]) and (y_coord[i] == y_coord[j])) {
                    x_coord[j] = x_mem[j];
                    y_coord[j] = y_mem[j];
                }
                stopped[i] = true;
                stopped[j] = true;
            }
        }
    }

}

void create_coords(int num, int width, int height, int x_coord[], int y_coord[]){
    int x_rand;
    int y_rand;
    bool F, f;

    for (int i = 0; i <= num - 1; i += 1) {
        F = true;
        while(F){
            f = false;
            x_rand = rndint(0, width - 1);
            y_rand = rndint(0, height - 1);
            for (int j = 0; j <= num - 1; j +=1){
                if ((x_coord[j] == x_rand) and (y_coord[j] == y_rand)){
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
        x_coord[i] = x_rand;
        y_coord[i] = y_rand;
    }
}

int model_simple(int width, int height, int num, int x_coord[], int y_coord[]) {
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
                if ((x_coord[i] == 0) or (y_coord[i] == 0) or (x_coord[i] == width - 1) or (y_coord[i] == height - 1)) {
                    stopped[i] = true;
                } else all_unmobile = false;
            }
        }
    }
    return time;
}

int model_advanced(int width, int height, int num, int x_coord[], int y_coord[]) {
    int time = 0, rnd_number;
    int x_mem[num];
    int y_mem[num];
    bool all_unmobile = true;
    bool stopped[num];
    for (int i = 0; i < num; i++) {stopped[i] = false;}

    Check(width, height, num, x_coord, y_coord, x_mem, y_mem, stopped);
    all_unmobile = true;
    for (int i = 0; i < num; i++) {
        if (not stopped[i]) {all_unmobile = false;}
    }

    while (not all_unmobile) {
        time++;
        for (int i = 0; i < num; i++) {
            x_mem[i] = x_coord[i];
            y_mem[i] = y_coord[i];
        }
        for (int i = 0; i < num; i++) {
            if (not stopped[i]) {
                rnd_number = rndint(1, 4);
                if (rnd_number == 1) { x_coord[i]++; }
                if (rnd_number == 2) { y_coord[i]++; }
                if (rnd_number == 3) { x_coord[i]--; }
                if (rnd_number == 4) { y_coord[i]--; }
            }
        }
        Check(width, height, num, x_coord, y_coord, x_mem, y_mem, stopped);
        all_unmobile = true;
        for (int i = 0; i < num; i++) {
            if (not stopped[i]) {all_unmobile = false;}
        }
    }
    return time;
}

int model_one_dim_simple(int width, int height, int num, int x_coord[]) {

    int time = 0, rnd_number;
    bool stopped[num] = {false};
    bool all_unmobile = true;
    for (int i = 0; i < num; i++) {
        if ((x_coord[i] == 0) or (x_coord[i] == width) ) {
            stopped[i] = true;
        } else all_unmobile = false;
    }
    while (not all_unmobile) {
        all_unmobile = true;
        time++;
        for (int i = 0; i < num; i++) {
            if (not stopped[i]) {
                rnd_number = rndint(1, 2);
                if (rnd_number == 1) { x_coord[i]++; }
                if (rnd_number == 2) { x_coord[i]--; }
                if ((x_coord[i] == 0)  or (x_coord[i] == width - 1)) {
                    stopped[i] = true;
                } else all_unmobile = false;
            }
        }
    }
    return time;
}

int model_one_dim_advanced(int width, int height, int num, int x_coord[]) {
    int time = 0, rnd_number;
    int x_mem[num];
    bool all_stopped = true;
    bool stopped[num];
    for (int i = 0; i < num; i++) {stopped[i] = false;}

    Check_one_dim(width, height, num, x_coord, x_mem, stopped);
    all_stopped = true;
    for (int i = 0; i < num; i++) {
        if (not stopped[i]) {
            all_stopped = false;
        }
    }

    while (not all_stopped) {
        time++;
        for (int i = 0; i < num; i++) {
            x_mem[i] = x_coord[i];
        }
        for (int i = 0; i < num; i++) {
            if (not stopped[i]) {
                rnd_number = rndint(0,1);
                if (rnd_number == 0) { x_coord[i]++; }
                if (rnd_number == 1) { x_coord[i]--; }
            }
        }
        Check_one_dim(width, height, num, x_coord, x_mem, stopped);
        all_stopped = true;
        for (int i = 0; i < num; i++) {
            if (not stopped[i]) {
                all_stopped = false;
            }
        }
    }
    return time;
}

int model_tor(int width, int height, int num, int x_coord[], int y_coord[]){
    int time = 0, rnd_number;
    int x_mem[num];
    int y_mem[num];
    bool all_unmobile = true;
    bool stopped[num];
    for (int i = 0; i < num; i++) {stopped[i] = false;}

    Check_tor(width, height, num, x_coord, y_coord, x_mem, y_mem, stopped);
    all_unmobile = true;
    for (int i = 0; i < num; i++) {
        if (not stopped[i]) {all_unmobile = false;}
    }

    while (not all_unmobile) {
        time++;
        for (int i = 0; i < num; i++) {
            x_mem[i] = x_coord[i];
            y_mem[i] = y_coord[i];
        }
        for (int i = 0; i < num; i++) {
            if (not stopped[i]) {
                rnd_number = rndint(1, 4);
                if (rnd_number == 1) { x_coord[i]++; }
                if (rnd_number == 2) { y_coord[i]++; }
                if (rnd_number == 3) { x_coord[i]--; }
                if (rnd_number == 4) { y_coord[i]--; }
            }
        }
        Check_tor(width, height, num, x_coord, y_coord, x_mem, y_mem, stopped);
        all_unmobile = true;
        for (int i = 0; i < num; i++) {
            if (not stopped[i]) {all_unmobile = false;}
        }
    }
    return time;
}


void show1(){
    int time_sum = 0;
    int x_coord[1];
    int y_coord[1];
    for (int i = 1; i <= MAX_DIM; i += 2) {
        for (int j = 0; j < ACCURACY1; j++) {
            x_coord[0] = i / 2;
            y_coord[0] = i / 2;
            time_sum += model_simple(i, i, 1, x_coord, y_coord);
        }
        std::cout << time_sum*1.0/ACCURACY1 << "," << ' ';
        time_sum = 0;
    }
}

void show2(){
    int time_sum = 0;
    int x_coord[MAX_DOTS];
    int y_coord[MAX_DOTS];

    for(int k = DEM_BEGIN; k < DEM_BEGIN + DEM_STEP*STEPS ; k += DEM_STEP){
        for(int i = 1; i <= MAX_DOTS; i += 1){
            time_sum = 0;
            for(int j = 0; j < ACCURACY2; j++) {
                create_coords(i, k, k, x_coord, y_coord);
                time_sum += model_advanced(k, k, i, x_coord, y_coord);
                }
            std::cout << time_sum*1.0/ACCURACY2 <<"," <<' ';
            }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}

void show3(){
    int time_sum = 0;
    int x_coord[1];
    for (int i = 1; i <= MAX_DIM; i += 2) {
        for (int j = 0; j < ACCURACY3; j++) {
            x_coord[0] = i / 2;
            time_sum += model_one_dim_simple(i, 1, 1, x_coord);
        }
        std::cout << time_sum*1.0/ACCURACY3 << "," << ' ';
        time_sum = 0;
    }
}

void show4(){
    int time_sum;
    int x_coord[MAX_DOTS];
    int y_coord[1];

    for(int k = DEM_BEGIN; k < DEM_BEGIN + DEM_STEP * STEPS ; k += DEM_STEP){
        for(int i = 1; i <= MAX_DOTS; i += 1){
            time_sum = 0;
            for(int j = 0; j < ACCURACY4; j++) {
                create_coords(i, MAX_DOTS, 1, x_coord, y_coord);
                time_sum += model_one_dim_advanced(MAX_DOTS, 1, i, x_coord);
            }
            std::cout << time_sum*1.0/ACCURACY4 << ',' << ' ';
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

}

void show_tor(){
    int time_sum = 0;
    int x_coord[MAX_DOTS];
    int y_coord[MAX_DOTS];

    for(int k = DEM_BEGIN; k < DEM_BEGIN + DEM_STEP*STEPS ; k += DEM_STEP){
        for(int i = 1; i <= MAX_DOTS; i += 1){
            time_sum = 0;
            for(int j = 0; j < ACCURACY2; j++) {
                create_coords(i, k, k, x_coord, y_coord);
                time_sum += model_advanced(k, k, i, x_coord, y_coord);
                }
            std::cout << time_sum*1.0/ACCURACY2 <<"," <<' ';
            }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}


int choose_work(){
    int n;
    std::cout << "1 - two-dim  1st task" ;
    std::cout << std::endl;
    std::cout << "2 - two-dim  2nd task";
    std::cout << std::endl;
    std::cout << "3 - one-dim  1st task";
    std::cout << std::endl;
    std::cout << "4 - one-dim  2nd task";
    std::cout << std::endl;
    std::cout << "5 - tor 2nd task";
    std::cout << std::endl;
    std::cout << "enter the number ";
    std::cin >> n;
    std::cout << std::endl;
    return n;
}

int main() {
    int n = choose_work();
    if(n==1){
    show1();
    }
    else if(n==2){
    show2();
    }
    else if(n==3){
    show3();
    }
    else if(n==4){
    show4();
    }
    else if(n==5){
    show_tor();
    }
    return 0;
}
