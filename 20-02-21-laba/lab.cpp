#include <iostream>
#include <cmath>
#include <random>


// первый вопрос

int rndint(int min, int max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

int model(int width, int height, int num, int x_coord[], int y_coord[]) {
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

void show(){
    int num = 1, time_sum = 0, accuracy = 100;
    int x_coord[num];
    int y_coord[num];
    for (int i = 1; i <= 45; i += 2) {
        for (int j = 0; j < accuracy; j++) {
            x_coord[0] = i / 2;
            y_coord[0] = i / 2;
            time_sum += model(i, i, num, x_coord, y_coord);
        }
        std::cout << (float)time_sum / (float)accuracy << ' ';
        time_sum = 0;
        std::cout << std::endl;
    }
}
int main() {
    show();
    return 0;
}
