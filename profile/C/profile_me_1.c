#include <stdlib.h>
#include <math.h>

#define SIZE 550

void first_assign(int i1, int i2, double * a, double * b, double * c )
{  
  a[i2*SIZE+i1] = a[i2*SIZE+i1] + b[i2*SIZE+i1] + c[i2*SIZE+i1];
}

void second_assign(int i1, int i2, double * a, double * b, double * c )
{  
  a[i1*SIZE+i2] = a[i1*SIZE+i2] + b[i1*SIZE+i2] + c[i1*SIZE+i2];
}

int main( int argc, char * argv[] )
{

  double a[SIZE][SIZE], b[SIZE][SIZE], c[SIZE][SIZE];

  int i, j; 
 
  for( i = 0; i < SIZE; i++ ){
    for( j = 0; j < SIZE; j++ ){

      a[i][j] = 1.0;
      b[i][j] = 2.0;
      c[i][j] = 3.0;
    }
  }

  for( i = 0; i < SIZE; i++ ){
    for( j = 0; j < SIZE; j++ ){
      first_assign(i, j, &a[0][0], &b[0][0], &c[0][0]);
    }
  }

  for( i = 0; i < SIZE; i++ ){
    for( j = 0; j < SIZE; j++ ){
      second_assign(i, j, &a[0][0], &b[0][0], &c[0][0]);
    }
  }

  return 0;
}
