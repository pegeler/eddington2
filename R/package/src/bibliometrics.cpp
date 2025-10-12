#include <Rcpp.h>
#include <cmath>

//' @rdname h_index
//' @export
// [[Rcpp::export]]
int g_index(const Rcpp::NumericVector &citations, bool sorted = false) {
  // NOTE: The choice to use NumericVector instead of IntegerVector can push
  //       the g-index higher on edge cases. Try using
  //       `as.integer(daily_totals$total_length)` as an example.
  if (!citations.size())
    return 0;  // Early exit

  auto c = sorted ? citations : clone(citations);
  if (!sorted)
    c.sort(true);

  double cumsum = 0;
  int g = 0;
  for (; g < c.size(); g++) {
    cumsum += c(g);
    if (cumsum < pow(g + 1, 2))
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
