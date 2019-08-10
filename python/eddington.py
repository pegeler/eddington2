#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""Compute the Eddington Number for cycling

Created on Sun Sep 23 14:43:48 2018

Example:

    This is an example that uses a random ride generator::

        import random
        import eddington

        n = 100

        x = [random.gammavariate(2,10) for i in range(n)]

        eddington.E_num(x)

    You may also use this module from the command line. It reads ride data
    from file and outputs the summary Eddington number.::

        $ ./eddington.py ../mock-data/rides.dat

"""


def E_num(rides) -> int:
    """Eddington Number for Cycling

    :param rides: A list of mileages for each ride.
    :type rides: list
    :rtype: integer
    :returns: The Eddington number, E, for the data.
    """

    if not rides:
        return 0

    for E, ride in enumerate(sorted(rides, reverse=True), 1):
        if ride < E:
            E -= 1
            break

    return E


def E_cum(rides) -> list:
    """Cumulative Eddington Number for Cycling

    :param rides: A list of mileages for each ride.
    :type rides: list
    :rtype: list
    :returns: The Eddington number, E, for each element in the data.
    """

    n = len(rides)
    running, above = 0, 0
    E = []
    H = [0 for x in range(n)]

    for i in range(n):
        ride = int(rides[i])

        if ride > running:
            above += 1

            if ride < n:
                H[ride] += 1

            if above > running:
                running += 1
                above -= H[running]

        E.append(running)

    return E


if __name__ == "__main__":
    import sys

    with open(sys.argv[1]) as f:
        rides = f.readlines()

    E = E_num([float(i.strip()) for i in rides])

    print("The Eddington number is: % 3i" % E)
