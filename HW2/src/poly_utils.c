#include "poly_utils.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

Poly create_poly(void) {
  Poly p;
  memset(p.coeffs, 0, sizeof(p.coeffs)); // faster zero initialization
  return p;
}

double positive_fmod(double x, double m) {
  assert(m > 0.0);
  double r = fmod(x, m);
  if (r < 0.0)
    r += m;
  return r;
}

int64_t poly_degree(Poly p) {
  for (int64_t i = MAX_POLY_DEGREE - 1; i >= 0; i--) {
    if (fabs(p.coeffs[i]) > 1e-9) {
      return i;
    }
  }
  return 0;
}

double get_coeff(Poly p, int64_t degree) {
  if (degree >= MAX_POLY_DEGREE || degree < 0) {
    return 0.0;
  }
  return p.coeffs[degree];
}

void set_coeff(Poly *p, int64_t degree, double value) {
  if (degree >= MAX_POLY_DEGREE || degree < 0) {
    return;
  }
  p->coeffs[degree] = value;
}

Poly coeff_mod(Poly p, double modulus) {
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

Poly poly_add(Poly a, Poly b) {
  Poly sum = create_poly();
  int64_t max_deg = poly_degree(a);
  int64_t b_deg = poly_degree(b);
  if (b_deg > max_deg) max_deg = b_deg;
  
  for (int i = 0; i <= max_deg; i++) {
    sum.coeffs[i] = a.coeffs[i] + b.coeffs[i];
  }
  return sum;
}

Poly poly_mul_scalar(Poly p, double scalar) {
  Poly res = create_poly();
  int64_t degree = poly_degree(p);
  for (int i = 0; i <= degree; i++) {
    res.coeffs[i] = p.coeffs[i] * scalar;
  }
  return res;
}

Poly poly_mul(Poly a, Poly b) {
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

void poly_divmod(Poly num, Poly den, Poly *quot, Poly *rem) {
  // In our case `den` should always be (x^n + 1)
  assert(poly_degree(den) > 0 || fabs(get_coeff(den, 0)) > 1e-9);

  size_t ndeg = poly_degree(num);
  size_t ddeg = poly_degree(den);

  *quot = create_poly();
  *rem = num;

  if (ndeg < ddeg) {
    return;
  }

  double d_lead = get_coeff(den, ddeg);
  assert(fabs(d_lead) > 1e-9);

  for (int64_t k = ndeg - ddeg; k >= 0; --k) {
    int64_t target_deg = ddeg + k;
    double r_coeff = get_coeff(*rem, target_deg);
    double coeff = trunc(round(r_coeff) / round(d_lead));
    quot->coeffs[k] += coeff;

    // optim: only iterate to the denominator degree
    for (int i = 0; i <= ddeg; i++) {
      if (fabs(den.coeffs[i]) > 1e-9) {
        int64_t deg = i + k;
        assert(deg < MAX_POLY_DEGREE);
        rem->coeffs[deg] -= coeff * den.coeffs[i];
      }
    }
  }

  assert(poly_degree(*rem) < poly_degree(den));
}

Poly poly_round_div_scalar(Poly x, double divisor) {
  Poly out = create_poly();
  assert(fabs(divisor) > 1e-9);

  // Optim: only iterate to actual degree
  int64_t degree = poly_degree(x);
  for (int i = 0; i <= degree; i++) {
    double v = x.coeffs[i];
    out.coeffs[i] = round(v / divisor);
  }
  return out;
}
