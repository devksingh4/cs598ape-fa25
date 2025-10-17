#include "poly_utils.h"
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <unordered_map>

static std::unordered_map<const Poly*, int64_t> degree_cache;

Poly create_poly(void) {
  Poly p;
  memset(p.coeffs, 0, sizeof(p.coeffs)); // faster zero initialization
  return p;
}

double positive_fmod(double x, double m) {
  double r = fmod(x, m);
  if (r < 0.0)
    r += m;
  return r;
}

int64_t poly_degree(const Poly& p) {
  auto it = degree_cache.find(&p);
  if (it != degree_cache.end()) {
    return it->second;
  }
  
  for (int64_t i = MAX_POLY_DEGREE - 1; i >= 0; --i) {
    if (fabs(p.coeffs[i]) > 1e-9) {
      degree_cache[&p] = i;
      return i;
    }
  }
  degree_cache[&p] = 0;
  return 0;
}

double get_coeff(const Poly& p, int64_t degree) {
  if (degree >= MAX_POLY_DEGREE || degree < 0) {
    return 0.0;
  }
  return p.coeffs[degree];
}

void set_coeff(Poly& p, int64_t degree, double value) {
  if (degree >= MAX_POLY_DEGREE || degree < 0) {
    return;
  }
  p.coeffs[degree] = value;
}

Poly coeff_mod(const Poly& p, double modulus) {
  Poly out = create_poly();
  // optim: compute actual degree once and iterate only up to it
  int64_t degree = poly_degree(p);
  for (int i = 0; i <= degree; i++) {
    double coeff = p.coeffs[i];
    if (fabs(coeff) > 1e-9) {
      double rounded = round(coeff);
      out.coeffs[i] = positive_fmod(rounded, modulus);
    }
  }
  return out;
}

Poly poly_add(const Poly& a, const Poly& b) {
  Poly sum = create_poly();
  int64_t max_deg = poly_degree(a);
  int64_t b_deg = poly_degree(b);
  if (b_deg > max_deg) max_deg = b_deg;
  
  for (int i = 0; i <= max_deg; i++) {
    sum.coeffs[i] = a.coeffs[i] + b.coeffs[i];
  }

  return sum;
}

Poly poly_mul_scalar(const Poly& p, double scalar) {
  Poly res = create_poly();
  int64_t degree = poly_degree(p);
  for (int i = 0; i <= degree; i++) {
    res.coeffs[i] = p.coeffs[i] * scalar;
  }
  return res;
}

Poly poly_mul(const Poly& a, const Poly& b) {
  Poly res = create_poly();

  // Optim: compute degrees once and iterate only necessary ranges
  int64_t a_deg = poly_degree(a);
  int64_t b_deg = poly_degree(b);
  
  for (int i = 0; i <= a_deg; i++) {
    double a_coeff = a.coeffs[i];
    if (fabs(a_coeff) > 1e-9) {
      int max_j = (b_deg < MAX_POLY_DEGREE - 1 - i) ? b_deg : MAX_POLY_DEGREE - 1 - i;
      for (int j = 0; j <= max_j; j++) {
        double b_coeff = b.coeffs[j];
        if (fabs(b_coeff) > 1e-9) {
          res.coeffs[i + j] += a_coeff * b_coeff;
        }
      }
    }
  }
  return res;
}

// optim: reduction for cyclotomic polynomial x^n + 1 (since x^n = -1, we have x^(n+k) = -x^k)
Poly poly_mod_optimized(Poly& p, size_t n) {
  Poly result = create_poly();
  for (int i = 0; i < MAX_POLY_DEGREE; i++) {
    if (fabs(p.coeffs[i]) > 1e-9) {
      if (i < n) {
        result.coeffs[i] = p.coeffs[i];
      } else {
        int wrapped_idx = i % n;
        int num_wraps = i / n;
        // Apply negation for odd number of wraps
        double sign = (num_wraps % 2 == 0) ? 1 : -1;
        result.coeffs[wrapped_idx] += sign * p.coeffs[i];
      }
    }
  }
  
  return result;
}