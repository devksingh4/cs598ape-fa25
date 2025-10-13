#include "ring_utils.h"
#include "poly_utils.h"

Poly ring_add_mod(Poly x, Poly y, double modulus, Poly poly_mod) {
  Poly sum = poly_add(x, y);

  Poly sum_mod = coeff_mod(sum, modulus);

  size_t n = poly_degree(poly_mod);
  Poly rem = poly_mod_optimized(sum_mod, n);

  Poly rem_mod = coeff_mod(rem, modulus);

  return rem_mod;
}

Poly ring_mul_mod(Poly x, Poly y, double modulus, Poly poly_mod) {
  Poly prod = poly_mul(x, y);

  Poly prod_mod = coeff_mod(prod, modulus);

  size_t n = poly_degree(poly_mod);
  Poly rem = poly_mod_optimized(prod_mod, n);

  Poly rem_mod = coeff_mod(rem, modulus);

  return rem_mod;
}

Poly ring_mul_no_mod_q(Poly x, Poly y, Poly poly_mod) {
  Poly prod = poly_mul(x, y);

  size_t n = poly_degree(poly_mod);
  Poly rem = poly_mod_optimized(prod, n);

  return rem;
}

Poly ring_add_no_mod_q(Poly x, Poly y, Poly poly_mod) {
  Poly sum = poly_add(x, y);

  size_t n = poly_degree(poly_mod);
  Poly rem = poly_mod_optimized(sum, n);

  return rem;
}

Poly ring_mul_poly_mod(Poly x, Poly y, Poly poly_mod) {
  Poly prod = poly_mul(x, y);
  size_t n = poly_degree(poly_mod);
  Poly rem = poly_mod_optimized(prod, n);
  return rem;
}

Poly ring_add_poly_mod(Poly x, Poly y, Poly poly_mod) {
  Poly sum = poly_add(x, y);
  size_t n = poly_degree(poly_mod);
  Poly rem = poly_mod_optimized(sum, n);
  return rem;
}