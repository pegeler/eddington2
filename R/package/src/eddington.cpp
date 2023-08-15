// [[Rcpp::interfaces(r, cpp)]]
#include <Rcpp.h>
#include <optional>
#include <unordered_map>
#include <vector>

using namespace Rcpp;

// [[Rcpp::plugins(cpp17)]]


struct EddingtonResult {
  int eddington_number = 0;
  int n_above = 0;
  std::optional<std::vector<int>> cumulative;
};


EddingtonResult compute_eddington_number(
    const IntegerVector& rides, bool store_cumulative = false) {
  EddingtonResult e;
  std::unordered_map<int, int> dist_table(150);

  if (store_cumulative) {
    e.cumulative = std::vector<int>();
    e.cumulative->reserve(rides.size());
  }

  for (auto ride : rides) {
    if (ride > e.eddington_number) {
      e.n_above++;
      dist_table[ride]++;
      if (e.n_above > e.eddington_number) {
        e.n_above -= dist_table[++e.eddington_number];
        dist_table.erase(e.eddington_number);
      }
    }
    if (store_cumulative) {
      e.cumulative->push_back(e.eddington_number);
    }
  }

  return e;
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
int E_num(const IntegerVector& rides) {
  auto e = compute_eddington_number(rides, false);
  return e.eddington_number;
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
IntegerVector E_cum(const IntegerVector& rides) {
  auto e = compute_eddington_number(rides, true);
  return wrap(*e.cumulative);
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
List E_next(const IntegerVector& rides) {
  auto e = compute_eddington_number(rides, false);
  List out = List::create(
    _["E"] = e.eddington_number,
    _["req"] = e.eddington_number + 1 - e.n_above
  );

  out.attr("class") = "E_next";

  return out;
}


/*** R
E_num(c(2.2, 1.1, 3.3))
E_cum(c(2.2, 1.1, 3.3))
E_next(c(2.2, 1.1, 3.3))
*/
