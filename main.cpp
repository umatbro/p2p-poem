#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> //write
#include <string.h>
#include <pthread.h>
#include "functions.h"

void *get_response_from_ip(char* ip, int port_number){
  int socket_descriptor;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  int buffer_size = 200;
  char buffer[buffer_size] = {0};

  socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_descriptor < 0){
    printf("Error creating socket\n");
    return 0;
  }
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port_number);
  serv_addr.sin_addr.s_addr =  inet_addr(ip);//INADDR_ANY;


  if(connect(socket_descriptor, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == 0){
    printf("Connected to the server %s:%d\n", ip, port_number);
  }
  char message[buffer_size];
  while(*buffer == 0){
    recv(socket_descriptor, buffer, buffer_size, 0);
    strcpy(message,buffer);
    if(strcmp(buffer,"exit") != 0) {
      //clear array
      for(int i = 0; i < buffer_size; i++){
        buffer[i] = 0;
      }
    }

    printf("received message: %s\n", message);
  }
  write(socket_descriptor, "odp", 4);

  close(socket_descriptor);
}

int main(int argc, char* argv[]){
  get_response_from_ip("192.168.0.199", 10554);
  return 0;
}
