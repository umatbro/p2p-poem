#include "functions.h"

int test = 10;

void get_response_from_ip(char* ip, int port_number, char* response){
  int socket_descriptor;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  int buffer_size = 200;
  char buffer[buffer_size] = {0};

  socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_descriptor < 0){
    printf("<cli> Error creating socket\n");
    return ;
  }
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port_number);
  serv_addr.sin_addr.s_addr =  inet_addr(ip);//INADDR_ANY;


  if(connect(socket_descriptor, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == 0){
    printf("<cli> Connected to the server %s:%d\n", ip, port_number);
    recv(socket_descriptor, buffer, buffer_size, 0);
    sprintf(response, "%s", buffer);
    //printf("Response: \"%s\"", &response[1]);
  } else {
    printf("Connection with %s:%d not succeeded\n", ip, port_number);
  }

  close(socket_descriptor);
}

void server(int port_number){
  int socket_descriptor;
  int client_socket_descriptor;
  //int port_number;
  int buffer_size = 200;
  char buffer[buffer_size] = {0};
  struct sockaddr_in serv_addr, cli_addr;

  int option = 1;
  socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)); // so there is no error on reusing socket while after

  if(socket_descriptor < 0){
    printf("<srv> Error opening socket (server)\n");
    return ;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port_number);

  if(bind(socket_descriptor, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){
      printf("<srv> Error bindig a socket (server)\n");
      return ;
  }

  printf("<srv> Server listening  on port %d...\n", port_number);
  while(1){
    listen(socket_descriptor, 5);
    socklen_t clilen;
    clilen = sizeof(cli_addr);
    client_socket_descriptor = accept(socket_descriptor, (struct sockaddr*) &cli_addr, &clilen);
    if(client_socket_descriptor < 0){
      printf("<srv> Error on accept (server)\n");
      return ;
    }
    else {
      int message_size = 200;
      char message[message_size] = {0};
      message[0] = 6;
      strcpy(&message[1], "gdyś jej ścieżki powycinał żelaznymi łzami.");
      write(client_socket_descriptor, message, message_size);
      printf("\n<srv> Sent poem verse to peer on ip adress: %s\n", inet_ntoa(cli_addr.sin_addr));
      close(client_socket_descriptor);
    }
  }
  close(socket_descriptor);
}

void disp_menu(){
  char cmd[50] = {0};

  while(strcmp(cmd, "exit") != 0)
  {
    printf("cmd> ");
    memset(cmd, 0, sizeof(cmd));
    scanf("%s",cmd);
    if(strcmp(cmd,"help") == 0){
      printf("POMOC\n----------------");
      printf("\nDostepne komendy:\nexit - wyjscie z programu\n\n");
    }
  }
  return ;
}
