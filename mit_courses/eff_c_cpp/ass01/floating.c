#include "floating.h"

/* Function print_binary:
 * ------------------------
 *  displays x in binary format (zeros and ones)
 */
void print_binary(unsigned int x)
{
    for (int i = (sizeof(int) * 8) - 1; i >= 0; i--)
        (x & (1 << i)) ? putchar('1') : putchar('0');
    printf("\n");
}

/* Function print_hex:
 * ----------------------------
 *  display bits of a float number
 */
void print_hex(float f)
{
    union float_bits t;
    t.f = f;
    printf("Float bits: 0x%x\n", t.bits);
}

/* Function print_float:
 * -----------------------------------
 *  displays a float number in the following format:
 *  one sign bit, eight exponent bits and 32 mantissa bits
 */
void print_float(FILE *output, float f)
{
    union float_bits t;
    t.f = f;

    uint32_t sign_bit = t.bits >> ABSOLUTE_WIDTH;
    uint32_t exponent = (t.bits >> MANTISSA_WIDTH) & EXPONENT_MASK;
    uint32_t mantissa = t.bits & MANTISSA_MASK;

    if (sign_bit)
        fprintf(output, "-");

    if (exponent > EXPONENT_BIAS << 1) {
        fprintf(output, "Inf\n");
        return;
    } else if (!exponent) {
        fprintf(output, "0.");
        if (mantissa) ++exponent;
    } else {
        fprintf(output, "1.");
    }

    for (int8_t k = MANTISSA_WIDTH - 1; k >= 0; --k)
        fprintf(output, "%d", (mantissa >> k) & 1);

    if (exponent || mantissa)
        fprintf(output, " * 2^%d\n", exponent - EXPONENT_BIAS);
}
