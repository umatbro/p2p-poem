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

#define RANGE_BEGIN 170
#define RANGE_END 220

void get_response_from_ip(char* ip, int port_number, char* response);
void server(int port_number);
void disp_menu(int port_number);
void search_range(char* ip, int port_number, int range_begin, int range_end);

#endif
