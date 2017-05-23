//funckje

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
