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
  // printf("Zaczynam przeszukiwać adresy: 192.160.102.*\n");
  // char response[LINE_LENGTH] = {0};
  // std::thread t(get_response_from_ip, (char*)"192.168.0.199", 10000, response);
  // t.join();
  // printf("%s - wynik\n", response);
  // add_verse(response[0], &response[1]);

  std::thread server_thread(server, port_num);
  std::thread menu(disp_menu, port_num);

  server_thread.join();
  return 0;
}
