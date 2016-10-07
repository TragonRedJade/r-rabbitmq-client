#include "doubler.h"


// [[Rcpp::export]]
int double_me(int x) {
  // takes a numeric input and doubles it
  return 2 * x;
}
