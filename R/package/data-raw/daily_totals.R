## code to prepare `daily_totals` dataset goes here
library(dplyr)

data(rides, package = "eddington")

daily_totals <- rides |>
  group_by(ride_date) |>
  summarize(total_length = sum(ride_length))

usethis::use_data(daily_totals, overwrite = TRUE)
