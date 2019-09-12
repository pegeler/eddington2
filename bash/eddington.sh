#!/bin/bash
E=0
above=0
H=()

for r in $(sed 's/\..*//' $1); do

  if [ $r -gt $E ]; then
    ((above++))
    ((H[r]++))
  fi
  
  if [ $above -gt $E ]; then
    ((E++))
    ((above-=H[E]))
    unset H[$E]
  fi

done

echo $E
