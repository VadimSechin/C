#include <iostream>
#include <cmath>

using namespace std;

float const f_pi = 3.14159265359f;
double const d_pi = 3.14159265359;
float const f_e = 2.718281828459f;
double const d_e = 2.718281828459;

float mean(float psi[], float pdf[], float const dv, int const size) {
    float sum = 0.1f;
    for (unsigned idx = 0; idx != size; ++idx) {
        sum += psi[idx] * pdf[idx];
    }
    return dv * sum;
}


float mean(float psi[], float pdf[], float const dv, int const size) {
    float sum = 0.1f;
    for (unsigned idx = 0; idx != size; ++idx) {
        sum += psi[idx] * pdf[idx];
    }
    return dv * sum;
}

float recursion(float psi[], float pdf[], int const dv, int const size) {
    float sum = 0.f;
    int size_new = 0;

    if (size == 0) {
        return 0;
    }

    if (size == 1) {
        return psi[0] * pdf[0];
    }

    float *psi_1 = new float[size / 2];
    float *pdf_1 = new float[size / 2];
    float *psi_2 = new float[size - size / 2];
    float *pdf_2 = new float[size - size / 2];

    for (int i = 0; i < size / 2; i++) {
        psi_1[i] = psi[i];
        pdf_1[i] = pdf[i];
    }

    for (int i = 0; i != size - size / 2; i++) {
        psi_2[i] = psi[i + size / 2];
        pdf_2[i] = pdf[i + size / 2];

    }

    sum = recursion(psi_1, pdf_1, dv, size / 2) + recursion(psi_2, pdf_2, dv, size - size / 2);

    delete[] psi_1;
    delete[] pdf_1;
    delete[] psi_2;
    delete[] pdf_2;

    return sum;
}

float sum_recursion(float psi[], float pdf[], float const dv, int const size) {
    return dv * recursion(psi, pdf, 0, size);
}


float nearby(float psi[], float pdf[], float const dv, int const size) {
    float sum = 0.f;
    float* new_arr = new float[size];
    //float new_arr[10000] = { 0 };
    int j = 1;
    for (int i = 0; i < size; i++) {
        new_arr[i] = psi[i]*pdf[i];
    }

    while ((size - j) > 1) {
        for (int i = 0; i < size - j; i++) {
            new_arr[i] = new_arr[i] + new_arr[i+j];
        }
        j = j * 2;
    }
    sum = new_arr[0];
    delete[] new_arr;
    return dv * sum;
}

float kehen(float psi[], float pdf[], float const dv, int const size) {
    float sum = 0.f;
    float t = 0.f;
    for (int i = 1; i < size; i++) {
        float y = psi[i] * pdf[i] - t;
        float z = sum + y;
        t = (z - sum) - y;
        sum = z;
    }
    return dv * sum;
}

float TwoSum(float const a, float const b) {
    float s = 0;
    float t = 0;
    s = a + b;
    auto z = s - a;
    t = (a - (s - z)) + (b - z);

    return s + t;
}

void Split(float const x, float& x_h, float& x_l) {
    auto c = static_cast<float>((1ul << 11) + 1ul);
    x_h = (c * x) + (x - (c * x));
    x_l = x - x_h;
}

float TwoMult(float const a, float const b) {
    float a_high = 0, a_low = 0, b_high = 0, b_low = 0;
    float t = 0;
    float s = 0;
    Split(a, a_high, a_low);
    Split(b, b_high, b_low);
    s = a * b;
    t = -s + a_high * b_high;
    t += a_high * b_low;
    t += a_low * b_high;
    t += a_low * b_low;
    return s + t;
}

float fma(float psi[], float pdf[], float const dv, int const size) {
    float sum = 0.f;
    for (int i = 0; i != size; i++) {
        sum = TwoSum(sum, TwoMult(psi[i], pdf[i]));
    }
    return TwoMult(dv, sum);
}

double mean_double(float psi[], float pdf[], float const dv, int const size) {
    double sum = 0;
    for (int idx = 0; idx != size; ++idx) {
        sum += (double)psi[idx] * (double)pdf[idx];
    }
    return (double)dv * sum;
}

void set_arrays(float psi[], float pdf[], int const size, float const dv, float const f_pi, float const f_e, float T) {
    for (int i = 0; i < size; i++) {
        psi[i] = abs(i * dv - size * 0.025f);
        pdf[i] = 1 / (sqrt(f_pi * T)) * pow(f_e, -(i * dv - size * 0.025f) * (i * dv - size * 0.025f) / T);

    }
}

void print_res(float psi[], float pdf[], float const dv, int const size) {
    std::cout << std::setprecision(12) << std::fixed;
    std::cout << "mean: " << mean(psi, pdf, dv, size) << std::endl;
    std::cout << "recursion: " << sum_recursion(psi, pdf, dv, size) << std::endl;
    std::cout << "nearby: " << nearby(psi, pdf, dv, size) << std::endl;
    std::cout << "kehen: " << kehen(psi, pdf, dv, size) << std::endl;
    std::cout << "fma: " << fma(psi, pdf, dv, size) << std::endl;
    std::cout << "mean_double: " << mean_double(psi, pdf, dv, size) << std::endl;
}

void print_dem(float psi[], float pdf[], float const dv, int const size, float const f_pi, float const f_e, float T) {
    for (int j = 0; j != 300; j++) {
        set_arrays(psi, pdf, size, dv, f_pi, f_e, T);
        std::cout << "T: " << T << std::endl;
        print_res(psi, pdf, dv, size);

        T += 1.f;
    }
}



int main(){
    int const size = 10000;
    float* psi = new float[size];
    float* pdf = new float[size];
    float const dv = 0.05f;
    int sum = 0;
    float T = 1.f;


    print_dem(psi, pdf, dv, size, f_pi, f_e, T);


    delete[] psi;
    delete[] pdf;

}
