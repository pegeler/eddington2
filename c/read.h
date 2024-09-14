#pragma once

#include <stdio.h>

#include "vector.h"

#define MAX_LEN 1000

/** Read lines from file stream and return them as an integer vector
 *
 *  @param[in] file the file stream to read from
 */
Vector read_values(FILE *file);
