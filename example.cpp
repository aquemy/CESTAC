#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <cfloat>

#include <pert.hpp>
#include <utils.hpp>
#include <double.hpp>

constexpr const size_t n = SAMPLE_SIZE;

int main() {
    // Exemple on POD double precision
     double ab=4095.1;
     double aa=ab+1;
     double ax=1;

    for (int i = 0; i < 5; ++i) {
        ax = (aa*ax) - ab;
        std::cout << "iteration " << i << " - " << std::setprecision(std::numeric_limits<double>::max_digits10) << ax << '\n';
     }

     // Example using CESTAC
     using namespace cestac;
     Double<n> b = 4095.1;
     Double<n> a =  b+1;
     Double<n> x = 1.;

     for (int i = 0; i < 10; ++i) {
          x = (a*x) - b;
          if(x.significant() < 1) {
                std::cout << "iteration " << i << " non significant result - exit" << '\n';
                break;
          }
          std::cout << "iteration " << i << " - " << std::setprecision(15) << x << '\n';
     }

    return 0;
}
