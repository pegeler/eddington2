#' Compute the side length of a Durfee square
#'
#' @param is An integer vector representing an integer partition.
#' @returns The side length of the Durfee square for that partition.
#' @export
durfee <- function(is) .Call(`_eddington_E_num`, is)

# Using .Call instead of just assigning `E_num` to `durfee` so that formals
# could be renamed.
