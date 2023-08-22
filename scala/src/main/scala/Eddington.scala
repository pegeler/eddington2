package bike.eddington

import scala.collection.mutable


/** Computes the Eddington number using Algorithm A */
def get_eddington_number(distances: Seq[Int]): Int =
  distances
    .sorted(Ordering[Int].reverse)
    .foldLeft(0)((e, current) => if (current > e) e + 1 else e)


/** Determine whether the dataset satisfies a candidate Eddington number */
def is_satisfied(distances: Seq[Int], candidate: Int): Boolean =
  distances.size >= candidate && distances.count(_ >= candidate) >= candidate


/** Get the number of distances at or above the candidate in order to satisfy the candidate Eddington Number */
def get_required(distances: Seq[Int], candidate: Int): Int =
  (candidate - distances.count(_ >= candidate)).max(0)


/** A stateful class for tracking the Eddington number
 *
 * @param distances An optional sequence of distances used to initialize the class.
 */
class Eddington(distances: Option[Seq[Int]]) {
  private val hashmap = mutable.HashMap.empty[Int, Int].withDefaultValue(0)
  private val _cumulative = mutable.ListBuffer.empty[Int]
  private var _current = 0
  private var _above = 0
  distances match
    case Some(d) => update(d)
    case None =>

  /** The current Eddington number */
  def current: Int = _current

  /** The cumulative Eddington number */
  def cumulative: Seq[Int] = _cumulative.toSeq

  /** The minimum number of entries required to increment the Eddington number */
  def next: Int = _current + 1 - _above

  /** Update the instance with additional data
   *
   * @param distances A sequence of distances to add to the data.
   */
  def update(distances: Seq[Int]): Unit =
    for (dist <- distances)
      if (dist > _current)
        _above += 1
        hashmap(dist) += 1
        if (_above > _current)
          _current += 1
          hashmap.remove(_current) match
            case Some(i) => _above -= i
            case None =>
      _cumulative += _current

  /** Get the number of additional distances required to achieve the target Eddington number
   *
   * @param target The target Eddington number.
   */
  def required(target: Int): Int =
    target match
      case t if t <= _current => 0
      case t if t == _current + 1 => next
      case t => t - hashmap.filter(_._1 >= t).foldLeft(0)(_ + _._2)
}
