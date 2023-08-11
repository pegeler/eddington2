#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Tools to compute the Eddington number for cycling.

Can compute both summary Eddington number and a vector of cumulative
statistics in linear asymptotic time, with relatively low memory overhead.
The `E_cum` function uses a variant of the algorithm that is a "streaming"
algorithm, which can track the cumulative Eddington number over inputs of
unknown size.
"""
import argparse
import sys

from collections import defaultdict
from collections.abc import Iterable
from collections.abc import Iterator
from typing import Optional


class Eddington:
    """
    A class for tracking Eddington Number for cycling.

    :ivar int current: The current Eddington number.
    :ivar list[int] cumulative: A list of Eddington numbers. Each element
            represents the Eddington number for the dataset up to that point.
    """

    def __init__(self, distances: Optional[Iterable[float]] = None):
        self.current = 0
        self.cumulative = []
        self._above = 0
        self._dist_table = defaultdict(int)
        if distances is not None:
            self.update(distances)

    def update(self, distances: Iterable[float]):
        """
        Update the current and cumulative Eddington number statistics with
        new data.
        """
        for dist in map(int, distances):
            if dist > self.current:
                self._above += 1
                self._dist_table[dist] += 1

                if self._above > self.current:
                    self.current += 1
                    self._above -= self._dist_table.pop(self.current, 0)

            self.cumulative.append(self.current)

    def next(self) -> int:
        """
        Report how many distances must be accumulated above the current
        Eddington number to advance to the next number.
        """
        return self.current + 1 - self._above

    def required(self, target: int) -> int:
        """
        Report how many distances must be accumulated at or above the `target`
        Eddington number to achieve that number, given the current state.
        """
        if target <= self.current:
            return 0
        if target == self.current + 1:
            return self.next()
        above = sum(v for k, v in self._dist_table.items() if k >= target)
        return target - above


def E_num(distances: list[float]) -> int:
    """
    Compute the Eddington Number for a dataset.

    :param distances: A list of distances for each day.
    :return: The Eddington number, E, for the data.
    """
    eddington_number = 0
    n_above = 0
    dist_table = defaultdict(int)

    for dist in map(int, distances):
        if dist > eddington_number:
            n_above += 1

            if dist < len(distances):
                # Optimization. We don't need to track distances in the
                # distance table that are greater than the length of the
                # dataset since the Eddington number can never exceed it.
                dist_table[dist] += 1

            if n_above > eddington_number:
                eddington_number += 1
                n_above -= dist_table.pop(eddington_number, 0)

    return eddington_number


def E_cum(distances: Iterable[float]) -> Iterator[int]:
    """
    Compute the cumulative Eddington Number for cycling.

    :param Iterable distances: An iterable of distances for each day.
    :returns: The Eddington number, E, for each element in the data.
    """
    current = 0
    n_above = 0
    dist_table = defaultdict(int)

    for dist in map(int, distances):
        if dist > current:
            n_above += 1
            dist_table[dist] += 1
            if n_above > current:
                current += 1
                n_above -= dist_table.pop(current, 0)

        yield current


def parse_args(argv=None):
    parser = argparse.ArgumentParser(
        prog='python3 -m eddington',
        description='Compute the Eddington number for cycling.')
    parser.add_argument(
        'files',
        nargs='*',
        help='file(s) containing ride lengths')
    parser.add_argument(
        '-c', '--cumulative',
        action='store_true',
        help='print the cumulative Eddington number')

    return parser.parse_args(argv)


def get_distances_from_files(files):
    for f in files:
        with open(f, 'rt') as fh:
            for line in fh:
                yield float(line)


def get_distances_from_stdin():
    for line in sys.stdin:
        if line.strip():
            yield float(line)


def main():
    args = parse_args()

    if not args.files or args.files == ['-']:
        distances = get_distances_from_stdin()
    else:
        distances = get_distances_from_files(args.files)

    if args.cumulative:
        print(*E_cum(distances), sep='\n')
    else:
        distances = list(distances)
        eddington_number = E_num(distances)
        print(eddington_number)


if __name__ == '__main__':
    main()
