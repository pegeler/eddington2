package bike.eddington

import scala.collection.mutable

class Eddington(distances: Option[Seq[Int]]) {
  private val hashmap = mutable.HashMap.empty[Int, Int].withDefaultValue(0)
  private val _cumulative = mutable.ListBuffer.empty[Int]
  private var _current = 0
  private var _above = 0
  distances match
    case Some(d) => update(d)
    case None =>

  def current: Int = _current
  def cumulative: Seq[Int] = _cumulative.toSeq
  def next: Int = _current + 1 - _above

  def update(distances: Iterable[Int]): Unit =
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
}
