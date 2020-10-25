#include "common_encoder.h"

#define NULL_VALUE_ERROR 1
#define METHOD_ERROR 2
#define CESAR "cesar"
#define RC4 "rc4"
#define VIGENERE "vigenere"

static int encoder_t_saveEncoder(encoder_t* self, unsigned char* method) {
  if (!strcmp((char*)method, CESAR)) {
    cesarEncoder_t cesarEncoder;
    cesarEncoder_t_initialize(&cesarEncoder, self->key);
    self->encoder = &cesarEncoder;
    self->encode = &(cesarEncoder_t_encode);
    self->decode = &(cesarEncoder_t_decode);

  } else if (!strcmp((char*)method, RC4)) {
    rc4Encoder_t rc4Encoder;
    rc4Encoder_t_initialize(&rc4Encoder, self->key);
    self->encoder = &rc4Encoder;
    self->encode = &(rc4Encoder_t_encode);
    self->decode = &(rc4Encoder_t_decode);

  } else if (!strcmp((char*)method, VIGENERE)) {
    vigenereEncoder_t vigenereEncoder;
    vigenereEncoder_t_initialize(&vigenereEncoder, self->key);
    self->encoder = &vigenereEncoder;
    self->encode = &(vigenereEncoder_t_encode);
    self->decode = &(vigenereEncoder_t_decode);

  } else {
    return METHOD_ERROR;
  }

  return 0;
}

int encoder_t_init(encoder_t* self, unsigned char* method, unsigned char* key) {
  if (self == NULL) return NULL_VALUE_ERROR;

  self->key = key;
  encoder_t_saveEncoder(self, method);

  return 0;
}

int encoder_t_encode(encoder_t* self, unsigned char string[]) {
  if (self == NULL) return NULL_VALUE_ERROR;

  self->encode(self->encoder, string);
  return 0;
}

int encoder_t_decode(encoder_t* self, unsigned char string[],
                     unsigned int bytesToDecode) {
  if (self == NULL) return NULL_VALUE_ERROR;

  self->decode(self->encoder, string, bytesToDecode);
  return 0;
}
