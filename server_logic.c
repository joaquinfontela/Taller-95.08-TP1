#include "server_logic.h"

#define SUCCESS 0
#define MESSAGE_RECEVING_ERROR -1
#define COMMAND_PROCESSING_ERROR 1
#define DECODING_ERROR 2

#define BUFFER_SIZE 1000

static bool server_logic_commandIsValid(server_t* self, int argc, char** argv) {
  serverCommandValidator_t serverCommandValidator;
  serverCommandValidator_initialize(&serverCommandValidator, argc, argv);
  return (serverCommandValidator_t_commandIsValid(&serverCommandValidator));
}

static bool server_logic_init(server_t* self, int argc, char** argv) {
  serverCommandParser_t serverCommandParser;
  serverCommandParser_t_initialize(&serverCommandParser, argv);
  self->commandParser = serverCommandParser;

  server_socket_t skt;
  server_socket_t_init(&skt);
  self->skt = skt;

  encoder_t decoder;
  encoder_t_init(&decoder, (unsigned char*)(self->commandParser.method),
                 (unsigned char*)(self->commandParser.key));
  self->decoder = decoder;

  return true;
}

static ssize_t server_logic_recieveMessage(server_t* self, unsigned char* buf) {
  if (!server_socket_t_bindListen(&(self->skt), self->commandParser.port, true,
                                  10))
    return MESSAGE_RECEVING_ERROR;

  if (server_socket_t_accept(&(self->skt)) == -1) return MESSAGE_RECEVING_ERROR;

  ssize_t bytesRecieved =
      server_socket_t_recieve(&(self->skt), buf, BUFFER_SIZE);

  if (bytesRecieved == -1) return MESSAGE_RECEVING_ERROR;

  server_socket_t_disconnect(&(self->skt));
  server_socket_t_destroy(&(self->skt));

  return bytesRecieved;
}

static bool server_logic_decode(server_t* self, unsigned char* buf,
                                size_t bytesRecieved) {
  if (encoder_t_decode(&(self->decoder), buf, bytesRecieved) != 0) return false;

  return true;
}

int server_logic_execute(server_t* self, int argc, char* argv[]) {
  if (!server_logic_commandIsValid(self, argc, argv)) return -1;

  server_logic_init(self, argc, argv);

  unsigned char buf[BUFFER_SIZE];
  ssize_t bytesRecieved = server_logic_recieveMessage(self, buf);

  if (!server_logic_decode(self, buf, bytesRecieved)) return DECODING_ERROR;

  printf("%s\n", buf);

  return 0;
}
