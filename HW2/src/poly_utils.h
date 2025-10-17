#ifndef POLY_UTILS_H
#define POLY_UTILS_H

#include "types.h"
#include <math.h>
#include <stdint.h>

double positive_fmod(double x, double m);

int64_t poly_degree(const Poly& p);

double get_coeff(const Poly& p, int64_t degree);

void set_coeff(Poly& p, int64_t degree, double value);

Poly coeff_mod(const Poly& p, double modulus);

Poly poly_add(const Poly& a, const Poly& b);

Poly poly_mul_scalar(const Poly& p, double scalar);

Poly poly_mul(const Poly& a, const Poly& b);

void poly_divmod(const Poly& numerator, const Poly& denominator, Poly* quotient,
                 Poly* remainder);

Poly create_poly(void);

#endif