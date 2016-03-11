# Informe:

## Con `time`

Se crea un `Makefile` para compilar los dos programas:

* `profile_me_1.c`  

* `profile_me_2.o`


La primer corrida da:

```
$time ./profile_me_1.e 
Violación de segmento (`core' generado)

real	0m0.140s
user	0m0.000s
sys	0m0.001s
```

```
$time ./profile_me_2.e 
Violación de segmento (`core' generado)

real	0m0.099s
user	0m0.000s
sys	0m0.002s

```

Con parámetros adecuados:

En  `profile_me_1.c` puse `#define SIZE 550`


```
$ time ./profile_me_1.e

real	0m0.022s
user	0m0.013s
sys	0m0.004s

```

Pasando un parámetro en línea de comandos a `./profile_me_2.e <numero>` 

```
$ time ./profile_me_2.e 700
3523.98
real	0m0.002s
user	0m0.000s
sys	0m0.001s

```

## Con `gprof`


