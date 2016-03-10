## Various bugs


## Floating point exception


## Segmentation Fault


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


