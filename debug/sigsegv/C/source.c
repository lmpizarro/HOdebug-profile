/* 
 * This source code was implemented as example for a debugging session of the 
 * Workshop on Advanced Techniques for Scientific Programming and Management of Open Source Software Packages. 
 * The code impements an inefficient version of a matrix multiplication such as C = A * AT.
 * Where A, AT and C are square matrix of dimension SIZE x SIZE.
 * A is the input matrix while C is te output matrix. With in the function mat_Tmat_mul a temporary AT matrix is defined.
 * Run the program compiling both version on your workstation as reported
 *
 *     1) gcc source.c -o small.x -D__SMALL -O0 -g
 *
 *     2) gcc source.c -o big.x -O0 -g 
 *
 * The case number 2) is expected to crash with a "Segmentation fault" generating a core file. 
 * Try to analize the core file using gdb to identify where the execution broke. 
 * Print the content of local variable to understand the source of the error.
 *
 * The command to anylize core file is as follows:
 *
 * $gdb ./[EXE].x core.[PID]
 *
 * Please, use the gdb on-line manual or publicly available documentation on web for details on gdb sintax.
 *
 */ 


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef __SMALL
#define SIZE 100
#else 
#define SIZE 5000
#endif

void mat_Tmat_mul( float * A, float * C ){

  int i, j, k;
  float * temp;

  temp = (float *) malloc( SIZE * SIZE * sizeof(float) );

  for( i = 0; i < SIZE; i++ )
    for( j = 0; j < SIZE; j++ )
      temp[ j + i * SIZE ] = A[ ( i * SIZE ) + j ];

 
  for( i = 0; i < SIZE; i++ )
    for( j = 0; j < SIZE; j++ )
      for( k = 0; k < SIZE; k++ )
	C[ ( i * SIZE ) + j ] += A[ ( i * SIZE ) + k ] * temp[ j + i * SIZE ] ;

 
  free(temp);
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
  
  mat_Tmat_mul( A, C );
  
  free( A );
  free( C );
  
  return 0;
}
  
