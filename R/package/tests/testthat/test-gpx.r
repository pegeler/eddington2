context("GPX file processing")

test_that("...", {
  # Base case


  # Multiple trkseg nodes in the same file


  # 0 and 1 trkpt nodes in a trkseg node


  # time node presence


})

context("Haversine distance formula")

test_that("d is real for edge cases", {
  # d is only real for 0 <= h <= 1
  # Equal points: h = 1
  expect_equal(eddington:::get_haversine_distance_(0, 0, 0, 0, 1), 0)
  # Antipodal points: h = 1
  expect_equal(eddington:::get_haversine_distance_(-90, -90, 90, 90, 1), pi)
})

test_that("one mile is one mile", {
  # In NYC, 20 blocks == 1 mile
  w59 <- c(40.76684156255418, -73.97908243833855)  # W 59th St and 7th Ave
  w39 <- c(40.75406905512651, -73.98830604245481)  # W 39th St and 7th Ave

  # TODO: update with new units API
  d <- get_haversine_distance(w39[1], w39[2], w59[1], w59[2], "miles")
  expect_equal(d, 1., tolerance = 0.01)

  d <- get_haversine_distance(w39[1], w39[2], w59[1], w59[2], "kilometers")
  expect_equal(d, 1.62, tolerance = 0.01)

})
