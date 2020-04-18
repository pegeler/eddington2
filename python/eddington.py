#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""Compute the Eddington number for cycling"""
from __future__ import print_function
from collections import Counter


class Eddington:
    """A class for tracking Eddington Number for Cycling"""

    def __init__(self, rides=None):
        self.above = 0
        self.current = 0
        self.cumulative = []
        self.H = Counter()
        if rides:
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


def E_num(rides):
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


def E_cum(rides):
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


if __name__ == '__main__':
    import argparse
    from sys import stdin
    
    parser = argparse.ArgumentParser(
                        prog='python3 -m eddington',
                        description='Compute the Eddington number for cycling.')
    parser.add_argument('files', nargs='*',
                        help='file(s) containing ride lengths')
    parser.add_argument('-c', '--cumulative', action='store_true',
                        help='print the cumulative Eddington number')
    
    args = parser.parse_args()
    
    rides = []
    if args.files:
        for f in args.files:
            rides.extend(float(i.strip()) for i in open(f).readlines())
    else:
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
