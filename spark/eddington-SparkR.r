#!/usr/bin/env Rscript

library(SparkR, lib.loc = c(file.path(Sys.getenv("SPARK_HOME"), "R", "lib")))
sparkR.session(master = "local[*]", sparkConfig = list(spark.driver.memory = "2g"))

file_path <- commandArgs(TRUE)

read.df(file_path, "csv", header = "true", inferSchema = "true") |>
  groupBy(column("ride_date")) |>
  agg(sum(column("ride_length")) |> alias("sum_len")) |>
  mutate(
    "row_num" = row_number() |> over(windowOrderBy(column("sum_len") |> desc()))
  ) |>
  where("sum_len >= row_num") |>
  agg(max(column("row_num")) |> alias("eddington_number")) |>
  collect() |>
  _$eddington_number |>
  cat("\n", sep = "")
