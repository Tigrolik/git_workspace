#ifndef _FLOATING_H
#define _FLOATING_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define ABSOLUTE_WIDTH 31
#define MANTISSA_WIDTH 23
#define EXPONENT_WIDTH 8
#define EXPONENT_MASK 0xffu
#define MANTISSA_MASK 0x007fffffu
#define EXPONENT_BIAS 127

union float_bits {
    float f;
    unsigned int bits;
};

/* Function print_binary:
 * ------------------------
 *  displays x in binary format (zeros and ones)
 */
void print_binary(unsigned int x);

/* Function print_hex:
 * ----------------------------
 *  display bits of a float number
 */
void print_hex(float f);

void print_float(FILE *output, float f);

#endif
