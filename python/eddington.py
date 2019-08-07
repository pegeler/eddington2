#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""Compute the Eddington Number for cycling

Created on Sun Sep 23 14:43:48 2018

Example:

  This is an example that uses a random ride generator::

    import random

    n = 100

    x = [random.gammavariate(2,10) for i in range(n)]

    Eddington_number(x)

  You may also use this module from the command line::

    $ ./eddington.py 1 2 3 0 0 15 3

"""


def E_num(rides) -> int:
  """Eddington Number for Cycling

  :param rides: A list of mileages for each ride.
  :type rides: list
  :rtype: integer
  :returns: The Eddington number, E, for the data.
  """

  # Test that the list is not empty
  if not rides:
    return 0

  for E, ride in enumerate(sorted(rides, reverse = True), 1):
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
    
  return E;



if __name__ == "__main__":
  import sys

  E = E_num([float(i) for i in sys.argv[1:]])

  print("The Eddington number is: % 3i" % E)
