#include "functions.h"
#include "poem.h"

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
  serv_addr.sin_addr.s_addr = inet_addr(ip);


  if(connect(socket_descriptor, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == 0){
    printf("<cli> Connected to the server %s:%d\n", ip, port_number);

    /*https://stackoverflow.com/questions/37502281/c-sockets-close-connection-if-no-response*/
    int ret;
    fd_set set;
    struct timeval timeout;
    /* Initialize the file descriptor set. */
    FD_ZERO(&set);
    FD_SET(socket_descriptor, &set);
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    recv(socket_descriptor, buffer, buffer_size, 0);
    sprintf(response, "%s", buffer);
  } else {
    //printf("<cli> Connection with %s:%d not succeeded\n", ip, port_number);
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

void disp_menu(int port_number){
  char cmd[50] = {0};

  while(strcmp(cmd, "exit") != 0)
  {
    printf("cmd> ");
    memset(cmd, 0, sizeof(cmd));
    scanf("%s",cmd);
    if(strcmp(cmd,"help") == 0){
      printf("------------------------------------\n");
      printf("POMOC\n");
      printf("Dostepne komendy:\n");
      printf("show - pokaż dotychczas zebrana tresc wiersza\n");
      printf("search - szukaj wersow p2p\n");
      printf("exit - wyjscie z programu\n");
      printf("------------------------------------\n");
    }
    else if (strcmp(cmd,"search") == 0) {
      printf("Zaczynam przeszukiwać adresy: 192.160.102.*\n");
      char ip[] = "192.168.0.";
      search_range(ip, port_number, 50, 170);
    }
    else if (strcmp(cmd,"show") == 0){
      show_poem();
    }
    else {
      printf("Bledna komenda. Wpisz \"help\" po pomoc.\n");
    }
  }
  std::terminate();
  return ;
}

void search_range(char *ip, int port_number, int range_begin, int range_end){
  int threads_number = range_end - range_begin;
  std::thread threads[threads_number];

  char response[threads_number][LINE_LENGTH] = {0}; // tablica przechowująca wynik działania kazdego z wątków

  int iterator = 0;
  for(int i = range_begin; i <= range_end; i++){
    char suffix[3];
    sprintf(suffix, "%d", i);
    char whole_ip[sizeof(ip) + 3];
    strcpy(whole_ip, ip);
    strcat(whole_ip, suffix);
    threads[iterator] = std::thread(get_response_from_ip, whole_ip, port_number, response[iterator]);
    iterator++;
  }
  for(int i = 0; i < threads_number; i++){
    threads[i].join();
    if(strlen(response[i]) != 0){
      add_verse(response[i][0], &response[i][1]);
    }
  }
  printf("Zakonczono przeszukiwanie\n");
}
