#!/bin/bash
E=0

for r in $(sort -rg $1 | sed 's/\..*//'); do

  if [ $r -ge $E ]; then
  
    ((E++))
    
  else
  
    break
    
  fi
  
done

echo $E
