import argparse
from sys import stdin
from .eddington import E_num, E_cum

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
        if ride: rides.append(float(ride))
        else: break

if args.cumulative:
    print(*E_cum(rides), sep = '\n')
else:
    print(E_num(rides))
