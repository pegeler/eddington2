#include <Rcpp.h>

using namespace Rcpp;

//' Get the Eddington Number for Cycling
//'
//' Gets the Eddington number for cycling.
//'
//' The Eddington Number for cycling, \emph{E}, is the maximum number where a
//' cyclist has ridden \emph{E} miles in \emph{E} days. This is not to be
//' confused with the
//' \href{https://en.wikipedia.org/wiki/Eddington_number}{Eddington Number in
//' astrophysics}, \eqn{N_{Edd}}, which represents the number of protons in the
//' observable universe.
//'
//' The Eddington Number for cycling is equivalent to the
//' \href{https://en.wikipedia.org/wiki/H-index}{Hirsch index} for publications.
//'
//' @param rides A vector of mileage, where each element represents a single
//'   ride.
//'
//' @return An integer which is the Eddington cycling number for the
//'   data provided.
//'
//' @seealso \code{\link{E_cum}}, \code{\link{E_sat}}, \code{\link{E_req}}
//'
//' @references http://www2.lowell.edu/users/jch/mtb/e.html
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
int E_num(NumericVector &rides) {
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

//' Calculate the cumulative Eddington number
//'
//' This function is much like \code{\link{E_num}} except it provides
//' a cumulative Eddington number over the vector rather than a single summary
//' number.
//'
//' @inheritParams E_num
//' @seealso \code{\link{E_num}}, \code{\link{E_sat}}, \code{\link{E_req}}
//' @return An integer vector the same length as \code{rides}.
//' @export
// [[Rcpp::export]]
IntegerVector E_cum(NumericVector &rides) {
  int n = rides.size(), running = 0, ride = 0, above = 0;
  IntegerVector E(n), H(n);

  for (int i = 0; i < n; i++) {
    ride = (int) rides[i];
    if (ride > running) {
      above++;
      if (ride < n) H[ride]++;

      if (above > running) {
        running++;
        above -= H[running];
      }
    }

    E[i] = running;

  }

  return E;
}

//' Get the number of rides required to increment to the next Eddington number
//'
//' @inheritParams E_num
//' @seealso \code{\link{E_num}}, \code{\link{E_sat}}, \code{\link{E_cum}}
//' @return A named list with the current Eddington number (\code{E}) and the
//'   number of rides required to increment by one (\code{req}).
//' @export
// [[Rcpp::export]]
List E_req(NumericVector &rides) {
  int n = rides.size(), E = 0, ride = 0, above = 0;
  IntegerVector H(n + 2);

  for (int i = 0; i < n; i++) {
    ride = (int) rides[i];
    if (ride > E) {
      above++;
      H[std::min(ride, n + 1)]++;

      if (above > E) {
        E++;
        above -= H[E];
      }
    }
  }

  List out = List::create(
    _["E"] = E,
    _["req"] = E + 1 - above
  );

  out.attr("class") = "E_req";

  return out;
}

/*** R
# Generate data
set.seed(2018)
rides <- rgamma(15, shape = 2, scale = 10)

# View the rides sorted in decreasing order
setNames(sort(rides, decreasing = TRUE), seq_along(rides))

# Get the Eddington number
E_num(rides)
E_num(rep(100, 15))
E_num(numeric(0))

# Get the cumulative Eddington number
E_cum(rides)
E_cum(rep(100, 15))
E_cum(numeric(0))
*/
