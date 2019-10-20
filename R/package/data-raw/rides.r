set.seed(2018)
date_range <- seq(as.Date("2009-01-01"), as.Date("2009-12-31"), by = "day")
debug <- if(interactive()) rstudioapi::showQuestion(
  "Debug", "Do you want to see debug data?", "Yes", "No")

# ** Long Rides --------------------------------------------------------------
n <- 50
ride_lengths <- round(rgamma(n, shape = 2, scale = 10),2)

# Weight months and dates based on weekend and seasonality
wkday <- as.POSIXlt(date_range)$wday + 1
wkday_wts <- c(u = 9, m = 1,t = 1, w = 2, r = 2, f = 5, s = 10)

mon <- as.POSIXlt(date_range)$mon + 1
mon_wts <- c(
  '1' = 1, '2' = 1, '3' = 2,
  '4' = 3, '5' = 6, '6' = 20,
  '7' = 20, '8' = 20, '9' = 15,
  '10' = 10, '11' = 4, '12' = 1
)

ride_dates <- sample(
  date_range,
  n,
  replace = TRUE,
  wkday_wts[wkday] * mon_wts[mon]
)

# Combine into a data.frame
rides <- data.frame(
  "ride_date" = ride_dates,
  "ride_length" = ride_lengths
)

# ** Short rides ---------------------------------------------------------
n <- 200
ride_lengths <- round(rnorm(n, 12, 3), 2)

wkday_wts <- c(u = 2, m = 10,t = 10, w = 10, r = 10, f = 5, s = 2)
short_wts <- setNames(wkday_wts[wkday], date_range)

ride_dates <- sample(
  date_range,
  n,
  replace = TRUE,
  short_wts * ifelse(names(short_wts) %in% as.character(ride_dates), 0.1, 1)
)

short_rides <- data.frame(
  "ride_date" = ride_dates,
  "ride_length" = ride_lengths
)

# Combining long and short rides --------------------------------------------
rides <- rbind(rides, short_rides)
rides <- rides[order(rides$ride_date),]
row.names(rides) <- NULL

# Check ----------------------------------------------------------------------
if (debug) {

  library(dplyr)
  check <- rides %>%
    group_by(ride_date) %>%
    summarize(n = n(), ttl_len = sum(ride_length)) %>%
    arrange(desc(ttl_len))

  View(check)
  plot(check$ride_date, check$ttl_len, type = "h")
  hist(ride_dates, breaks = "day")
  range(rides$ride_length)

}

# Saving to file ------------------------------------------------------------
usethis::use_data(rides, overwrite = TRUE)
