#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""Compute the Eddington number for cycling"""


# https://docs.python.org/3/library/stdtypes.html#dict
class Counter(dict):
    def __missing__(self, key):
        return 0


class Eddington:
    """A class for tracking Eddington Number for Cycling"""

    def __init__(self, rides):
        self.above = 0
        self.current = 0
        self.cumulative = []
        self.H = Counter()
        self.update(rides)

    def update(self, rides):
        for r in rides:
            ride = int(r)

            if ride > self.current:
                self.above += 1
                self.H[ride] += 1

                if self.above > self.current:
                    self.current += 1
                    self.above -= self.H.pop(self.current, 0)

            self.cumulative.append(self.current)

    def next(self):
        return self.current + 1 - self.above

    def required(self, target):
        if self.current >= target:
            return 0
        else:
            return target - sum(v for k, v in self.H.items() if k >= target)


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
