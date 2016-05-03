#ifndef FLOATING_H
#define FLOATING_H

#include <iostream>

static constexpr int absolute_width {31};
static constexpr int mantissa_width {23};
static constexpr int exponent_width {8};
static constexpr int mantissa_mask  {0x007fffffu};
static constexpr int exponent_mask  {0x0ffu};
static constexpr int exponent_bias  {127};

union float_bits {
    float f;
    int bits;
};

class Floating {
    public:
        Floating(const float = 0.0);
        Floating(const Floating&);
        Floating &operator=(const Floating&);

        float value() const { return f_; }
        //unsigned int bits() const { return bits_; }

        friend std::ostream &operator<<(std::ostream&, const Floating&);
    private:
        float f_;
        //unsigned int bits_;
};

int get_bits(const float);

#endif

