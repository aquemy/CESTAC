#include <cmath>
#include <random>
#include <stdint.h>

#include <pert.hpp>

double cestac::inc_float(double f) {
    return ++*(uint64_t*)&f, f;
}

double cestac::dec_float(double f) {
    return --*(uint64_t*)&f, f;
}

double cestac::next_float(double f) {
    return f == 0.0 ?  0x1p-1074 :
      isinf(f) || isnan(f) ?  f :
      (f > 0 ? inc_float : dec_float)(f);
}

double cestac::prev_float(double f){
    return -next_float(-f);
}

std::random_device rd;
std::mt19937 gen(rd());
std::bernoulli_distribution d(0.5);

double cestac::pert(const double& x) {
    if (d(gen))
        return x;
    else {
       if(d(gen))
         return next_float(x);
       else
         return prev_float(x);
    }
}
