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
#' h_index <- index(force)
#' h_index(citations)
#'
#' # Create a g-index function
#' g_index <- index(\(i) i * i, cumulative = TRUE)
#' g_index(citations)
#'
#' # Create an i10-index
#' i10_index <- index(\(i) 10L)
#' i10_index(citations)
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
#' @param citations A vector of citation counts.
#' @param sorted Whether the data is pre-sorted. This may speed up computations
#'    for some algorithms.
#' @returns The summary number.
#' @seealso [E_num()], [durfee()]
#' @name h_index
#' @aliases bibliometrics
#' @export
h_index <- function(citations) .Call(`_eddington_E_num`, citations)

#' @rdname h_index
#' @export
i10_index <- function(citations) sum(citations >= 10L)


if (FALSE) {  # Quick benchmark
  h_alt <- index(force)
  g_alt <- index(\(i) i * i, cumulative = TRUE)
  i10_alt <- index(\(i) 10L)

  data(daily_totals)

  xs <- daily_totals$total_length

  microbenchmark::microbenchmark(
    h_index(xs),
    h_alt(xs),
    g_index(xs),
    g_alt(xs),
    i10_index(xs),
    i10_alt(xs)
  )

  # FINDING: way faster. as fun as the closure is for generalization,
  # performance demands writing separate functions.
}
