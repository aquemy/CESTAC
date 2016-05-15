#ifndef CEST_DOUBLE_H
#define CEST_DOUBLE_H

#include <array>
#include <cstddef>
#include <ostream>
#include <pert.hpp>
#include <utils.hpp>

#ifndef SAMPLE_SIZE
    #define SAMPLE_SIZE 3
#endif

namespace cestac {

template <std::size_t N = SAMPLE_SIZE>
class Double {
public:
    Double() = default;

    Double(const double &x);
    Double(double &&x);
    Double(const Double<N>& x);
    Double(Double<N>&& x);

    Double<N>& operator=(const Double<N>& x);

    virtual ~Double() {}

    template <std::size_t T>
    friend std::ostream& operator<<(std::ostream&, const Double<T>&);

    template <std::size_t T>
    friend Double<T> operator+(const Double<T> &a, const Double<T> &b);

    template <std::size_t T>
    friend Double<T> operator+(Double<T> &a, double);

    template <std::size_t T>
    friend Double<T> operator-(Double<T> &a, double);

    template <std::size_t T>
    friend Double<T> operator-(const Double<T> &a, const Double<T> &b);

    template <std::size_t T>
    friend Double<T> operator*(const Double<T> &a, const Double<T> &b);

    double significant();
    void pert();

protected:

    double _significant;
    std::array<double, N> v;
    double a;
    double s;
};


template <std::size_t N>
Double<N>::Double(const double &x) {
    for(unsigned i = 0; i < N; ++i)
        v[i] = x;
    pert();
}

template <std::size_t N>
Double<N>::Double(double &&x) {
    for(unsigned i = 0; i < N; ++i)
        v[i] = x;
    pert();
}

template <std::size_t N>
Double<N>::Double(const Double<N>& x) {
    v = x.v;
    a = x.a;
    s = x.s;
    _significant = x._significant;
};

template <std::size_t N>
Double<N>::Double(Double<N>&& x) {
    v = std::move(x.v);
};

template <std::size_t N>
Double<N>& Double<N>::operator=(const Double<N>& x) {
    v = x.v;
    a = x.a;
    s = x.s;
    _significant = x._significant;
    return *this;
}

template <std::size_t N>
double Double<N>::significant() {
    a = average(v);
    s = stddev(v, a);
    _significant = cs(a, s);
    return _significant;
}

template <std::size_t N>
void Double<N>::pert() {
    for(auto& i : v)
        i = cestac::pert(i);
}


template <std::size_t N>
Double<N> operator+(const Double<N> &a, const Double<N> &b) {
    Double<N> c(a);
    for(unsigned i = 0; i < N; ++i)
        c.v[i] += b.v[i];
    c.pert();
    return c;
}

template <std::size_t N>
Double<N> operator+(Double<N> &a, double b) {
    Double<N> c(a);
    for(unsigned i = 0; i < N; ++i)
        c.v[i] += b;
    c.pert();
    return c;
}

template <std::size_t N>
Double<N> operator+(double b, const Double<N> &a) {
    return a + b;
}

template <std::size_t N>
Double<N> operator-(const Double<N> &a, const Double<N> &b) {
    Double<N> c(a);
    for(unsigned i = 0; i < N; ++i)
        c.v[i] -= b.v[i];
    c.pert();
    return c;
}

template <std::size_t N>
Double<N> operator-(Double<N> &a, double b) {
    for(auto& i: a.v)
        i -= b;
    a.pert();
    return a;
}

template <std::size_t N>
Double<N> operator-(double b, const Double<N> &a) {
    Double<N> c(b);
    for(unsigned i = 0; i < N; ++i)
        c.v[i] = b - a.v[i];
    c.pert();
    return c;
}

template <std::size_t N>
Double<N> operator*(const Double<N> &a, const Double<N> &b) {
    Double<N> c(a);
    for(unsigned i = 0; i < N; ++i)
        c.v[i] *= b.v[i];
    c.pert();
    return c;
}

template <std::size_t N>
Double<N> operator*(const Double<N> &a, double b) {
    for(auto& i: a)
        i *= b;
    a.pert();
    return a;
}

template <std::size_t N>
Double<N> operator*(double b, const Double<N> &a) {
    return a * b;
}

template <std::size_t N>
std::ostream& operator<<(std::ostream& os, const Double<N>& x)
{
    os << x.a << " (" << x._significant << ")";
    #ifdef DEBUG
    std::cout << std::endl;
    for(unsigned i = 0; i < N; ++i) {
        std::cout << "x[" << i << "] = " << std::setprecision(56) << x.v[i] << " - ";
        display(x.v[i]);
    }
    #endif
    return os;
}

} // namespace cestac

#endif
