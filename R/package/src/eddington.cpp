// [[Rcpp::interfaces(r, cpp)]]
#include <Rcpp.h>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <climits>

using namespace Rcpp;

std::pair<int, int> compute_eddington_number(IntegerVector &rides) {
  int n = std::min<R_xlen_t>(rides.size(), INT_MAX - 1);
  int e = 0;
  int above = 0;
  std::unordered_map<int, int> dist_table(150);

  for (auto ride : rides) {
    if (ride > e) {
      above++;
      dist_table[std::min(ride, n + 1)]++;
      if (above > e) {
        above -= dist_table[++e];
        dist_table.erase(e);
      }
    }
  }

  return {e, above};
}

//' Get the Eddington number for cycling
//'
//' Gets the \href{https://en.wikipedia.org/wiki/Arthur_Eddington#Eddington_number_for_cycling}{Eddington number for cycling}.
//' The Eddington Number for cycling, \emph{E}, is the maximum number where a
//' cyclist has ridden \emph{E} miles on \emph{E} distinct days.
//'
//' The Eddington Number for cycling is related to computing the rank of an
//' integer partition, which is the same as computing the side length of its
//' \href{https://en.wikipedia.org/wiki/Durfee_square}{Durfee square}. Another
//' relevant application of this metric is computing the
//' \href{https://doi.org/10.1073/pnas.0507655102}{Hirsch index} for
//' publications.
//'
//' This is not to be confused with the
//' \href{https://en.wikipedia.org/wiki/Eddington_number}{Eddington Number in
//' astrophysics}, \eqn{N_{Edd}}, which represents the number of protons in the
//' observable universe.
//'
//' @param rides A vector of mileage, where each element represents a single
//'   day.
//'
//' @return An integer which is the Eddington cycling number for the
//'   data provided.
//'
//' @seealso \code{\link{E_cum}}, \code{\link{E_next}}, \code{\link{E_req}},
//'   \code{\link{E_sat}}
//'
//' @examples
//' # Randomly generate a set of 15 rides
//' rides <- rgamma(15, shape = 2, scale = 10)
//'
//' # View the rides sorted in decreasing order
//' setNames(sort(rides, decreasing = TRUE), seq_along(rides))
//'
//' # Get the Eddington number
//' E_num(rides)
//' @export
// [[Rcpp::export]]
int E_num(IntegerVector &rides) {
  auto result = compute_eddington_number(rides);
  return result.first;
}

//' Calculate the cumulative Eddington number
//'
//' This function is much like \code{\link{E_num}} except it provides
//' a cumulative Eddington number over the vector rather than a single summary
//' number.
//'
//' @inheritParams E_num
//' @seealso \code{\link{E_next}}, \code{\link{E_num}}, \code{\link{E_req}},
//'   \code{\link{E_sat}}
//' @return An integer vector the same length as \code{rides}.
//' @export
// [[Rcpp::export]]
IntegerVector E_cum(IntegerVector &rides) {
  int running = 0;
  int above = 0;
  std::unordered_map<int, int> dist_table(150);
  IntegerVector e(rides.size());

  for (R_xlen_t i = 0; i < rides.size(); i++) {
    int ride = rides[i];
    if (ride > running) {
      above++;
      if (ride < rides.size()) {
        dist_table[ride]++;
      }
      if (above > running) {
        above -= dist_table[++running];
        dist_table.erase(running);
      }
    }

    e[i] = running;

  }

  return e;
}

//' Get the number of rides required to increment to the next Eddington number
//'
//' Get the number of rides required to increment to the next Eddington number.
//'
//' @inheritParams E_num
//' @seealso \code{\link{E_cum}}, \code{\link{E_num}}, \code{\link{E_req}},
//'   \code{\link{E_sat}}
//' @return A named list with the current Eddington number (\code{E}) and the
//'   number of rides required to increment by one (\code{req}).
//' @export
// [[Rcpp::export]]
List E_next(IntegerVector &rides) {
  auto result = compute_eddington_number(rides);
  List out = List::create(
    _["E"] = result.first,
    _["req"] = result.first + 1 - result.second
  );

  out.attr("class") = "E_next";

  return out;
}

/*** R
E_num(c(2.2, 1.1, 3.3))
*/
