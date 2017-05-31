#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>



int main (int argc, const char* argv[])
{
  for (int i = 0; i < 50; i++){
    char* ip ="127.0.0.";
    char whole_ip[20];
    sprintf(whole_ip, "%s%d", ip, i);
    printf("%s\n", whole_ip);
  }
  return 0;
}


void disp_menu(int port_number){
  char cmd[50] = {0};
  std::thread t1;
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
      printf("Zaczynam przeszukiwać adresy: 192.168.102.*\n");
      char ip[] = "192.168.0.";
      t1 = std::thread(search_range, ip, port_number, RANGE_BEGIN, RANGE_END);
    }
    else if (strcmp(cmd,"show") == 0){
      show_poem();
    }
    else {
      printf("Bledna komenda. Wpisz \"help\" po pomoc.\n");
    }

  }
  t1.join();
  std::terminate();
  return ;
}
