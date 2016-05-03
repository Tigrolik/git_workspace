#include "Floating.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <bitset>

// {*reinterpret_cast<const unsigned int*>(&f)}: "convert" float to bit values
Floating::Floating(const float f): f_{f} { }
    //bits_{get_bits(f)} { }
    //bits_{*reinterpret_cast<const unsigned int*>(&f)} { }

//Floating::Floating(const Floating &o): f_{o.value()}, bits_{o.bits()} { }
Floating::Floating(const Floating &o): f_{o.value()} { }

Floating &Floating::operator=(const Floating &o) {
    if (this == &o)
        return *this;
    f_ = o.value();
    //bits_ = o.bits();
    return *this;
}

int get_bits(const float f) {
    union float_bits fb;
    fb.f = f;
    return fb.bits;
}

std::ostream &operator<<(std::ostream &os, const Floating &f) {
    const int bits {get_bits(f.value())};
    int exponent {(bits >> mantissa_width) & exponent_mask};
    int mantissa {bits & mantissa_mask};

    if (bits >> absolute_width) // sign
        os << '-';

    if (exponent > (exponent_bias << 1))
        return os << "Inf";

    if (!exponent) {
        os << "0.";
        if (mantissa)
            ++exponent;
    } else {
        os << "1.";
    }

    for (int k {mantissa_width - 1}; k >= 0; --k)
        os << ((mantissa >> k) & 1);
    if (exponent || mantissa)
        os << " * 2^" << (exponent - exponent_bias);
    return os;
}

