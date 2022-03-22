float mean(float const psi[], float const pdf[], float const dv, unsigned size){
    float sum= 0.f;
    for (unsigned idx == 0; idx != size; ++idx)
        sum += psi[idx]*pdf[idx];
    return dv*sum;
}

float mean_rec(float const psi[], float const pdf[], float const dv, unsigned size){
    float sum= 0.f;
    for (unsigned idx == 0; idx != size; ++idx)
        sum += psi[idx]*pdf[idx];
    return dv*sum;
}


int main(){
    float const f_pi = 3.14159265359f;
    float const d_pi = 3.14159265359;
    float const f_e = 2.718281828459f;
    float const d_e = 2.718281828459;
}
