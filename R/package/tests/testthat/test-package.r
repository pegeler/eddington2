context("Testing output")

simdata <- readRDS("simdata.rds")
refdata <- readRDS("refdata.rds")

E_ref <- refdata[length(refdata)]

test_that("E_num works",{
  expect_identical(E_num(simdata), E_ref)
})

test_that("E_cum works",{
  expect_identical(E_cum(simdata), refdata)
})


test_that("E_sat works",{
  expect_true(E_sat(simdata, E_ref))
  expect_false(E_sat(simdata, E_ref + 1L))
})

test_that("E_next works",{
  x <- E_next(simdata)
  ref_next <- x$E + 1L
  enough_rides <- c(simdata, rep(ref_next, x$req))
  not_enough_rides <- c(simdata, rep(ref_next, x$req - 1))

  expect_true(E_sat(enough_rides, ref_next))
  expect_false(E_sat(not_enough_rides, ref_next))
})

test_that("E_req works",{
  x <- E_next(simdata)
  ref_next <- x$E + 1L
  expect_equal(E_req(simdata, ref_next), x$req)
})

context("Testing R6 class")

test_that("Eddington class works",{ # WIP

  e <- Eddington$new(simdata)

  # current
  expect_equal(e$current, E_ref)

  # cumulative
  expect_equal(e$cumulative, E_cum(simdata))

  # Number to next and target
  expect_equal(e$getNumberToNext, E_next(simdata)$req)
  expect_equal(e$getNumberToTarget(27), E_req(simdata, 27))

  # satisfied
  expect_true(e$isSatisfied(e$current))
  expect_true(e$isSatisfied(e$current - 1L))
  expect_false(e$isSatisfied(e$current + 1L))

  # n
  expect_equal(e$n, length(simdata))

  # Get hashmap
  hashmap <- e$hashmap
  expect_s3_class(e$hashmap, "data.frame")
  expect_true(all(hashmap[["length"]] > e$current))
  expect_true(all(names(hashmap) == c("length", "count")))
  expect_true(nrow(hashmap) > 0)

  # clone is disabled
  expect_false(exists("clone", envir = e))

  # update
  e <- Eddington$new(simdata)
  e$update(rep(25, 10))
  expect_equal(e$cumulative, E_cum(c(simdata, rep(25, 10))))

})
