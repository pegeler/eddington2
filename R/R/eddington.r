#' @useDynLib eddington
#' @importFrom Rcpp sourceCpp
NULL

#' Determine if a dataset satisfies a specified Eddington number
#'
#' Indicates whether a certain Eddington number is satisfied, given the data.
#'
#' @inheritParams E_num
#' @param candidate The Eddington number to test for.
#' @seealso \code{\link{E_cum}}, \code{\link{E_num}}, \code{\link{E_req}}
#' @return A logical vector of length 1.
#' @export
E_sat <- function(rides, candidate)
  length(rides) >= candidate && sum(rides >= candidate) >= candidate

#' @export
print.E_req <- function(x, ...) {

  out_string <- sprintf(
    "Your current Eddington Number is %i. You need %i %s of %i or greater to get to an Eddington number of %i.",
    x$E,
    x$req,
    if (x$req > 1) "rides" else "ride",
    x$E + 1,
    x$E + 1
  )

  cat(strwrap(out_string), sep = "\n")

}
