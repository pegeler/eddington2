# Setting up reference values ---------------------------------------------

# In NYC, 20 blocks == 1 mile and the grid is diagonal. That makes it the
# perfect location for testing the haversine distance formula.
w59_coords <- list(lat=40.76684156255418, long=-73.97908243833855)  # W 59th St / 7th Ave
w39_coords <- list(lat=40.75406905512651, long=-73.98830604245481)  # W 39th St / 7th Ave

ave_7_distance <- get_haversine_distance(
  w39_coords$lat, w39_coords$long, w59_coords$lat, w59_coords$long, "miles"
)

park_ave_coords <- list(
  list(lat=40.735337983655434, long=-73.98973648773142),  # E 15 St / Park Ave
  list(lat=40.74772623378332, long=-73.98066078090876),   # E 35 St / Park Ave
  list(lat=40.76026319186414, long=-73.97149360922498),   # E 55 St / Park Ave
  list(lat=40.77301604875587, long=-73.96217737679450)    # E 75 St / Park Ave
)

park_ave_distance <- sum(
  sapply(
    seq_along(park_ave_coords)[-1],
    \(i) get_haversine_distance(
      park_ave_coords[[i]]$lat,
      park_ave_coords[[i]]$long,
      park_ave_coords[[i - 1]]$lat,
      park_ave_coords[[i - 1]]$long,
      "miles"
    )
  )
)

context("Haversine distance formula")

test_that("one mile is one mile", {
  d <- get_haversine_distance(
    w39_coords$lat,
    w39_coords$long,
    w59_coords$lat,
    w59_coords$long,
    "miles"
  )
  expect_equal(d, 1., tolerance = 0.01)

  d <- get_haversine_distance(
    w39_coords$lat,
    w39_coords$long,
    w59_coords$lat,
    w59_coords$long,
    "kilometers"
  )
  expect_equal(d, 1.62, tolerance = 0.01)

})

test_that("d is real for edge cases", {
  # d is only real for 0 <= h <= 1
  # Equal points: h = 1
  expect_equal(eddington:::get_haversine_distance_(0, 0, 0, 0, 1), 0)
  # Antipodal points: h = 1
  expect_equal(eddington:::get_haversine_distance_(-90, -90, 90, 90, 1), pi)
})


context("GPX file processing")

test_that("GPX file base case works", {
  d <- read_gpx("base-case.gpx")
  expect_equal(d$date, as.Date("2023-12-01"))
  expect_equal(d$distance, park_ave_distance)
})

test_that("Multiple trkseg nodes in same file are processed correctly", {
  d <- read_gpx("multi-trkseg.gpx")
  expect_equal(d$date, c(as.Date("2023-12-01"), rep(as.Date("2023-12-02"), 2)))
  expect_equal(sum(d$distance), sum(ave_7_distance, park_ave_distance))
})

test_that("trkseg nodes with 0 or 1 trkpt nodes result in distance of 0", {
  d <- read_gpx("zero-node-trkseg.gpx")
  expect_true(is.na(d$date))
  expect_equal(d$distance, 0.)

  d <- read_gpx("one-node-trkseg.gpx")
  expect_equal(d$date, as.Date("2023-12-01"))
  expect_equal(d$distance, 0.)
})

test_that("Files with missing trkseg nodes return empty data frame", {
  d <- read_gpx("no-trkseg.gpx")
  expect_equal(nrow(d), 0L)
  expect_equal(names(d), c("date", "distance"))
})

test_that("correctly handles time nodes", {
  d <- read_gpx("no-time-nodes.gpx")
  expect_true(is.na(d$date))
  expect_equal(d$distance, park_ave_distance)
})
