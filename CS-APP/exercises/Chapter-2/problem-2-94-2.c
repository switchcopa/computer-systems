#include <stdio.h>
#include <stdint.h>
#include <limits.h>

typedef uint32_t float_bits;

__attribute__((optimize("O3")))
float_bits float_twice(float_bits f) {
    uint32_t sign = (f >> 31) & 1u;
    uint32_t exp  = (f >> 23) & 0xFFu;
    uint32_t frac =  f & 0x7FFFFFu;

    if (exp == 0xFFu) return f;

    uint8_t denorm = (exp == 0u);

    exp += 1u & !denorm;
    frac <<= 1u & denorm;
    frac &= (exp == 0xFFu) ? 0u : (uint32_t)0xFFFFFFFFu;

    return (sign << 31) | (exp << 23) | frac;
}

static inline float u2f(float_bits f) {
    union {
        float_bits u;
        float f;
    } pun;

    pun.u = f;
    return pun.f;
}

static inline float_bits f2u(float f) {
    union {
        float_bits u;
        float f;
    } pun;

    pun.f = f;
    return pun.u;
}

static inline int is_special(float_bits f) {
    uint8_t exp = (f >> 23) & 0xFFu;
    return !(exp ^ 0xFFu);
}

float_bits float_twice_expected(float_bits f) {
    if (is_special(f))
        return f;

    float x = u2f(f);
    x *= 2.0f;
    return f2u(x);
}

int main(void) {
    float_bits (*test_function)(float_bits) = float_twice;
    float_bits (*expected)(float_bits) = float_twice_expected;

    for (float_bits b = 0U; b < UINT32_MAX; b++)
        if (test_function(b) != expected(b))
            return 1;

    return 0;
}
