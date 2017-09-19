# Segmented pipeline, only detentions

  - compile: g++ main.c -o main

## Operations

#### Aritmetic-logic Operations
 | opCode | rs1 | rs2 | rd | 11bits |

  - 6bits opCode
  - 5bits rs1
  - 5bits rs2
  - 5bits rd

#### Memory Access
  | opCode | rs1 | rs2 | inmd(to extend)|

  - 6bits opCode
  - 5bits rs1
  - 5bits rs2
  - 16bits inmd(to extend to 32bits)

## Implemented Operations

  - nop 000000
  - mov 000001  rs2 <- ext(inmd) + rs1
  - lw  000010  rs2 <- mem[ext(inmd) + rs1]
  - sw  000011  [ext(inmd) + rs1] <- rs2
  - beq 000100  if rs1 == rs2 go to ext(inmd) memory jump (delayed one cycle)
  - and 001000  rd <- rs1 & rs2
  - or  001001  rd <- rs1 | rs2
  - sum 001010  rd <- rs1 + rs2
  - res 001011  rd <- rs1 - rs2
  - rs1 001100  rd <- rs1
  - <   001101  rd <- rs1, if rs1 < rs2 flagX = 1
  - =   001111  rd <- rs1 , if rs1 == rs2 flagZ = 1
