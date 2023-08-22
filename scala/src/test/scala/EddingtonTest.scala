package bike.eddington

import org.scalatest.funsuite.AnyFunSuite
import org.scalatest.verbs.ShouldVerb

val test_data = Seq(1, 3, 3)

class EddingtonTest extends AnyFunSuite {
  test("Eddington class works") {
    val e = Eddington(Option(test_data))
    assert(e.current === 2)
    assert(e.cumulative === Seq(1, 1, 2))
    assert(e.next === 1)
    assert(e.required(2) === 0)
    assert(e.required(3) === 1)
    assert(e.required(4) === 4)

    e.update(Seq(4, 4, 4, 4))
    assert(e.current === 4)
    assert(e.cumulative === Seq(1, 1, 2, 3, 3, 3, 4))
  }

  test("Algorithm A") {
    assert(get_eddington_number(test_data) === 2)
  }

  test("is_satisfied") {
    assert(is_satisfied(test_data, 2))
    assert(!is_satisfied(test_data, 3))
  }

  test("get_required") {
    assert(get_required(test_data, 2) === 0)
    assert(get_required(test_data, 3) === 1)
    assert(get_required(test_data, 4) === 4)
  }
}
