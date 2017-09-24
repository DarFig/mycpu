# MyCPU-Emu

### Compilar

#### Utilizando makefile
  Reglas
  - make        --> lanza las ordenes build y tools
  - make build  --> construye ./c_modules/bin/main
  - make tools  --> construye las herramientas, por ahora ./herramientas/interpretar
  - make run    --> lanza ./c_modules/ bin/main

### Requirements

- c/c++ compiler

### Estructura

- ./view --> futura interfaz(ToDO)
- ./herramientas --> herramientas independientes, utils y demás(interprete)
- ./c_modules/ --> modulos de la cpu en lenguaje c/c++
- ./c_modules/bin/ -->  ejecutables c
- ./c_modules/src/ -->  ficheros fuente .c .cpp .cc
- ./c_modules/include/ --> ficheros cabecera .h
- ./c_modules/old/ --> otras versiones de la cpu


### Información

#### Guía Estructural

![Guía Estructural](https://github.com/DarFig/mycpu/blob/master/c_modules/guia_estructural.md)


#### Información del segmentado

![Segmented pipeline](https://github.com/DarFig/mycpu/blob/master/c_modules/doc_seg_pipeline.md)    

### Herramientas

#### Interprete (Interpretar)

![Interpretar](https://github.com/DarFig/mycpu/blob/master/herramientas/interpretar.md)    
