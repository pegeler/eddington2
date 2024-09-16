#include <stdlib.h>

#include "vector.h"

void v_cleanup(Vector v) {
  free(v.data);
}
