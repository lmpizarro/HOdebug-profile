#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/time.h>

#include "internal_profiling.h"

double seconds()
  /* Returns elepsed seconds past from the last call to timer rest */
{

    struct timeval tmp;
    double sec;
    gettimeofday( &tmp, (struct timezone *)0 );
    sec = tmp.tv_sec + ((double)tmp.tv_usec);
    return sec;
}
