#include <iostream>
#include <cmath>
#include <random>

// третий вопрос с одномерным случаем часть 2
int rndint(int min, int max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

void Check(int width, int height, int &num, int x_coord[], int y_coord[], int x_mem[], int y_mem[], bool stopped[]) {
    for (int i = 0; i < num; i++) {
        for (int j = i + 1; j < num; j++) {
            if ((abs(x_coord[i] - x_coord[j])) <= 1) {
                if ((x_coord[i] == x_coord[j]) ) {
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


int model(int width, int height, int num, int x_coord[], int y_coord[]) {
    int time = 0, rnd_number;
    int x_mem[num];
    int y_mem[num];
    bool all_unmobile = true;
    bool stopped[num];
    for (int i = 0; i < num; i++) {stopped[i] = false;}
    int visual[width * height];
    for (int i = 0; i < width * height; i++) {visual[i] = 1;}

    for (int i = 0; i < num; i++) {
        visual[y_coord[i] * width + x_coord[i]] = 0;
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            //std::cout << visual[i * width + j] << " ";
        }
        //std::cout << std::endl;
    }
    //std::cout << std::endl;

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
                rnd_number = rndint(1, 2);
                if (rnd_number == 1) { x_coord[i]++; }
                if (rnd_number == 2) { x_coord[i]--; }
            }
        }
        Check(width, height, num, x_coord, y_coord, x_mem, y_mem, stopped);
        all_unmobile = true;
        for (int i = 0; i < num; i++) {
            if (not stopped[i]) {all_unmobile = false;}
        }

        for (int i = 0; i < width * height; i++) {visual[i] = 1;}
        for (int i = 0; i < num; i++) {
            visual[y_coord[i] * width + x_coord[i]] = 0;
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                //std::cout << visual[i * width + j] << " ";
            }
            //std::cout << std::endl;
        }
        //std::cout << std::endl;
    }
    return time;
}

void show(){
    int num = 1, time_sum = 0, accuracy = 100;

    int demention_begin = 10;
    int demention_step = 2;
    int steps = 5;
    int dots_max = 6;

    int x_coord[dots_max];
    int y_coord[dots_max];

    for(int k = demention_begin; k < demention_begin + demention_step*steps ; k += demention_step){
        for(int i = 1; i <= dots_max; i += 1){
            num = i;
            time_sum = 0;
            for(int j = 0; j < accuracy; j++) {
                create_coords(num, k, 1, x_coord, y_coord);
                time_sum += model(k, 1, num, x_coord, y_coord);
                }
            std::cout << (float)time_sum / (float)accuracy << ',' << ' ';
            }
        std::cout << std::endl;
        std::cout << std::endl;
    }

//    for (int i = 5; i <= 5; i += 2) {
//        for (int j = 0; j < accuracy; j++) {
//            x_coord[0] = i / 2;
//            y_coord[0] = i / 2;
//            time_sum += model(i, i, num, x_coord, y_coord);
//        }
//        std::cout << "aboba" << (float)time_sum / (float)accuracy << ' ';
//        time_sum = 0;
//        std::cout << std::endl;
//    }
}

int main() {
    show();
    return 0;
}
