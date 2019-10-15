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


def E_num(rides) -> int:
    """Eddington Number for Cycling

    :param rides: A list of mileages for each ride.
    :type rides: list
    :rtype: integer
    :returns: The Eddington number, E, for the data.
    """

    n, E, above = len(rides), 0, 0
    H = [0 for x in range(n)]

    for i in range(n):
        ride = int(rides[i])

        if ride > E:
            above += 1

            if ride < n:
                H[ride] += 1

            if above > E:
                E += 1
                above -= H[E]

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


def __main__():
    import argparse

    parser = argparse.ArgumentParser(
                        description='Compute the Eddington number for cycling.')
    parser.add_argument('file', nargs='?',
                        help='file containing ride lengths')
    parser.add_argument('-c', '--cumulative', action='store_true',
                        help='print the cumulative Eddington number')

    args = parser.parse_args()

    if args.file:
        with open(args.file) as f:
            rides = [float(i.strip()) for i in f.readlines()]
    else:
        from sys import stdin

        rides = []

        for line in stdin:
            ride = line.strip()

            if ride:
                rides.append(float(ride))
            else:
                break

    if args.cumulative:
        print(*E_cum(rides), sep = '\n')
    else:
        print(E_num(rides))


if __name__ == "__main__":
    __main__()
