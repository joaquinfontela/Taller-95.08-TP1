#include "client_logic.h"

#include <stddef.h>
#include <stdio.h>
#define BUFFER_LEN 1000000

static bool client_logic_commandIsValid(client_t* self, int argc, char** argv) {
  clientCommandValidator_t commandValidator;
  clientCommandValidator_initialize(&commandValidator, argc, argv);
  return clientCommandValidator_t_commandIsValid(&commandValidator);
}

static bool client_logic_init(client_t* self, int argc, char** argv) {
  clientCommandParser_t commandParser;
  clientCommandParser_t_initialize(&commandParser, argv);
  self->commandParser = commandParser;

  stdinReader_t stdinReader;
  stdinReader_t_init(&stdinReader);
  self->stdinReader = stdinReader;

  client_socket_t skt;
  client_socket_t_init(&skt);
  self->skt = skt;

  encoder_t encoder;
  encoder_t_init(&encoder, (unsigned char*)(self->commandParser.method),
                 (unsigned char*)(self->commandParser.key));
  self->encoder = encoder;
  return true;
}

static bool client_logic_send(client_t* self) {
  char message[BUFFER_LEN];
  size_t bytesRead;

  client_socket_t_connect(&(self->skt), self->commandParser.host,
                          self->commandParser.port);

  // cesarEncoder_t* cesar = (cesarEncoder_t*)self->encoder.encoder;

  do {
    // printf("\n%d\n", cesar->offset);
    bytesRead = stdinReader_t_readChunk(&(self->stdinReader), message);
    encoder_t_encode(&(self->encoder), (unsigned char*)message);
    client_socket_t_send(&(self->skt), message, bytesRead);
  } while (bytesRead == 64);

  client_socket_t_disconnect(&(self->skt));
  client_socket_t_destroy(&(self->skt));

  return true;
}

int client_logic_execute(client_t* self, int argc, char** argv) {
  if (!client_logic_commandIsValid(self, argc, argv)) return -1;
  client_logic_init(self, argc, argv);
  client_logic_send(self);
  return 0;
}