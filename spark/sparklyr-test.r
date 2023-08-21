#!/usr/bin/env Rscript

suppressPackageStartupMessages({
  library(sparklyr)
  library(dplyr)
  library(dbplyr)
  library(eddington)
})

# Connect to the Spark session and load data
sc <- spark_connect("local")
tbl_rides <- copy_to(sc, rides)

# Computing Eddington Number using dplyr interface
tbl_rides |>
  group_by(ride_date) |>
  summarize(daily_length = sum(ride_length, na.rm = TRUE)) |>
  window_order(desc(daily_length)) |>
  mutate(rank = row_number()) |>
  filter(daily_length >= rank) |>
  summarize(E = max(rank, na.rm = TRUE)) |>
  collect() |>
  pull() |>
  cat()

# Disconnect Spark session
spark_disconnect(sc)

