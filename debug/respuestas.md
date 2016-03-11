## Various bugs



## Floating point exception

Para la solución de este problema escribí 2 Makefile
uno en fpe/, y el otro en fpe/fpe_x87_sse/. Este último
`Makefile` compila `fpe_x87_sse.c`  y genera el objeto `fpe_x87_sse_c.o`.

El `Makefile` en `fpe/` setea algunos variables que se van a usar como flags:

```
CFLAGS = -DTRAPFPE
IFLAGS = -I./fpe_x87_sse
LFLAGS = ./fpe_x87_sse/fpe_x87_sse_c.o -lm

```

* `-DTRAPFPE` requiere agregar la función `set_fpe_x87_sse_();`,
definida en el archivo `fpe_x87_sse/fpe_x87_sse.c`.  Para  que el
programa *linkee* adecuadamente se usa `LFLAGS` como se muestra.
La variable `IFLAGS` se usa para poder compilar los programas en
`fpe/` con el .h que está en la carpeta `fpe/fpe_x87_sse/`.

###  Comportamiento de los programas

#### Sin -DTRAPFE

```
$ ./test_fpe1.e 
Insert a, b 
1
0
c = inf 

```

```
$ ./test_fpe2.e 
Insert a, b 
1
0
c = 1.000000 
```

```
$ ./test_fpe3.e 
Insert a, b 
1
0
c = inf 
```


test_fpe2.e   a = 1, b = 0
respuesta:    c = 1.0   

test_fpe3.e   a = 1, b = 0
respuesta:    c = inf


#### Con -DTRAPFE

```
$ ./test_fpe1.e 
Insert a, b 
1
0
Excepción de coma flotante (`core' generado)
```


```
$./test_fpe2.e 
Insert a, b 
1
0
Excepción de coma flotante (`core' generado)

```

```
$./test_fpe3.e 
Insert a, b 
1
0
Excepción de coma flotante (`core' generado)

```

Cuando se usa la función  `set_fpe_x87_sse_();`, cuando se produce la
excepción de coma flotante, el programa genera interrumpe su ejecución
y genera un mensaje indicando el error.


## Segmentation Fault

[ulimit y sysctl](http://www.linuxhowtos.org/Tips%20and%20Tricks/ulimit.htm)
son programas que permiten poner límite a la disponibilidad
de recursos de sistema. `$ulimit -a` permite conocer el límite de los recursos.

Cuando se ejecuta el código `big.x` antes de ejectutar `$ulimit -s unlimited` 
,que no pone límites en el uso de la memoria disponible para el stack ,  
produce un error: `Violación de segmento ('core' generado)`. 

La solución con `ulimit -s ...` no es una solución en el sentido
del debugging dado que  no se elimina el error que produce el problema.

La solución del bug consiste en hacer allocación dinámica de memoria
para la matríz `temp` en la función `void mat_Tmat_mul( float * A, float * C )`.

```
  float * temp;

  temp = (float *) malloc( SIZE * SIZE * sizeof(float) );
```



## Valgrind


### Programa `source1.c`

Salida de `valgrind`:

```
$ valgrind --leak-check=full ./a.out
==11270== Memcheck, a memory error detector
==11270== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==11270== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==11270== Command: ./a.out
==11270== 
==11270== 
==11270== HEAP SUMMARY:
==11270==     in use at exit: 12,877,200 bytes in 73 blocks
==11270==   total heap usage: 73 allocs, 0 frees, 12,877,200 bytes allocated
==11270== 
==11270== 12,524,400 bytes in 71 blocks are definitely lost in loss record 3 of 3
==11270==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==11270==    by 0x400785: mat_Tmat_mul (source1.c:30)
==11270==    by 0x40064A: main (source1.c:59)
==11270== 
==11270== LEAK SUMMARY:
==11270==    definitely lost: 12,524,400 bytes in 71 blocks
==11270==    indirectly lost: 0 bytes in 0 blocks
==11270==      possibly lost: 0 bytes in 0 blocks
==11270==    still reachable: 352,800 bytes in 2 blocks
==11270==         suppressed: 0 bytes in 0 blocks
==11270== Reachable blocks (those to which a pointer was found) are not shown.
==11270== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==11270== 
==11270== For counts of detected and suppressed errors, rerun with: -v
==11270== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
Terminado

```

La subrutina `void mat_Tmat_mul( float * A, float * C )` alloca `temp`, pero
no lo libera y  produce el leak de memoria. Liberando memoria con `free()`.

Ahora se tiene:

``` 
$ valgrind --leak-check=full --show-leak-kinds=all ./a.out
==11364== Memcheck, a memory error detector
==11364== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==11364== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==11364== Command: ./a.out
==11364== 
==11364== 
==11364== HEAP SUMMARY:
==11364==     in use at exit: 529,200 bytes in 3 blocks
==11364==   total heap usage: 59 allocs, 56 frees, 10,407,600 bytes allocated
==11364== 
==11364== 176,400 bytes in 1 blocks are still reachable in loss record 1 of 3
==11364==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==11364==    by 0x4004E1: main (source1.c:48)
==11364== 
==11364== 176,400 bytes in 1 blocks are still reachable in loss record 2 of 3
==11364==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==11364==    by 0x4004EE: main (source1.c:49)
==11364== 
==11364== 176,400 bytes in 1 blocks are definitely lost in loss record 3 of 3
==11364==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==11364==    by 0x4007C5: mat_Tmat_mul (source1.c:30)
==11364==    by 0x40068A: main (source1.c:59)
==11364== 
==11364== LEAK SUMMARY:
==11364==    definitely lost: 176,400 bytes in 1 blocks
==11364==    indirectly lost: 0 bytes in 0 blocks
==11364==      possibly lost: 0 bytes in 0 blocks
==11364==    still reachable: 352,800 bytes in 2 blocks
==11364==         suppressed: 0 bytes in 0 blocks
==11364== 
==11364== For counts of detected and suppressed errors, rerun with: -v
==11364== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
Terminado

``` 
Eliminando el ciclo infinito en la línea 59, se tiene:

```
$ valgrind --leak-check=full --show-leak-kinds=all ./a.out
==11416== Memcheck, a memory error detector
==11416== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==11416== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==11416== Command: ./a.out
==11416== 
==11416== 
==11416== HEAP SUMMARY:
==11416==     in use at exit: 0 bytes in 0 blocks
==11416==   total heap usage: 3 allocs, 3 frees, 529,200 bytes allocated
==11416== 
==11416== All heap blocks were freed -- no leaks are possible
==11416== 
==11416== For counts of detected and suppressed errors, rerun with: -v
==11416== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```

En las 2 primeras corridas de `valgrind`, el programa se terminó con el comando `kill` del programa `top`.

### Programa `test_oob4.c`

Inicialmente `valgrind` detecta 2 errores, con `Insert last` de 20:

```
$ valgrind --leak-check=full --show-leak-kinds=all ./a.out
==3432== Memcheck, a memory error detector
==3432== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==3432== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==3432== Command: ./a.out
==3432== 
Insert last 
20
a = 7.000000 
==3432== 
==3432== HEAP SUMMARY:
==3432==     in use at exit: 800,000,000 bytes in 20 blocks
==3432==   total heap usage: 20 allocs, 0 frees, 800,000,000 bytes allocated
==3432== 
==3432== 120,000,000 bytes in 3 blocks are possibly lost in loss record 1 of 2
==3432==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==3432==    by 0x400599: mysub (test_oob4.c:10)
==3432==    by 0x400599: main (test_oob4.c:33)
==3432== 
==3432== 680,000,000 bytes in 17 blocks are definitely lost in loss record 2 of 2
==3432==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==3432==    by 0x400599: mysub (test_oob4.c:10)
==3432==    by 0x400599: main (test_oob4.c:33)
==3432== 
==3432== LEAK SUMMARY:
==3432==    definitely lost: 680,000,000 bytes in 17 blocks
==3432==    indirectly lost: 0 bytes in 0 blocks
==3432==      possibly lost: 120,000,000 bytes in 3 blocks
==3432==    still reachable: 0 bytes in 0 blocks
==3432==         suppressed: 0 bytes in 0 blocks
==3432== 
==3432== For counts of detected and suppressed errors, rerun with: -v
==3432== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```


`void mysub(float **a, int dim)`  alloca memoria para `*a` y no  la
libera.

Agrego `free(*a)` y obtengo `Violación de segmento ('core' generado)`

Corriendo `valgrind ./a.out`, se obtiene un error en la línea 36,
`printf("a = %f \n", a[0]);`. Este error se produce por tener liberada la memoria
apuntada por `float * a`.



```
$ valgrind --leak-check=full --show-leak-kinds=all ./a.out
==3479== Memcheck, a memory error detector
==3479== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==3479== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==3479== Command: ./a.out
==3479== 
Insert last 
20
==3479== Invalid read of size 4
==3479==    at 0x4006B2: main (test_oob4.c:36)
==3479==  Address 0x7822040 is 0 bytes inside a block of size 40,000,000 free'd
==3479==    at 0x4C2BDEC: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==3479==    by 0x4006A7: mysub (test_oob4.c:17)
==3479==    by 0x4006A7: main (test_oob4.c:33)
==3479== 
a = 7.000000 
==3479== 
==3479== HEAP SUMMARY:
==3479==     in use at exit: 0 bytes in 0 blocks
==3479==   total heap usage: 20 allocs, 20 frees, 800,000,000 bytes allocated
==3479== 
==3479== All heap blocks were freed -- no leaks are possible
==3479== 
==3479== For counts of detected and suppressed errors, rerun with: -v
==3479== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

```

Comentado la línea del `printf()`:

```
$ valgrind --leak-check=full --show-leak-kinds=all ./a.out
==3519== Memcheck, a memory error detector
==3519== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==3519== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==3519== Command: ./a.out
==3519== 
Insert last 
20
==3519== 
==3519== HEAP SUMMARY:
==3519==     in use at exit: 0 bytes in 0 blocks
==3519==   total heap usage: 20 allocs, 20 frees, 800,000,000 bytes allocated
==3519== 
==3519== All heap blocks were freed -- no leaks are possible
==3519== 
==3519== For counts of detected and suppressed errors, rerun with: -v
==3519== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```



## Funny


### salida del programa

#### sin el flag -DDEBUG

```
Violación de segmento (`core' generado)
 
```


#### con el flag -DDEBUG


```
I'm HERE !!!! 
Violación de segmento (`core' generado)
```

Cuando está el flag -DDEBUG el programa imprime el
mensaje *I'm HERE !!!!*.

Esto se explica por que en main se tiene

```
#ifdef DEBUG
  char *errmsg;
#endif

#ifdef DEBUG
  errmsg = (char *)malloc(sizeof(char)*1024);
  sprintf(errmsg, "I'm HERE !!!! \n");
#endif

#ifdef DEBUG
  printf("%s", errmsg);
#endif


```

El preprocesador cuando encuentra el flag DEBUG, incluye el 
código entre los:

```

#ifdef DEBUG
.
#endif
```

