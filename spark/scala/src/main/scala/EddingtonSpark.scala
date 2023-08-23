package bike.eddington.spark

import org.apache.spark.sql.SparkSession
import org.apache.spark.sql.expressions.Window
import org.apache.spark.sql.functions._

object EddingtonSpark {
  def main(args: Array[String]): Unit = {
    val spark = SparkSession
      .builder
      .appName("EddingtonSpark")
      .getOrCreate()

    val filename = args(0)
    val opts = Map(
      "header" -> "true",
      "inferSchema" -> "true"
    )

    val df = spark
      .read
      .format("csv")
      .options(opts)
      .load(filename)

    val result = df
      .groupBy("ride_date")
      .agg(sum("ride_length") as "sum_len")
      .withColumn("row_num", row_number().over(Window.orderBy(desc("sum_len"))))
      .where("sum_len >= row_num")
      .agg(max("row_num") as "eddington_number")

    println(result.collect().last.getInt(0))
  }
}
