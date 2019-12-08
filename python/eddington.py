#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""Compute the Eddington number for cycling

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

    To print the cumulative Eddington number, use the -c flag.::

        $ ./eddington.py -c ../mock-data/rides.dat

"""


# https://docs.python.org/3/library/stdtypes.html#dict
class Counter(dict):
    def __missing__(self, key):
        return 0


def E_num(rides) -> int:
    """Eddington Number for Cycling

    :param rides: A list of mileages for each ride.
    :type rides: list
    :rtype: integer
    :returns: The Eddington number, E, for the data.
    """

    n, E, above = len(rides), 0, 0
    H = Counter()

    for r in rides:
        ride = int(r)

        if ride > E:
            above += 1

            if ride < n:
                H[ride] += 1

            if above > E:
                E += 1
                above -= H.pop(E, 0)

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
    H = Counter()

    for r in rides:
        ride = int(r)

        if ride > running:
            above += 1

            if ride < n:
                H[ride] += 1

            if above > running:
                running += 1
                above -= H.pop(running, 0)

        E.append(running)

    return E


def __main__():
    import argparse

    parser = argparse.ArgumentParser(
                        description='Compute the Eddington number for cycling.')
    parser.add_argument('files', nargs='*',
                        help='file(s) containing ride lengths')
    parser.add_argument('-c', '--cumulative', action='store_true',
                        help='print the cumulative Eddington number')

    args = parser.parse_args()

    rides = []
    if args.files:
        for f in args.files:
            rides.extend([float(i.strip()) for i in open(f).readlines()])
    else:
        from sys import stdin
        for line in stdin:
            if line:
                rides.append(float(line.strip()))
            else:
                break

    if args.cumulative:
        print(*E_cum(rides), sep = '\n')
    else:
        print(E_num(rides))


if __name__ == "__main__":
    __main__()
