// Testing if Rcpp::IntegerVector, std::map, or std::unordered_map is faster
// also looking at memory usage.
#include <Rcpp.h>
#include <map>
#include <unordered_map>

using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]

// [[Rcpp::export]]
int E_vec(NumericVector &rides) {
  int n = rides.size(), E = 0, ride = 0, above = 0;
  IntegerVector H(n);

  for (int i = 0; i < n; i++) {
    ride = (int) rides[i];
    if (ride > E) {
      above++;
      if (ride < n) H[ride]++;

      if (above > E) {
        E++;
        above -= H[E];
      }
    }
  }

  return E;
}

// [[Rcpp::export]]
int E_map(NumericVector &rides) {
  int n = rides.size(), E = 0, ride = 0, above = 0;
  std::map<int, int> H;

  for (int i = 0; i < n; i++) {
    ride = (int) rides[i];
    if (ride > E) {
      above++;
      if (ride < n) H[ride]++;

      if (above > E) {
        E++;
        above -= H[E];
      }
    }
  }

  return E;
}

// [[Rcpp::export]]
int E_umap(NumericVector &rides) {
  int n = rides.size(), E = 0, ride = 0, above = 0;
  std::unordered_map<int, int> H;

  for (int i = 0; i < n; i++) {
    ride = (int) rides[i];
    if (ride > E) {
      above++;
      if (ride < n) H[ride]++;

      if (above > E) {
        E++;
        above -= H[E];
      }
    }
  }

  return E;
}

/*** R
library(microbenchmark)
library(profmem)

E_num <- function(rides) sum(sort(rides, decreasing = TRUE) >= seq_along(rides))

set.seed(2018)
rides <- rgamma(1e6, shape = 2, scale = 10) # Tried with various powers of 10

microbenchmark(
  #E_num(rides),
  E_vec(rides),
  E_map(rides),
  E_umap(rides))

## For small n (100), Rcpp::IntegerVector is faster
# Unit: microseconds
#           expr   min     lq    mean median     uq    max neval
#   E_vec(rides) 1.161 1.2545 1.38310 1.3085 1.4400  3.076   100
#   E_map(rides) 3.636 3.7815 4.00958 3.8580 3.9440 11.397   100
#  E_umap(rides) 4.553 4.7705 5.04050 4.8560 4.9695 17.614   100
#
## For large n (1e6), std::unordered_map wins
# Unit: microseconds
#           expr      min        lq      mean   median        uq      max neval
#   E_vec(rides) 1560.924 2603.3080 2720.8150 2623.952 2648.7045 6430.644   100
#   E_map(rides)  957.138  965.4295  985.9452  974.392  988.9025 1358.485   100
#  E_umap(rides)  759.446  767.8320  780.5924  778.066  788.4710  901.169   100

p <- profmem({
  #E_num(rides)
  E_vec(rides)
  E_map(rides)
  E_umap(rides)
})

p

## For small n (100), Rcpp::IntegerVector has a little extra overhead
# Memory allocations:
#        what bytes    calls
# 1     alloc   440  E_vec()
# 2     alloc  2544  E_vec()
# 3     alloc  2544  E_map()
# 4     alloc  2544 E_umap()
# total        8072
#
## For large n (1e6), obviously Rcpp::IntegerVector is disadvantaged
# Memory allocations:
#        what   bytes    calls
# 1     alloc 4000040  E_vec()
# 2     alloc    2544  E_vec()
# 3     alloc    2544  E_map()
# 4     alloc    2544 E_umap()
# total       4007672
*/
