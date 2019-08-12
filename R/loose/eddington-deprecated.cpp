#include <Rcpp.h>
using namespace Rcpp;

//' @rdname Eddington_number
//' @export
// [[Rcpp::export]]

int E_fast(NumericVector rides) {

  // Check vector size
  int n = rides.size();

  // Return 0 if no elements
  if (!n) return 0;

  // Sort in descending order
  NumericVector r = clone(rides);
  r.sort(true);

  // Iterate through list
  int E = 0;
  for (; E < n; E++) {
    if (r(E) < E + 1) break;
  }

  return E;

}

/*** R
# Generate data
set.seed(2018)
rides <- rgamma(15, shape = 2, scale = 10)

# View the rides sorted in decreasing order
setNames(sort(rides, decreasing = TRUE), seq_along(rides))

# Get the Eddington number
E_fast(rides)
E_fast(rep(100, 15))
E_fast(numeric(0))
*/
