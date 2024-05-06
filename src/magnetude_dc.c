#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

uint8_t code_AC_CbCr[256][17] = {{2,0,0},{2,0,1},{3,1,0,0},{4,1,0,1,0},{5,1,1,0,0,0},{5,1,1,0,0,1},{6,1,1,1,0,0,0},{7,1,1,1,1,0,0,0},{9,1,1,1,1,1,0,1,0,0},{10,1,1,1,1,1,1,0,1,1,0},{12,1,1,1,1,1,1,1,1,0,1,0,0},{0},{0},{0},{0},{0},{0},{4,1,0,1,1},{6,1,1,1,0,0,1},{8,1,1,1,1,0,1,1,0},{9,1,1,1,1,1,0,1,0,1},{11,1,1,1,1,1,1,1,0,1,1,0},{12,1,1,1,1,1,1,1,1,0,1,0,1},{16,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0},{16,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,0,0,0,1,0,1,0},{16,1,1,1,1,1,1,1,1,1,0,0,0,1,0,1,1},{0},{0},{0},{0},{0},{0},{5,1,1,0,1,0},{8,1,1,1,1,0,1,1,1},{10,1,1,1,1,1,1,0,1,1,1},{12,1,1,1,1,1,1,1,1,0,1,1,0},{15,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0},{16,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0},{16,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,1},{16,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0},{16,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1},{16,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0},{0},{0},{0},{0},{0},{0},{5,1,1,0,1,1},{8,1,1,1,1,1,0,0,0},{10,1,1,1,1,1,1,1,0,0,0},{12,1,1,1,1,1,1,1,1,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,1},{16,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,0},{16,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,1},{16,1,1,1,1,1,1,1,1,1,0,0,1,0,1,0,0},{16,1,1,1,1,1,1,1,1,1,0,0,1,0,1,0,1},{16,1,1,1,1,1,1,1,1,1,0,0,1,0,1,1,0},{0},{0},{0},{0},{0},{0},{6,1,1,1,0,1,0},{9,1,1,1,1,1,0,1,1,0},{16,1,1,1,1,1,1,1,1,1,0,0,1,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0},{16,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,0},{16,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,1},{16,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0},{16,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,1},{16,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0},{0},{0},{0},{0},{0},{0},{6,1,1,1,0,1,1},{10,1,1,1,1,1,1,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1},{16,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0},{16,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,1},{16,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,0},{16,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,1},{16,1,1,1,1,1,1,1,1,1,0,1,0,0,1,0,0},{16,1,1,1,1,1,1,1,1,1,0,1,0,0,1,0,1},{16,1,1,1,1,1,1,1,1,1,0,1,0,0,1,1,0},{0},{0},{0},{0},{0},{0},{7,1,1,1,1,0,0,1},{11,1,1,1,1,1,1,1,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,0,1,0,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,0,1,0,1,0,0,0},{16,1,1,1,1,1,1,1,1,1,0,1,0,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0},{16,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,1},{16,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,0},{16,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,1},{16,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0},{0},{0},{0},{0},{0},{0},{7,1,1,1,1,0,1,0},{11,1,1,1,1,1,1,1,1,0,0,0},{16,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1},{16,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0},{16,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,1},{16,1,1,1,1,1,1,1,1,1,0,1,1,0,0,1,0},{16,1,1,1,1,1,1,1,1,1,0,1,1,0,0,1,1},{16,1,1,1,1,1,1,1,1,1,0,1,1,0,1,0,0},{16,1,1,1,1,1,1,1,1,1,0,1,1,0,1,0,1},{16,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0},{0},{0},{0},{0},{0},{0},{8,1,1,1,1,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0},{16,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0},{16,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1},{16,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0},{16,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1},{16,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0},{16,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1},{0},{0},{0},{0},{0},{0},{9,1,1,1,1,1,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},{16,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1},{16,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0},{16,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},{16,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0},{16,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,1},{16,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0},{16,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0},{0},{0},{0},{0},{0},{0},{9,1,1,1,1,1,1,0,0,0},{16,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,1,0,0,1,0,1,0},{16,1,1,1,1,1,1,1,1,1,1,0,0,1,0,1,1},{16,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0},{16,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1},{16,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0},{16,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1},{16,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0},{16,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1},{0},{0},{0},{0},{0},{0},{9,1,1,1,1,1,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,0},{16,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,1},{16,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,0},{16,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1},{16,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0},{16,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0},{16,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,0},{0},{0},{0},{0},{0},{0},{9,1,1,1,1,1,1,0,1,0},{16,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1},{16,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0},{16,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1},{16,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0},{16,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1},{16,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},{16,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1},{16,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0},{16,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1},{0},{0},{0},{0},{0},{0},{11,1,1,1,1,1,1,1,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0},{16,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,1},{16,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0},{16,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0},{16,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0},{16,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1},{16,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0},{0},{0},{0},{0},{0},{0},{14,1,1,1,1,1,1,1,1,1,0,0,0,0,0},{16,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1},{16,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0},{16,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1},{16,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},{16,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1},{16,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0},{16,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1},{16,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0},{16,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1},{0},{0},{0},{0},{0},{10,1,1,1,1,1,1,1,0,1,0},{15,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},{16,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0},{16,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},{16,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0},{16,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1},{16,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},{16,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},{16,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}};

uint8_t code_AC_Y[256][17]= {{4,1,0,1,0},{2,0,0},{2,0,1},{3,1,0,0},{4,1,0,1,1},{5,1,1,0,1,0},{7,1,1,1,1,0,0,0},{8,1,1,1,1,1,0,0,0},{10,1,1,1,1,1,1,0,1,1,0},{16,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0},{16,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1},{0},{0},{0},{0},{0},{0},{4,1,1,0,0},{5,1,1,0,1,1},{7,1,1,1,1,0,0,1},{9,1,1,1,1,1,0,1,1,0},{11,1,1,1,1,1,1,1,0,1,1,0},{16,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,0},{16,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1},{16,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0},{16,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0},{0},{0},{0},{0},{0},{0},{5,1,1,1,0,0},{8,1,1,1,1,1,0,0,1},{10,1,1,1,1,1,1,0,1,1,1},{12,1,1,1,1,1,1,1,1,0,1,0,0},{16,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,0,0,0,1,0,1,0},{16,1,1,1,1,1,1,1,1,1,0,0,0,1,0,1,1},{16,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0},{16,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,1},{16,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0},{0},{0},{0},{0},{0},{0},{6,1,1,1,0,1,0},{9,1,1,1,1,1,0,1,1,1},{12,1,1,1,1,1,1,1,1,0,1,0,1},{16,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1},{16,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0},{16,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,1},{16,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,0},{16,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,1},{16,1,1,1,1,1,1,1,1,1,0,0,1,0,1,0,0},{16,1,1,1,1,1,1,1,1,1,0,0,1,0,1,0,1},{0},{0},{0},{0},{0},{0},{6,1,1,1,0,1,1},{10,1,1,1,1,1,1,1,0,0,0},{16,1,1,1,1,1,1,1,1,1,0,0,1,0,1,1,0},{16,1,1,1,1,1,1,1,1,1,0,0,1,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0},{16,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,0},{16,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,1},{16,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0},{16,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,1},{0},{0},{0},{0},{0},{0},{7,1,1,1,1,0,1,0},{11,1,1,1,1,1,1,1,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0},{16,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1},{16,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0},{16,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,1},{16,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,0},{16,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,1},{16,1,1,1,1,1,1,1,1,1,0,1,0,0,1,0,0},{16,1,1,1,1,1,1,1,1,1,0,1,0,0,1,0,1},{0},{0},{0},{0},{0},{0},{7,1,1,1,1,0,1,1},{12,1,1,1,1,1,1,1,1,0,1,1,0},{16,1,1,1,1,1,1,1,1,1,0,1,0,0,1,1,0},{16,1,1,1,1,1,1,1,1,1,0,1,0,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,0,1,0,1,0,0,0},{16,1,1,1,1,1,1,1,1,1,0,1,0,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0},{16,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,1},{16,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,0},{16,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,1},{0},{0},{0},{0},{0},{0},{8,1,1,1,1,1,0,1,0},{12,1,1,1,1,1,1,1,1,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0},{16,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1},{16,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0},{16,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,1},{16,1,1,1,1,1,1,1,1,1,0,1,1,0,0,1,0},{16,1,1,1,1,1,1,1,1,1,0,1,1,0,0,1,1},{16,1,1,1,1,1,1,1,1,1,0,1,1,0,1,0,0},{16,1,1,1,1,1,1,1,1,1,0,1,1,0,1,0,1},{0},{0},{0},{0},{0},{0},{9,1,1,1,1,1,1,0,0,0},{15,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},{16,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0},{16,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0},{16,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0},{16,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1},{16,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0},{16,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1},{0},{0},{0},{0},{0},{0},{9,1,1,1,1,1,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0},{16,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1},{16,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},{16,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1},{16,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0},{16,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1},{16,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0},{16,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,1},{16,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0},{0},{0},{0},{0},{0},{0},{9,1,1,1,1,1,1,0,1,0},{16,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0},{16,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,1,0,0,1,0,1,0},{16,1,1,1,1,1,1,1,1,1,1,0,0,1,0,1,1},{16,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0},{16,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1},{16,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0},{16,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1},{0},{0},{0},{0},{0},{0},{10,1,1,1,1,1,1,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0},{16,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1},{16,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,0},{16,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,1},{16,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,0},{16,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1},{16,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0},{16,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0},{0},{0},{0},{0},{0},{0},{10,1,1,1,1,1,1,1,0,1,0},{16,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,0},{16,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1},{16,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0},{16,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1},{16,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0},{16,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1},{16,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},{16,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1},{0},{0},{0},{0},{0},{0},{11,1,1,1,1,1,1,1,1,0,0,0},{16,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0},{16,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1},{16,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0},{16,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,1},{16,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0},{16,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0},{16,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0},{0},{0},{0},{0},{0},{0},{16,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1},{16,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0},{16,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1},{16,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0},{16,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1},{16,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},{16,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1},{16,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0},{16,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1},{16,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0},{0},{0},{0},{0},{0},{11,1,1,1,1,1,1,1,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1},{16,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0},{16,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1},{16,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},{16,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1},{16,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0},{16,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1},{16,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},{16,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},{16,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}};

uint8_t code_DC_Y[12][10] ={{2,0,0},{3,0,1,0},{3,0,1,1},{3,1,0,0},{3,1,0,1},{3,1,1,0},{4,1,1,1,0},{5,1,1,1,1,0},{6,1,1,1,1,1,0},{7,1,1,1,1,1,1,0},{8,1,1,1,1,1,1,1,0},{9,1,1,1,1,1,1,1,1,0}};

uint8_t code_DC_CbCr[12][12] = {{2,0,0},{2,0,1},{2,1,0},{3,1,1,0},{4,1,1,1,0},{5,1,1,1,1,0},{6,1,1,1,1,1,0},{7,1,1,1,1,1,1,0},{8,1,1,1,1,1,1,1,0},{9,1,1,1,1,1,1,1,1,0},{10,1,1,1,1,1,1,1,1,1,0},{11,1,1,1,1,1,1,1,1,1,1,0}};

uint8_t trouver_magnetude(int16_t n){
    int64_t nombre=1;
    uint16_t n2; //on prend la valeur absolue sinon LES PROBLEMES 
    if (n<0){
        n2=-n;
    }
    else{
        n2=n;
    }
    for (uint8_t k=0;k<12;k++){
        if (nombre-1 >= n2){
            return k;
        }
        nombre = nombre * 2;
    }
    perror("C'est trop grand chacal t'abuses \n");
    return 0;
}


uint8_t* codage_AC_RLE(int16_t* tab){  
    uint8_t* tab_RLE = malloc(sizeof(uint8_t)*64);
    uint8_t indice = 1;
    uint8_t nb_zero = 0;
    for (uint8_t i = 0; i<64; i++){
        if (tab[i] == 0){
            nb_zero ++;
        }
        else{
            uint8_t magnetude = trouver_magnetude(tab[i]);
            tab_RLE[indice] = nb_zero*(16) + magnetude;
            indice ++;
            nb_zero = 0;
        }
    }
    //tab_RLE[indice] = 0;
    tab_RLE[0] = indice +1; // l'indice 0 est la taille du tableau qui suit
    tab_RLE = realloc(tab_RLE, sizeof(uint8_t)*(indice +2));
    return tab_RLE;
}


uint8_t *codage_indice_magn(int16_t n){
    
    uint8_t magn = trouver_magnetude(n);
    int64_t nombre = 1;
    uint64_t res;
    int64_t tmp;
    uint8_t *tab;
    for (uint8_t k = 0;k<magn;k++){
        nombre = nombre * 2;   
    }
    nombre = nombre - 1;
    if (n==0){
        tab = malloc(sizeof(uint8_t));
        tab[0]=0; 
    }
    else if (n<0){
        res = (nombre + n) ;
    }
    else{
        tmp = ((int64_t) ((nombre+1) / 2));
        res = (nombre - tmp + 1) + (n - tmp); //les négatifs puis les positifs, on compte tous ceux qui sont avant
    }
    //on transforme res en binaire
    // on a magn qui nous dit sur combien de bits on code res  
    tab = malloc(magn*sizeof(uint8_t));
    for (uint8_t i=0;i<magn;i++){
        tab[magn-i-1]= res%2;
        res = res/2;
    }
    // for (uint8_t i=0;i<magn;i++){
    //     printf("%d ",tab[i]);
    // }
    return tab;
}


uint8_t *codage_total_AC_DC_CbCr(uint8_t *RLE, int16_t *flux){ //attention le flux contient DC 
    // renvoie le flux de bits attendu 
    printf("flux ");
    uint64_t compteur = 1;
    uint64_t compteurRLE = 1;
    uint64_t indice=0; //contient la taille, le premier element
    uint8_t *res = malloc((60000)*sizeof(uint8_t));
    uint8_t magn = trouver_magnetude(flux[0]);
    printf("magn %d\n",magn);
    uint8_t *tab_temp = codage_indice_magn(flux[0]);

    //PARTIE DC 
    for (uint8_t i=1;i<=code_DC_CbCr[magn][0];i++){
        res[indice] = code_DC_Y[magn][i];
        printf("%d" ,res[indice]);
        indice ++;
    }
    for (uint8_t i=0;i<magn;i++){
        res[indice] = tab_temp[i];
        printf("%d" ,res[indice]);
        indice ++;
    }
    printf("\n\n\n\n");
    while (compteur <= 64){
        if (flux[compteur]==0){
            compteur++;
        }
        else{
            uint8_t temp = RLE[compteurRLE+1];
            uint8_t *tab_temp = code_AC_CbCr[temp];
            uint64_t s = 0;
            for (uint8_t i=1;i<=tab_temp[0];i++){
                res[indice] =tab_temp[i];
                printf("%d" , res[indice]); // a commenter pour enlever les tests
                s += pow(2,tab_temp[0]-i)*tab_temp[i];
                indice++;
            }
            tab_temp = codage_indice_magn(flux[compteur]);
            uint8_t magn = trouver_magnetude(flux[compteur]);
            for (uint8_t i=0;i<magn;i++){
                res[indice] = tab_temp[i];
                printf("%d" , res[indice]);
                indice++;
            }
            printf("value %d magnetude %d huffman path %ld \ncode %d, nb bits %d\n",flux[compteur],magn,s,temp,code_AC_Y[temp][0]);// a commenter pour enlever les tests
            compteurRLE++;
            compteur++;
        }
    }
    res[indice] = 88; //fin du fichier 
    res = realloc(res,(indice+1)*sizeof(uint8_t));
    return res;
}
uint8_t *codage_total_DC_Y(int16_t n){
    uint8_t magn = trouver_magnetude(n);
    uint8_t *cd = codage_indice_magn(n);
    
    uint8_t *entete = code_DC_Y[magn];
    uint8_t *res = malloc((entete[0]+magn)*sizeof(uint8_t));
    res[0]=entete[0]+magn;
    for (uint8_t i=1;i<=entete[0];i++){
        res[i] = entete[i];
    }
    for (uint8_t i=1;i<=magn;i++){
        res[i+entete[0]] = cd[i-1];
    }
    return res;
}

uint8_t *codage_total_DC_CbCr(int16_t n){
    uint8_t magn = trouver_magnetude(n);
    uint8_t *cd = codage_indice_magn(n);
    uint8_t *entete = code_DC_CbCr[magn];
    uint8_t *res = malloc((entete[0]+magn)*sizeof(uint8_t));
    res[0]=entete[0]+magn;
    for (uint8_t i=1;i<=entete[0];i++){
        res[i] = entete[i];
    }
    for (uint8_t i=1;i<=magn;i++){
        res[i+entete[0]] = cd[i-1];
    }
    return res;
}

uint8_t *codage_total_AC_DC_Y(uint8_t *RLE, int16_t *flux, int16_t *flux2, bool changement_DC){ //attention le flux contient DC, flux2 est le suivant de flux
    // renvoie le flux de bits attendu 
    printf("flux ");
    uint64_t compteur = 1;
    uint64_t compteurRLE = 1;
    uint64_t indice=0; //contient la taille, le premier element
    uint8_t magn;
    uint8_t *tab_temp;
    uint8_t *res = malloc((60000)*sizeof(uint8_t));
    if (!changement_DC){
        magn = trouver_magnetude(flux2[0]);
        printf("magn %d\n",magn);
        tab_temp = codage_indice_magn(flux2[0]);
    }
    else{
        magn = trouver_magnetude(flux2[0]-flux[0]);
        printf("magn %d\n",magn);
        tab_temp = codage_indice_magn(flux2[0]-flux[0]);
    }


    //PARTIE DC 
    for (uint8_t i=1;i<=code_DC_Y[magn][0];i++){
        res[indice] = code_DC_Y[magn][i];
        printf("%d" ,res[indice]);
        indice ++;
    }
    for (uint8_t i=0;i<magn;i++){
        res[indice] = tab_temp[i];
        printf("%d" ,res[indice]);
        indice ++;
    }
    printf("\n\n\n\n");
    while (compteur <= 64){
        if (flux2[compteur]==0){
            compteur++;
        }
        else{
            uint8_t temp = RLE[compteurRLE+1];
            uint8_t *tab_temp = code_AC_Y[temp];
            uint64_t s = 0;
            for (uint8_t i=1;i<=tab_temp[0];i++){
                res[indice] =tab_temp[i];
                printf("%d" , res[indice]); // a commenter pour enlever les tests
                s += pow(2,tab_temp[0]-i)*tab_temp[i];
                indice++;
            }
            tab_temp = codage_indice_magn(flux2[compteur]);
            uint8_t magn = trouver_magnetude(flux2[compteur]);
            for (uint8_t i=0;i<magn;i++){
                res[indice] = tab_temp[i];
                printf("%d" , res[indice]);
                indice++;
            }
            printf("value %d magnetude %d huffman path %ld \ncode %d, nb bits %d\n",flux2[compteur],magn,s,temp,code_AC_Y[temp][0]);// a commenter pour enlever les tests
            compteurRLE++;
            compteur++;
        }
    }
    res[indice] = 88; //fin du fichier 
    res = realloc(res,(indice+1)*sizeof(uint8_t));
    return res;
}
// int main(){
//     // int16_t tab[64] = {-1,0x0001,0x0000,0x0000,0x0000,0x0001,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000};
//     // uint8_t* tab_rle = codage_AC_RLE(tab);
    
//     // for (int i = 0 ; i < tab_rle[0]; i++){
//     //     printf("%x ", tab_rle[i]);
//     // }
//     // printf("\n");
//     // uint8_t tab[11] = {10, 2, 2, 2, 1, 12, 0, 1, 3, 15, 0};
//     // uint8_t *res = bits_poids_forts(tab);
//     // uint8_t taille = res[0];
//     // for (int i = 1 ; i < taille; i++)
//     // {
//     //     printf("%d ", res[i]);
//     // }
//     // printf("\n");
//     // return 0;
// }
