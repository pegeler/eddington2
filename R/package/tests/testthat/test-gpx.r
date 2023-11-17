context("GPX file processing")

test_that("...", {
  # TODO
  #   - Base case
  #   - Multiple trkseg nodes in the same file
  #   - 0 and 1 trkpt nodes in a trkseg node
  #   - time node presence
  NULL
})

context("Haversine distance formula")

test_that("d is real for edge cases", {
  # d is only real for 0 <= h <= 1
  # Equal points: h = 1
  expect_equal(get_haversine_distance(0, 0, 0, 0, 1), 0)
  # Antipodal points: h = 1
  expect_equal(get_haversine_distance(-90, -90, 90, 90, 1), pi)
})
