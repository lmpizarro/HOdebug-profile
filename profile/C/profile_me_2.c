#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "internal_profiling.h"

int main( int argc, char * argv[] )
{

  double * a, * b, * c;
  double alpha;
  double elapsed, antes, despues;

  int i;
  
  size_t dim;
  
  dim = atoi(argv[1]);
 
  a = (double *) malloc( dim * sizeof( double ) );
  b = (double *) malloc( dim * sizeof( double ) );
  c = (double *) malloc( dim * sizeof( double ) );

  for( i = 0; i < dim; i++ ){

    a[i] = 1.0;
    b[i] = 2.0;
    c[i] = 3.0;
  }

  antes = seconds();
  for( i = 0; i < dim; i++ ){
    
    a[i] = exp( a[i] * i );
  }
  despues = seconds();

  printf ("llamada a exp() elapsed %f: microsecs \n", despues - antes);

  antes = seconds();
  for( i = 0; i <  dim; i++ ){
    
    a[i] = sqrt( a[i] * i );
  }
  despues = seconds();
  printf ("llamada a sqrt() elapsed %f: microsecs \n", despues - antes);

  antes = seconds();
  for( i = 0; i < dim; i++ ){
    
    a[i] = sin( a[i] * i );
  }
  despues = seconds();
  printf ("llamada a sin() elapsed %f: microsecs \n", despues - antes);

  alpha = 0.0;
  for( i = 0; i < dim; i++ ){
    alpha += a[i] + b[i] + c[i];
  }

  printf( "%g", alpha );

  free( a );
  free( b );
  free( c );

  return 0;
}
    
