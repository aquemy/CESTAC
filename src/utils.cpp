#include <iostream>
#include <utils.hpp>

double cestac::cs(double r, double s) {
    return std::log10(fabs(r) / s) - 0.396;
}

#ifdef DEBUG
void cestac::display(double d) {
    union number n;
    n.d = d;
    display(n);
}

void cestac::display(union number n) {
    int i;
    uint64_t base = 1;

    std::cout << (n.i & (base << 63)) << " ";
    for (i = 62; i > 51; --i) {
        std::cout << ((n.i & (base << i)) >> i);
    }

    std::cout << " ";
    for (; i >= 0; --i)
        std::cout << ((n.i & (base << i)) >> i);
    std::cout << std::endl;
}
#endif
