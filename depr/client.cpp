#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> //write
#include <string.h>

int main(int argc, char* argv[]){
  int socket_descriptor;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  int port_number = 10554;
  int buffer_size = 200;
  char buffer[buffer_size] = {0};
  //char* ip = "192.168.0.199";
  char* ip = "127.0.0.1";

  socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_descriptor < 0){
    printf("Error creating socket (client)\n");
    return 1;
  }
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port_number);
  serv_addr.sin_addr.s_addr =  inet_addr(ip);//INADDR_ANY;


  if(connect(socket_descriptor, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == 0){
    printf("Connected to the server port number: %d\n", port_number);
  }
  char message[buffer_size];
  while(*buffer == 0){
    recv(socket_descriptor, buffer, buffer_size, 0);
    strcpy(message,buffer);
    if(strcmp(buffer,"exit") != 0) {
      //clear array
      // for(int i = 0; i < buffer_size; i++){
      //   buffer[i] = 0;
      // }
      bzero(buffer, buffer_size);
    }

    printf("received message:%d. %s\n", message[0], &message[1]);
  }
  write(socket_descriptor, "odp", 4);

  close(socket_descriptor);
  return 0;
}
