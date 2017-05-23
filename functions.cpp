#include "functions.h"

void *get_response_from_ip(char* ip, int port_number, char* response){
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
  recv(socket_descriptor, buffer, buffer_size, 0);
  strcpy(message,buffer);
  sprintf(response, "%s", message);

  close(socket_descriptor);
}
