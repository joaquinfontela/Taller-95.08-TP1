#include "common_encoder.h"
#include "server_commandParser.h"
#include "server_socket.h"

#define PORT "8080"
#define BUFFER_SIZE 300

int main(int argc, char* argv[]) {
  serverCommandValidator_t commandValidator;
  serverCommandValidator_initialize(&commandValidator, argc, argv);
  if (!serverCommandValidator_t_commandIsValid(&commandValidator)) return -1;

  serverCommandParser_t commandParser;
  serverCommandParser_t_initialize(&commandParser, argv);

  server_socket_t skt;
  server_socket_t_init(&skt);
  server_socket_t_bindListen(&skt, PORT, true, 10);
  server_socket_t_accept(&skt);

  unsigned char buf[BUFFER_SIZE];
  server_socket_t_recieve(&skt, buf, BUFFER_SIZE);

  encoder_t encoder;
  encoder_t_init(&encoder, (unsigned char*)commandParser.method,
                 (unsigned char*)commandParser.key);
  encoder_t_decode(&encoder, buf);

  printf("%s\n", buf);
  return 0;
}