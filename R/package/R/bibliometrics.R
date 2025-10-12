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
#' @param xs A vector of citation counts.
#' @returns The summary number.
#' @seealso [E_num()], [durfee()]
#' @name h_index
NULL

#' @rdname h_index
#' @export
h_index <- index(force)

#' @rdname h_index
#' @export
g_index <- index(\(i) i * i, cumulative = TRUE)

#' @rdname h_index
#' @export
i10_index <- index(\(i) 10L)


if (FALSE) {
  library(eddington)
  h_alt <- E_num
  i10_alt <- function(xs) sum(xs >= 10L)

  data(daily_totals)

  xs <- daily_totals$total_length

  microbenchmark::microbenchmark(
    h_index(xs),
    h_alt(xs),
    g_index(xs),
    i10_index(xs),
    i10_alt(xs)  # way faster. as fun as the closure is for generalization,
                 # performance demands writing separate functions.
  )
}
