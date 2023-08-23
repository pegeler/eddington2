from sys import argv

from pyspark.sql import SparkSession
from pyspark.sql import functions
from pyspark.sql.window import Window


def main():
    spark = SparkSession.builder.appName("EddingtonSpark").getOrCreate()
    filename = argv[1]

    df = (spark
        .read
        .format("csv")
        .option("header", "true")
        .option("inferSchema", "true")
        .load(filename))

    window_spec = (functions.row_number()
        .over(Window.orderBy(functions.desc("sum_len"))))

    result = (df
        .groupBy("ride_date")
        .agg(functions.sum("ride_length").alias("sum_len"))
        .withColumn("row_num", window_spec)
        .where("sum_len >= row_num")
        .agg(functions.max("row_num").alias("eddington_number")))

    result.show()


if __name__ == "__main__":
    main()
