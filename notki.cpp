/*
  ŹRÓDŁA
  sockety
  http://www.beej.us/guide/bgnet/output/html/singlepage/bgnet.html
  http://www.binarytides.com/socket-programming-c-linux-tutorial/
  http://www.linuxhowtos.org/C_C++/socket.htm
  https://solarianprogrammer.com/2011/12/16/cpp-11-thread-tutorial/   - wątki
  https://stackoverflow.com/questions/37502281/c-sockets-close-connection-if-no-response


*/


//funckje

//stworzenie socket descriptora
socket_desc = socket(AF_INET, SOCK_STREAM, 0);

bind (int socket_descriptor,
      (struct sockaddr*) &server_addr,
      sizeof(server_addr));


struct sockaddr_in serv_addr;
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(port_number);
serv_addr.sin_addr.s_addr = INADDR_ANY;

//odpowiedz
write(socket_descriptor, "odp", 4);
recv(socket_descriptor, buffer, buffer_size, 0);
