context("Bibliometrics")

data("daily_totals")

# Reference: https://en.wikipedia.org/wiki/G-index
cites <- tibble::tribble(
  ~row, ~author1, ~author2,
  1, 30, 10,
  2, 17, 9,
  3, 15, 9,
  4, 13, 9,
  5, 8, 8,
  6, 6, 6,
  7, 5, 5,
  8, 4, 4,
  9, 3, 2,
  10, 1, 1
)

test_that("h-index works", {
  expect_identical(h_index(cites$author1), 6L)
  expect_identical(h_index(cites$author2), 6L)

  # NA handling
  expect_identical(h_index(c(1:3, NA), na.rm = TRUE), 2L)
  expect_identical(h_index(c(1:3, NA), na.rm = FALSE), NA_integer_)

  # Large value check
  expect_error(h_index(c(3**31, NA_real_), na.rm = TRUE), "exceed limits")
})

test_that("i10-index works", {
  expect_identical(i10_index(cites$author1), 4L)
  expect_identical(i10_index(cites$author2), 1L)
})


test_that("g-index works", {
  d <- daily_totals$total_length
  expect_identical(g_index(d), 38L)
  expect_identical(g_index(as.integer(d)), 37L)

  expect_identical(g_index(cites$author1, sorted = TRUE), 10L)
  expect_identical(g_index(cites$author2, sorted = TRUE), 7L)

  # Edge cases
  expect_identical(g_index(integer()), 0L)

  # NA handling
  expect_identical(g_index(c(1:3, NA), na.rm = TRUE), 2L)
  expect_identical(g_index(c(1:3, NA), na.rm = FALSE), NA_integer_)

  # Sort check
  expect_no_warning(g_index(1:3))  # sort is default
  expect_warning(
    g_index(1:3, sorted = TRUE),  # if caller claims data is pre-sorted, we still check
    "unsorted"
  )
})
