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

test_that("E_req works",{

  x <- E_req(simdata)

  E_current <- x$E
  E_new <- E_current + 1L

  enough_rides <- c(simdata, rep(E_current + 1, x$req))
  not_enough_rides <- c(simdata, rep(E_current + 1, x$req - 1))

  expect_true(E_sat(enough_rides, E_new))
  expect_false(E_sat(not_enough_rides, E_new))

})