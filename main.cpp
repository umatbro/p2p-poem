#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> //write
#include <string.h>
#include <pthread.h>
#include <thread>
#include "functions.h"


int main(int argc, char* argv[]){
  if(argc != 2){
    printf("Usage: ./p2p <port_number>\n");
    return 0;
  }
  int port_num = atoi(argv[1]);
  printf("Port number: %d\n", port_num);
  char message[200] = {0};
  std::thread server_thread(server, port_num);
  std::thread menu(disp_menu);
  // get_response_from_ip("192.168.0.19", port_num, message);
  // printf("message: %d. %s\n", message[0], &message[1]);
  // printf("%d\n", test);

  server_thread.join();
  return 0;
}
