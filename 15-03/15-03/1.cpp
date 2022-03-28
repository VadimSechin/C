#include <iostream>
#include <cmath>
#include <typeinfo>


float const f_pi = 3.14159265359f;
double const d_pi = 3.14159265359;
float const f_e = 2.718281828459f;
double const d_e = 2.718281828459;

float maxwell(float v, float T)
{
    return powf(f_e, -v * v / T) / sqrt(T * f_pi);
}

float my_fill(float v[], float f[], float T, float v1, float v2, unsigned long n)
{
    float dv = (v2 - v1) / n;
    for (unsigned long i = 0; i < n; i++){
        v[i] = abs(v1 + dv * i);
        f[i] = maxwell(v[i], T);
    }
return dv;
}


float mean_naive(float const v[], float const f[], float const dv, unsigned long n) {
    float sum = 0.f;
    for (unsigned long i = 0; i < n; i++)
        sum += v[i] * f[i];
    return sum * dv;
}

float sum_divide(float const v[], float const f[], unsigned long n) {
    float sum = 0.f;
    if (n > 1){
        sum += sum_divide(v, f, n / 2);
        sum += sum_divide(v + n / 2, f + n / 2, n - n / 2);
    }
    else sum = v[0] * f[0];
    return sum;
}

float mean_divide(float const v[], float const f[], float const dv, unsigned long n) {
    return sum_divide(v, f, n) * dv;
}

float mean_fma(float const v[], float const f[], float const dv, unsigned long n) {
    float sum = 0.f;
    for (unsigned long i = 0; i < n; i++)
        sum = fmaf(v[i], f[i], sum);
    return sum * dv;
}

long double mean_double(float const v[], float const f[], float const dv, unsigned long n) {
    long double sum = 0;
    for (unsigned long i = 0; i < n; i++)
        sum += (long double)v[i] * (long double)f[i];
    return sum * (long double) dv;
}

float mean_non_rec(float const v[], float const f[], float const dv, unsigned long n) {

    float *x = new float[n];
    for (size_t i = 0; i < n; i++)
        x[i] = v[i] * f[i];
    for (size_t step = 1; step < n; step *= 2)
        for (unsigned long i = 0; i + step < n; i += 2 * step)
            x[i] += x[i + step];
    return x[0] * dv;
}

float mean_kehen(float const v[], float const f[], float const dv, unsigned long n) {
    float sum = 0.f;
    float t = 0.f;
    for (unsigned long i = 0; i < n; i++) {
        float y = v[i] * f[i] - t;
        float z = sum + y;
        t = (z - sum) - y;
        sum = z;
    }
    return sum * dv;
}

void test(float const T, size_t N, float const v1, float const v2) {
    float* v = new float[N];
    float* f = new float[N];
    float dv = my_fill(v, f, T, v1, v2, N);

    std::cout<< "N = "<< N<< std::endl << "T = " << T << std::endl;
    std::cout << "------\n";
    std::cout.precision(8);
    std::cout << "Real mean: " << sqrt(T / f_pi) << std::endl;
    std::cout << "0. Naive mean: " << mean_naive(v, f, dv, N) << std::endl;
    std::cout << "1. Recursive split: " << mean_divide(v, f, dv, N) << std::endl;
    std::cout << "2. Non recursive: " << mean_non_rec(v, f, dv, N) << std::endl;
    std::cout << "3. Kahan summation: " << mean_kehen(v, f, dv, N) << std::endl;
    std::cout << "4. Fuse-Multiply-Add: " << mean_fma(v, f, dv, N) << std::endl;
    std::cout << "5. Double: " << mean_double(v, f, dv, N) << std::endl;
    delete v;
    delete f;
}

int main() {
test(1.f, 20000, -30.f, 30.f);
return 0;
}
