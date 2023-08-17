#include "primes.h"

int is_prime(uint32 n) {
  if (n <= 3)
    return n > 1;

  if ((n & 1) == 0 || n % 3 == 0)
    return 0;

  for (uint32 i = 5, stop = ceil(sqrt(n)); i <= stop; i += 6)
    if (n % i == 0 || n % (i + 2) == 0)
      return 0;

  return 1;
}

uint32 next_prime(uint32 n) {
  while (!is_prime(++n))
    ;
  return n;
}
