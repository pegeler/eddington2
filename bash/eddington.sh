#!/bin/bash
E=0

for r in $(sed 's/\..*//' $1 | sort -rn); do
  
  test $r -ge $E && ((++E)) || break
  
done

echo $E
