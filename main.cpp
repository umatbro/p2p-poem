#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> //write
#include <string.h>
#include <pthread.h>
#include <thread>
#include "functions.h"
#include "poem.h"


int main(int argc, char* argv[]){
  if(argc != 2){
    printf("Usage: ./p2p <port_number>\n");
    return 0;
  }
  int port_num = atoi(argv[1]);
  printf("Port number: %d\n", port_num);

  // dodaj znany wiersz to tablicy
  init_poem();

  std::thread server_thread(server, port_num);
  std::thread menu(disp_menu, port_num);

  server_thread.join();
  return 0;
}
