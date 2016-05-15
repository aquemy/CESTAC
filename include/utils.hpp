#ifndef CEST_UTILS_H
#define CEST_UTILS_H

#include <iterator>
#include <algorithm>
#include <numeric>

namespace std {

template <class T, std::size_t N>
constexpr std::size_t size(const T (&array)[N]) noexcept
{
    return N;
}

template <class T>
constexpr std::size_t size(const T &t) noexcept
{
    return t.size();
}

} // namespace std

namespace cestac {

template <class T>
double average(const T &v) {
    double sum = std::accumulate(std::begin(v), std::end(v), 0.0);
    return sum / std::size(v);
}

template <class T>
double stddev(const T &v, double m) {
    double accum = 0.0;
    std::for_each (std::begin(v), std::end(v), [&](const double d) {
        accum += (d - m) * (d - m);
    });
    return sqrt(accum / (std::size(v)-1));
}

double cs(double r, double s);

#ifdef DEBUG
union number {
    double d;
    uint64_t i;
};

void display(double d);
void display(union number n);
#endif

} // namespace cestac

#endif
