# Herramienta interpretar

## Info

  Brinda la funcionalidad para que dado un fichero origen con código
  ensamblador referente al emulador(ver abajo) se pueda pasar su contenido
  a los opcodes definidos y los escribe en otro fichero destino.
  - gcc versión 6.3.1
  - Compilar con: g++ -std=c++11 interpretar.cpp -o interpretar

## Operaciones

### Tipos de operaciones según el orden de los operandos

  - Tipo load o move: rs2 rs1 inmd  
  - Tipo store: rs1 inmd rs2
  - Tipo branch condicional: rs1 rs2 inmd
  - Tipo Aritmetic-logic: rd rs1 rs2

### Operaciones implementadas
  ``` assembly
     nop
     mov rs2 rs1 inmd    --equivale--     rs2 <- ext(inmd) + rs1
     lw  rs2 rs1 inmd    --equivale--     rs2 <-  mem[ext(inmd) + rs1]
     sw  rs1 inmd rs2    --equivale--     [ext(inmd) + rs1] <- rs2
     beq rs1 rs2 inmd    --equivale-- if rs1 == rs2 go to ext(inmd) memory jump (delayed one cycle)
     and rd  rs1 rs2    --equivale--     rd <- rs1 & rs2
     or  rd  rs1 rs2    --equivale--     rd <- rs1 | rs2
     sum rd  rs1 rs2    --equivale--     rd <- rs1 + rs2
     res rd  rs1 rs2    --equivale--     rd <- rs1 - rs2
     rs1 rd  rs1 rs2    --equivale--     rd <- rs1
     <   rd  rs1 rs2    --equivale--     rd <- rs1, if rs1 < rs2 flagX = 1
     =   rd  rs1 rs2    --equivale--     rd <- rs1 , if rs1 == rs2 flagZ = 1
  ```
  - Para el interprete las palabras clave sum y add son equivalentes
