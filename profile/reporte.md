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

Modifico `Makefile` con el flag `-pg` en la etapa de compilación.

### Para el programa `profile_me_1.e` 

```
Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ns/call  ns/call  name    
100.61      0.01     0.01   302500    33.26    33.26  first_assign
  0.00      0.01     0.00   302500     0.00     0.00  second_assign
```

```
                    Call graph (explanation follows)


granularity: each sample hit covers 2 byte(s) for 99.39% of 0.01 seconds

index % time    self  children    called     name
                0.01    0.00  302500/302500      main [2]
[1]    100.0    0.01    0.00  302500         first_assign [1]
-----------------------------------------------
                                                 <spontaneous>
[2]    100.0    0.00    0.01                 main [2]
                0.01    0.00  302500/302500      first_assign [1]
                0.00    0.00  302500/302500      second_assign [3]
-----------------------------------------------
                0.00    0.00  302500/302500      main [2]
[3]      0.0    0.00    0.00  302500         second_assign [3]
-----------------------------------------------

```


### Para el programa `profile_me_2.e`

No obtengo salida 


### Uso de medición interna de tiempos

Salida con optimización en `-O0`:

```
$ ./profile_me_2.e  550
llamada a exp() elapsed 5.711531: secs 
llamada a sqrt() elapsed 2.708098: secs 
llamada a sin() elapsed 4.465816: secs
```

Salida con optimización en `-O1`:

```
$ ./profile_me_2.e  550
llamada a exp() elapsed 5.418941: secs 
llamada a sqrt() elapsed 2.873274: secs 
llamada a sin() elapsed 4.133279: secs 

```


Salida con optimización en `-O2`:

```
$ ./profile_me_2.e  550
llamada a exp() elapsed 5.425079: secs 
llamada a sqrt() elapsed 1.578846: secs 
llamada a sin() elapsed 4.073390: secs

```

Salida con optimización en `-O3`:

```
$ ./profile_me_2.e  550
llamada a exp() elapsed 5.414800: microsecs 
llamada a sqrt() elapsed 1.577698: microsecs 
llamada a sin() elapsed 4.075891: microsecs
```

## Con `perf`


### Para el programa `profile_me_1.e` 
```

 Performance counter stats for './profile_me_1.e':

         21,431231 task-clock (msec)         #    0,761 CPUs utilized          
                13 context-switches          #    0,607 K/sec                  
                 2 cpu-migrations            #    0,093 K/sec                  
               889 page-faults               #    0,041 M/sec                  
        50.738.505 cycles                    #    2,368 GHz                    
        23.278.682 stalled-cycles-frontend   #   45,88% frontend cycles idle   
        11.568.307 stalled-cycles-backend    #   22,80% backend  cycles idle   
        79.129.832 instructions              #    1,56  insns per cycle        
                                             #    0,29  stalled cycles per insn
         9.939.896 branches                  #  463,804 M/sec                  
            15.501 branch-misses             #    0,16% of all branches        
                 0 L1-dcache-loads           #    0,000 K/sec                  
         1.502.279 L1-dcache-load-misses     #    0,00% of all L1-dcache hits  
           195.528 LLC-loads                 #    9,124 M/sec                  
   <not supported> LLC-load-misses:HG      

       0,028143658 seconds time elapsed

```

### Para el programa `profile_me_2.e`
```

 Performance counter stats for './profile_me_2.e 550':

          1,214540 task-clock (msec)         #    0,223 CPUs utilized          
                 8 context-switches          #    0,007 M/sec                  
                 0 cpu-migrations            #    0,000 K/sec                  
               211 page-faults               #    0,174 M/sec                  
         2.171.859 cycles                    #    1,788 GHz                    
         1.495.131 stalled-cycles-frontend   #   68,84% frontend cycles idle   
         1.182.905 stalled-cycles-backend    #   54,47% backend  cycles idle   
         1.428.994 instructions              #    0,66  insns per cycle        
                                             #    1,05  stalled cycles per insn
           238.164 branches                  #  196,094 M/sec                  
            14.632 branch-misses             #    6,14% of all branches        
                 0 L1-dcache-loads           #    0,000 K/sec                  
            20.278 L1-dcache-load-misses     #    0,00% of all L1-dcache hits  
            10.118 LLC-loads                 #    8,331 M/sec                  
   <not supported> LLC-load-misses:HG      

       0,005451022 seconds time elapsed


```
