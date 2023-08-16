package bike.eddington

import scala.io.Source
import scala.math.Ordering
import scala.util.Using
import scala.util.{Try, Success, Failure}

import bike.eddington.Eddington


def read_lines(filename: String): Try[Seq[Int]] =
  Using(Source.fromFile(filename)) {
    _
      .getLines
      .map(_.toDouble.toInt)
      .toSeq
  }


def get_eddington_number(rides: Seq[Int]): Int =
  rides
    .sorted(Ordering[Int].reverse)
    .foldLeft(0)((e, current) => if (current > e) e + 1 else e)


@main
def main(filename: String): Unit =
  val result = read_lines(filename)

  // Using a free function with Algorithm A
  println("Algorithm A")
  result match
    case Success(rides) => println(get_eddington_number(rides))
    case Failure(exception) => println(s"Failed: $exception")

  // Using the Eddington class with Algorithm B
  val e = Eddington(result.toOption)
  println("Algorithm B")
  println(e.current)
