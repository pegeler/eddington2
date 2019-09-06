BEGIN{

  E=0
  above=0

}

{

ride = int($1)

if (ride > E) {
  above++
  H[ride]++
}

if (above > E) {
  E++
  if (E in H) above -= H[E]
}

}

END{

  print E
 
}