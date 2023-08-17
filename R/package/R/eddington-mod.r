#' An Rcpp Module for Tracking Eddington Numbers for Cycling
#'
#' @examples
#' e <- new(EddingtonModule, c(3, 3, 2))
#' e$current
#'
#' e$update(c(3, 3, 5))
#' e$cumulative
#'
#' @name EddingtonModule
#' @import methods
#' @importFrom Rcpp loadModule
#' @export EddingtonModule
Rcpp::loadModule("eddington_mod", TRUE)
