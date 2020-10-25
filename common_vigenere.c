#include "common_vigenere.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

int vigenereEncoder_t_initialize(vigenereEncoder_t* self, unsigned char key[]) {
  if ((self == NULL) || (key == NULL)) return -1;
  self->key = key;
  self->currentKeyPosition = 0;
  return 0;
}

void vigenereEncoder_t_encode(void* selfVoid, unsigned char string[]) {
  vigenereEncoder_t* self = (vigenereEncoder_t*)selfVoid;
  uint32_t currentStringPosition = 0;
  uint32_t currentKeyPosition = self->currentKeyPosition;
  unsigned char currentChar = string[currentStringPosition];
  while (currentChar != '\0') {
    if (self->key[currentKeyPosition] == '\0') {
      currentKeyPosition = 0;
    }
    string[currentStringPosition] += self->key[currentKeyPosition];
    currentStringPosition++;
    currentKeyPosition++;
    currentChar = string[currentStringPosition];
  }
  self->currentKeyPosition = currentKeyPosition;
}

void vigenereEncoder_t_decode(void* selfVoid, unsigned char string[],
                              unsigned int bytesToDecode) {
  vigenereEncoder_t* self = (vigenereEncoder_t*)selfVoid;
  uint32_t currentStringPosition = 0;
  uint32_t currentKeyPosition = self->currentKeyPosition;
  unsigned char currentChar = string[currentStringPosition];
  while ((currentChar != '\0') && (currentStringPosition < bytesToDecode)) {
    if (self->key[currentKeyPosition] == '\0') {
      currentKeyPosition = 0;
    }
    string[currentStringPosition] -= self->key[currentKeyPosition];
    currentStringPosition++;
    currentKeyPosition++;
    currentChar = string[currentStringPosition];
  }
  self->currentKeyPosition = currentKeyPosition;
}
