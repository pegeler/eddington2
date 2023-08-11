import eddington

class TestEddington:

    def testInit(self):
        rides = [3.3] * 3
        e = eddington.Eddington(rides)

        assert e.current == 3
        assert e.cumulative == [1, 2, 3]

    def testUpdate(self):
        e = eddington.Eddington()

        # Nothing entered yet
        assert e.current == 0
        assert e.cumulative == []

        # Include some rides
        e.update([3.3, 2.2, 1.1])
        assert e.current == 2
        assert e.cumulative == [1, 2, 2]

        # Add more rides
        e.update([3.3, 3.3])
        assert e.current == 3
        assert e.cumulative == [1, 2, 2, 2, 3]

    def testNext(self):
        # Next number is 3 and two 3's have already been accumulated
        e = eddington.Eddington([3.3] * 2)
        assert e.next() == 1

        # Next number is 3 and no 3's have already been accumulated
        e = eddington.Eddington([2.2] * 2)
        assert e.next() == 3

    def testRequired(self):
        # Next number is 3 and two 3's have already been accumulated
        e = eddington.Eddington([3.3] * 2)
        assert e.required(3) == 1

        # Next number is 3 and no 3's have already been accumulated
        e = eddington.Eddington([2.2] * 2)
        assert e.required(3) == 3

        # Next number is 3, but we are checking on 4
        e = eddington.Eddington([2.2, 2.2, 4.4])
        assert e.required(4) == 3



def test_free_functions():
    rides = []

    # Empty
    assert eddington.E_num(rides) == 0
    assert list(eddington.E_cum(rides)) == []

    # Populate with some rides
    rides.extend([3.3, 2.2, 1.1])
    assert eddington.E_num(rides) == 2
    assert list(eddington.E_cum(rides)) == [1, 2, 2]

    # Add more rides
    rides.extend([3.3, 3.3])
    assert eddington.E_num(rides) == 3
    assert list(eddington.E_cum(rides)) == [1, 2, 2, 2, 3]
