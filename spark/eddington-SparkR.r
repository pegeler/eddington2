#!/usr/bin/env Rscript

library(SparkR, lib.loc = c(file.path(Sys.getenv("SPARK_HOME"), "R", "lib")))
sparkR.session(master = "local[*]", sparkConfig = list(spark.driver.memory = "2g"))

file_path <- commandArgs(TRUE)

df <- read.df(
  file_path,
  "csv",
  header = "true",
  inferSchema = "true"
  )

ws <- windowOrderBy(desc(column("sum_len")))

df |>
  groupBy(column("ride_date")) |>
  agg(sum(column("ride_length")) |> alias("sum_len")) |>
  mutate("row_num" = over(row_number(), ws)) |>
  where("sum_len >= row_num") |>
  agg(max(column("row_num")) |> alias("eddington_number")) |>
  collect()
