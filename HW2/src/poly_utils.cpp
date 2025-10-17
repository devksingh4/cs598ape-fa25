#include "poly_utils.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

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
  for (int64_t i = MAX_POLY_DEGREE - 1; i >= 0; i--) {
    if (fabs(p.coeffs[i]) > 1e-9) {
      return i;
    }
  }
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

void poly_divmod(const Poly& num, const Poly& den, Poly* quot, Poly* rem) {
  size_t ndeg = poly_degree(num);
  size_t ddeg = poly_degree(den);

  *quot = create_poly();
  *rem = num;

  if (ndeg < ddeg) {
    return;
  }

  double d_lead = get_coeff(den, ddeg);
  double d_lead_inv = 1.0 / d_lead;
  
  std::vector<int> nonzero_idx;
  nonzero_idx.reserve(ddeg + 1);
  for (int i = 0; i <= ddeg; ++i) {
    if (fabs(den.coeffs[i]) > 1e-9) {
      nonzero_idx.push_back(i);
    }
  }

  for (int64_t k = ndeg - ddeg; k >= 0; --k) {
    int64_t target_deg = ddeg + k;
    double r_coeff = get_coeff(*rem, target_deg);
    
    double coeff = trunc(round(r_coeff) * round(d_lead_inv));
    
    if (fabs(coeff) > 1e-9) {
      quot->coeffs[k] += coeff;

      for (int idx : nonzero_idx) {
        int64_t deg = idx + k;
        rem->coeffs[deg] -= coeff * den.coeffs[idx];
      }
    }
  }
}