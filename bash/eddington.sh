#!/bin/bash
E=0

for r in $(sort -rg $1 | sed 's/\..*//'); do
  
  test $r -ge $E && ((++E)) || break
  
done

echo $E
