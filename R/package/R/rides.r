#' A year of simulated bicycle ride mileages
#'
#' Simulated dates and distances of rides occurring in 2009.
#'
#' The dataset contains a total of 3,419 miles spread across 178
#' unique days. The Eddington number for the year was 29.
#'
#' @format A data frame with 250 rows and 2 variables:
#' \describe{
#'   \item{ride_date}{date the ride occurred}
#'   \item{ride_length}{the length in miles}
#' }
#' @seealso [daily_totals]
"rides"


#' A year of simulated bicycle ride mileages, aggregated by day
#'
#' Simulated dates and distances of rides occurring in 2009. This is an
#' aggregation of the \code{\link{rides}} dataset by day.
#'
#' The dataset contains a total of 3,419 miles spread across 178
#' unique days. The Eddington number for the year was 29.
#'
#' @format A data frame with 178 rows and 2 variables:
#' \describe{
#'   \item{ride_date}{date the ride occurred}
#'   \item{total_length}{the total length in miles for each day}
#' }
#' @seealso [rides]
"daily_totals"
