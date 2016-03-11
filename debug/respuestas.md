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
son programas programas que permiten poner límite a la disponibilidad
de recursos de sistema. `$ulimit -a` permite conocer el límite de los recursos.

Cuando se ejecuta el código `big.x` antes de ejectutar `$ulimit -s unlimited` 
,que no pone límites en el uso de la memoria disponible para el stack ,  
produce un error: `Violación de segmento ('core' generado)`. 

La solución con `ulimit -s ...` no es una solución en el sentido
del debugging dado que  no se elimina el error que produce el problema.

## Valgrind



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

