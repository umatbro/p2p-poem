#pragma once
#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> //write
#include <string.h>
#include <pthread.h>
#include <thread>

extern int test;
void get_response_from_ip(char* ip, int port_number, char* response);
void server(int port_number);
void disp_menu();



#endif
