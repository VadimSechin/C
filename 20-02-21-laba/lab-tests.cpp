#include <iostream>
#include <cmath>
#include <random>

// узкие моменты

int rndint(int min, int max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}


void Check(int width, int height, int &num, int x_coord[], int y_coord[], int x_mem[], int y_mem[], bool stopped[]) {
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
            std::cout << visual[i * width + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

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

        for (int i = 0; i < width * height; i++) {visual[i] = 1;}
        for (int i = 0; i < num; i++) {
            visual[y_coord[i] * width + x_coord[i]] = 0;
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                std::cout << visual[i * width + j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    return time;
}


int main() {
    int num = 3, width = 5, height = 5, time_sum = 0, accuracy = 1;
    int x_coord[3] = {0, 1, 2};
    int y_coord[3] = {0, 1, 2};

//    create_coords(num, width, height, x_coord, y_coord);
    std::cout << model(width, height, num, x_coord, y_coord);
    return 0;
}
