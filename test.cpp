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
