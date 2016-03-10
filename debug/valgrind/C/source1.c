/* 
 * This source code was implemented as example for a debugging session of the 
 * Workshop on Advanced Techniques for Scientific Programming and Management of Open Source Software Packages. 
 * The code impements an inefficient version of a matrix multiplication such as C = A * AT.
 * Where A, AT and C are square matrix of dimension SIZE x SIZE.
 * A is the input matrix while C is te output matrix. With in the function mat_Tmat_mul a temporary AT matrix is defined.
 * The program contains an infite loop calling the function mat_Tmat_mul
 * Run the program compiling the proposed version on your workstation as reported:
 *
 *     1) gcc source1.c -O3 -g; ./a.out
 *
 * Open an other shell and check the memory consumption. 
 * Run the debug using valgrind (possibly at reduced SIZE). 
 * Please, use the valgrind on-line manual or publicly available documentation on web for details on valgrind sintax.
 *
 */ 


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SIZE 4

void mat_Tmat_mul( float * A, float * C ){

  int i, j, k;
  float * temp;

  temp = (float *) malloc( SIZE * SIZE * sizeof(float) );

  for( i = 0; i < SIZE; i++ )
    for( j = 0; j < SIZE; j++ )
      temp[ ( j * SIZE) + i ] = A[ ( i * SIZE ) + j ];

  for( i = 0; i < SIZE; i++ )
    for( j = 0; j < SIZE; j++ )
      for( k = 0; k < SIZE; k++ )
	C[ ( i * SIZE ) + j ] += A[ ( i * SIZE ) + k ] * temp[ ( k * SIZE ) + j ] ;
  
}

int main( int argc, char * argv[] ){
  
  int i, j;
  float * A, * C;
  
  A = (float *) malloc( SIZE * SIZE * sizeof(float) );
  C = (float *) malloc( SIZE * SIZE * sizeof(float) );
  
  for( i = 0; i < SIZE; i++ ){
    for( j = 0; j < SIZE; j++ ){
      A[ ( i * SIZE ) + j ] = ( (float) i ) / j;
    }
  }
   
  memset( C, 0, SIZE * SIZE * sizeof(float) );
  
  for(;;) mat_Tmat_mul( A, C );
  
  free( A );
  free( C );
  
  return 0;
}
