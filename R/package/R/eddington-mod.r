#' An Rcpp Module for Tracking Eddington Numbers for Cycling
#'
#' A stateful C++ object for computing Eddington numbers.
#'
#' @section Warning:
#'
#' `EddingtonModule` objects cannot be serialized; they cannot be carried
#' between sessions using [base::saveRDS] or [base::save] and then loaded later
#' using [base::readRDS] or [base::load].
#'
#' @param rides An optional vector of values used to initialize the class.
#' @param store_cumulative Whether to store a vector of the cumulative Eddington
#'    number, as accessed from the `cumulative` property.
#' @field new Constructor. Parameter list may either be empty, `store_cumulative`,
#'    or `rides` and `store_cumulative`
#' @field current The current Eddington number.
#' @field cumulative A vector of Eddington numbers or `NULL` if `store_cumulative`
#'    is `FALSE`.
#' @field hashmap A `data.frame` containing the distances and counts above the
#'    current Eddington number.
#' @field update Update the class state with new data.
#' @field getNumberToNext Get the number of additional distances required to
#'    reach the next Eddington number.
#' @field getNumberToTarget Get the number of additional distances required to
#'    reach a target Eddington number.
#'
#' @examples
#' # Create a class instance with some initial data
#' e <- EddingtonModule$new(c(3, 3, 2), store_cumulative = TRUE)
#' e$current
#'
#' # Update with new data and look at the vector of cumulative Eddington numbers.
#' e$update(c(3, 3, 5))
#' e$cumulative
#'
#' # Get the number of rides required to reach the next Eddington number and
#' # an Eddington number of 4.
#' e$getNumberToNext()
#' e$getNumberToTarget(4)
#'
#' @name EddingtonModule
#' @importFrom methods new
#' @importFrom Rcpp loadModule
#' @export EddingtonModule
Rcpp::loadModule("eddington_mod", TRUE)
