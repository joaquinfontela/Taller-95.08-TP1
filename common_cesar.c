#include "common_cesar.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int cesarEncoder_t_initialize(cesarEncoder_t* self, unsigned char offset[]) {
  if (self == NULL) return -1;
  self->offset = strtol((char*)offset, (char**)NULL, 10);
  return 0;
}

void cesarEncoder_t_encode(void* selfVoid, unsigned char string[]) {
  cesarEncoder_t* self = (cesarEncoder_t*)selfVoid;
  uint32_t currentPosition = 0;
  unsigned char currentChar = string[currentPosition];
  while (currentChar != '\0') {
    string[currentPosition] = string[currentPosition] + self->offset;
    currentPosition++;
    currentChar = string[currentPosition];
  }
}

void cesarEncoder_t_decode(void* selfVoid, unsigned char string[],
                           unsigned int bytesToDecode) {
  cesarEncoder_t* self = (cesarEncoder_t*)selfVoid;
  uint32_t currentPosition = 0;
  unsigned char currentChar = string[currentPosition];
  while ((currentChar != '\0') && (currentPosition < bytesToDecode)) {
    string[currentPosition] = string[currentPosition] - self->offset;
    currentPosition++;
    currentChar = string[currentPosition];
  }
}
