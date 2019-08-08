#' Get the Eddington Number for Cycling
#'
#' Gets the Eddington number for cycling.
#'
#' The Eddington Number for cycling, \emph{E}, is the maximum number where a
#' cyclist has ridden \emph{E} miles in \emph{E} days. This is not to be
#' confused with the
#' \href{https://en.wikipedia.org/wiki/Eddington_number}{Eddington Number in
#' astrophysics}, \eqn{N_{Edd}}, which represents the number of protons in the
#' observable universe.
#'
#' The Eddington Number for cycling is equivalent to the
#' \href{https://en.wikipedia.org/wiki/H-index}{Hirsch index} for publications.
#'
#' @param rides A vector of mileage, where each element represents a single
#'   ride.
#'
#' @return An integer which is the Eddington cycling number for the data
#'   provided.
#'
#' @references http://www2.lowell.edu/users/jch/mtb/e.html
#' @examples
#' # Randomly generate a set of 15 rides
#' rides <- rgamma(15, shape = 2, scale = 10)
#'
#' # View the rides sorted in decreasing order
#' setNames(sort(rides, decreasing = TRUE), seq_along(rides))
#'
#' # Get the Eddington number
#' Eddington_number(rides)
Eddington_number <- function(rides) {
  sum(sort(rides, decreasing = TRUE) >= seq_along(rides))
}
