context("GPX file processing")

test_that("GPX file base case works", {
  d <- read_gpx("base-case.gpx")
  expect_equal(d$date, as.Date("2023-12-01"))
  expect_equal(d$distance, 3., tolerance = 0.01)
})

test_that("Multiple trkseg nodes in same file are processed correctly", {
  d <- read_gpx("multi-trkseg.gpx")
  expect_equal(d$date, c(as.Date("2023-12-01"), as.Date("2023-12-02")))
  expect_equal(d$distance, c(3., 1.), tolerance = 0.01)
})

test_that("trkseg nodes with 0 or 1 trkpt nodes result in distance of 0", {
  d <- read_gpx("zero-node-trkseg.gpx")
  expect_equal(d$date, as.Date("2023-12-01"))
  expect_equal(d$distance, 0.)

  d <- read_gpx("one-node-trkseg.gpx")
  expect_equal(d$date, as.Date("2023-12-01"))
  expect_equal(d$distance, 0.)
})

test_that("correctly handles time nodes", {
  d <- read_gpx("no-time-nodes.gpx")
  expect_equal(is.na(d$date))
  expect_equal(d$distance, 3., tolerance = 0.01)
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

  d <- get_haversine_distance(w39[1], w39[2], w59[1], w59[2], "miles")
  expect_equal(d, 1., tolerance = 0.01)

  d <- get_haversine_distance(w39[1], w39[2], w59[1], w59[2], "kilometers")
  expect_equal(d, 1.62, tolerance = 0.01)

})
