#include <Rcpp.h>
#include <cmath>

// [[Rcpp::export]]
int g_index(const Rcpp::NumericVector &citations, bool sorted = false) {
  if (!citations.size())
    return 0;  // Early exit

  auto c = sorted ? citations : clone(citations);
  if (!sorted)
    c.sort(true);

  double cumsum = 0;
  double prev = INFINITY;
  bool warned = false;
  int g = 0;
  for (; g < c.size(); g++) {
    double cite = c(g);

    // Sort check
    if (sorted && !warned && prev < cite) {
      Rcpp::warning("Data is unsorted, which may invalidate results");
      warned = true;
    }
    prev = cite;

    cumsum += cite;
    if (cumsum < (g + 1) * (g + 1)) // reject `pow` to avoid floating point conversion
      break;
  }

  return g;
}

/*** R
data(daily_totals)
g_index(daily_totals$total_length)

sorted_lens <- sort(daily_totals$total_length, decreasing = TRUE)
g_index(sorted_lens, sorted = TRUE)
*/
