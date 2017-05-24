#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
  int socket_descriptor;
  int client_socket_descriptor;
  int port_number;
  int buffer_size = 200;
  char buffer[buffer_size] = {0};
  struct sockaddr_in serv_addr, cli_addr;

  int option = 1;
  socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)); // so there is no error on reusing socket while after

  if(socket_descriptor < 0){
    printf("Error opening socket (server)\n");
    return 0;
  }

  port_number = 10554;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port_number);

  if(bind(socket_descriptor, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){
      printf("Error bindig a socket (server)\n");
      return 0;
  }

  while(1){
    listen(socket_descriptor, 5);
    socklen_t clilen;
    clilen = sizeof(cli_addr);
    client_socket_descriptor = accept(socket_descriptor, (struct sockaddr*) &cli_addr, &clilen);
    if(client_socket_descriptor < 0){
      printf("Error on accept (server)\n");
      return 0;
    }
    else {
      int message_size = 200;
      char message[message_size] = {0};
      message[0] = 6;
      strcpy(&message[1], "gdyś jej ścieżki powycinał żelaznymi łzami.");
      write(client_socket_descriptor, message, message_size);
      printf("Sent poem verse to peer on ip adress: %s\n", inet_ntoa(cli_addr.sin_addr));
      close(client_socket_descriptor);
    }
  }
  close(socket_descriptor);
  return 0;
}
