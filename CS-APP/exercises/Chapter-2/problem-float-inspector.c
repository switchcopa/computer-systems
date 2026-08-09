#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>

#define FLOAT_32_ALIGNMENT sizeof(float)

#define FLOAT_T_TYPE_DENORMALIZED 0
#define FLOAT_T_TYPE_NORMALIZED   1
#define FLOAT_T_TYPE_INFINITY     2
#define FLOAT_T_TYPE_NAN          3

struct float_t
{
    uint8_t  sign;
    uint8_t  exp_raw;
    int16_t  exp_E;
    uint32_t fraction_f;
    uint8_t  type;
};

__attribute__((noinline))
void inspect_float(const void *ptr, struct float_t *out)
{
    uint32_t f32;
    memcpy(&f32, ptr, sizeof(float));
    printf("f32 = %0X\n", f32);

    out->sign = (f32 >> 31);
    out->exp_raw = (f32 >> 23) & 0xFF;
    out->fraction_f = (~(uint32_t)0 >> 9) & f32;

    if (out->exp_raw == 255)
    {
        if (out->fraction_f != 0)
            out->type = FLOAT_T_TYPE_NAN;
        else
            out->type = FLOAT_T_TYPE_INFINITY;
        out->exp_E = 0;
    }
    else if (out->exp_raw == 0)
    {
        out->type  = FLOAT_T_TYPE_DENORMALIZED;
        out->exp_E = -126;
    }
    else
    {
        out->type  = FLOAT_T_TYPE_NORMALIZED;
        out->exp_E = out->exp_raw - 127;
    }
}

int main(void)
{
    float sample = NAN;
    
    struct float_t test_float;
    inspect_float(&sample, &test_float);

    printf("Sign:            %u\n", test_float.sign);
    printf("Raw Exponent e:  0x%02X (%u)\n", test_float.exp_raw, test_float.exp_raw);
    printf("Decoded Scale E: %d\n", test_float.exp_E);
    printf("Fraction f:      0x%06X\n", test_float.fraction_f);
    printf("Category Type:   %u\n", test_float.type);

    return 0;
}
