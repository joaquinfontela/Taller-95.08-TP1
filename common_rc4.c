#include "common_rc4.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void rc4Encoder_t_swap(rc4Encoder_t *self, uint32_t i, uint32_t j) {
  unsigned char aux = self->S[i];
  self->S[i] = self->S[j];
  self->S[j] = aux;
}

static void rc4Encoder_t_KSA(rc4Encoder_t *self) {
  unsigned int keyLength = strlen((char *)self->key);
  uint32_t i, j;

  for (i = 0; i < 256; i++) self->S[i] = i;

  for (i = j = 0; i < 256; i++) {
    j = (j + self->key[i % keyLength] + self->S[i]) & 255;
    rc4Encoder_t_swap(self, i, j);
  }
}

int rc4Encoder_t_initialize(rc4Encoder_t *self, unsigned char key[]) {
  if ((self == NULL) || (key == NULL)) return -1;
  self->key = key;
  rc4Encoder_t_KSA(self);

  self->i = 0;
  self->j = 0;
  return 0;
}

static unsigned char rc4Encoder_t_PRGA(rc4Encoder_t *self) {
  uint32_t i = self->i;
  uint32_t j = self->j;

  i = ((i) + 1) & 255;
  j = ((j) + self->S[i]) & 255;

  rc4Encoder_t_swap(self, i, j);

  self->i = i;
  self->j = j;

  return self->S[(self->S[i] + self->S[j]) & 255];
}

void rc4Encoder_t_encode(void *selfVoid, unsigned char string[]) {
  rc4Encoder_t *self = (rc4Encoder_t *)selfVoid;
  int n;
  size_t stringLength = strlen((char *)string);

  for (n = 0; n < stringLength; n++) {
    string[n] = string[n] ^ rc4Encoder_t_PRGA(self);
  }
}

void rc4Encoder_t_decode(void *selfVoid, unsigned char string[],
                         unsigned int bytesToDecode) {
  rc4Encoder_t *self = (rc4Encoder_t *)selfVoid;
  int n;
  unsigned int stringLength = bytesToDecode;

  for (n = 0; n < stringLength; n++) {
    string[n] = string[n] ^ rc4Encoder_t_PRGA(self);
  }
}
