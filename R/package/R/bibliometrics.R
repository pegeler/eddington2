filter_na <- \(x) Filter(Negate(is.na), x)

#' Define a custom bibliometric index function
#'
#' @param f A function to be applied to the index before comparison.
#' @param cumulative A logical on whether to apply a cumulative sum to the counts.
#' @examples
#' # NOTE: These will all be less performant than their counterparts exported
#' # in this package, i.e., `h_index()`, `g_index()`, `i10_index()`.
#' set.seed(2018)
#' citations <- rgamma(30, shape = 2, scale = 10)
#'
#' # Create an h-index
#' my_h_index <- index(force)
#' my_h_index(citations)
#'
#' # Create a g-index function
#' my_g_index <- index(\(i) i * i, cumulative = TRUE)
#' my_g_index(citations)
#'
#' # Create an i10-index
#' my_i10_index <- index(\(i) 10L)
#' my_i10_index(citations)
#'
#' @returns A function that will compute the specified index.
#' @seealso [bibliometrics]
#' @export
index <- function(f, cumulative = FALSE) {
  force(f)
  force(cumulative)
  function(xs) {
    is <- vapply(seq_along(xs), f, integer(1L))
    xs <- sort(xs, decreasing = TRUE)
    sum((if (cumulative) cumsum(xs) else xs) >= is)
  }
}

#' Compute several bibliometric indices
#'
#' Compute bibliometric indices such as the h-index, g-index, and i10-index.
#'
#' @section Implicit Type Conversions:
#' The `h_index()` function implicitly coerces inputs into integer vectors,
#' which will truncate any floating point inputs. This usually will result in
#' expected outputs, as there are not typically fractional inputs in the
#' intended domain, and the definitions of these indices are defined on integral
#' thresholds explicitly. However, to maximize the versatility of g-index
#' computation, the `g_index()` function does not perform this integer coercion.
#' Therefore it is worth noting that floating point input can push the g-index
#' higher on edge cases. For example,
#' `g_index(as.integer(daily_totals$total_length)) !=
#' g_index(daily_totals$total_length)` Thus to ensure accurate g-index results
#' on data that may have a fractional component, it is advised to first perform
#' an integer conversion prior to passing a vector into `g_index()` or otherwise
#' validate inputs.
#'
#' This integer conversion will also cause the `h_index()` to fail when inputs
#' contain extremely large values (\eqn{> 2^{31} - 1}{> 2^31 - 1}). The
#' Eddington number family of functions and `durfee()` do not have this check,
#' and may result in inaccurate outputs.
#'
#' @param citations A vector of citation counts.
#' @param na.rm If `TRUE`, `NA` values will be filtered out. Otherwise, any `NA`
#'   value found in the vector will propagate and `NA` will be returned.
#' @param is_sorted Whether the data is pre-sorted in descending order. This may
#'   speed up computations for some algorithms. The pre-sorted assumption is
#'   tested and a warning is emitted if unsorted data is detected.
#' @returns The summary number.
#' @references <https://en.wikipedia.org/wiki/Author-level_metrics>,
#' <https://en.wikipedia.org/wiki/G-index>
#' @seealso [E_num()], [durfee()]
#' @name h_index
#' @aliases bibliometrics
#' @export
h_index <- function(citations, na.rm = FALSE) {
  has_na <- anyNA(citations)
  if (!na.rm && has_na)
    return(NA_integer_)

  if (is.double(citations) && any(citations > .Machine$integer.max, na.rm = TRUE))
    stop("Values exceed limits for the integer data type.")

  .Call(`_eddington_E_num`, if (has_na) filter_na(citations) else citations)
}

#' @rdname h_index
#' @export
i10_index <- function(citations, na.rm = FALSE) sum(citations >= 10L, na.rm = na.rm)

#' @rdname h_index
#' @export
g_index <- function(citations, na.rm = FALSE, is_sorted = FALSE) {
  has_na <- anyNA(citations)
  if (!na.rm && has_na)
    return(NA_integer_)

  .Call(
    `_eddington_g_index_`,
    if (has_na) filter_na(citations) else citations,
    is_sorted
  )
}
