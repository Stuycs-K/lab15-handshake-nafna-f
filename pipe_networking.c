#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  int from_client = 0;
  //creating the well known pipe (WKP)
  if (mkfifo("WKP", 0650) == -1){
    printf("server_setup: wkp mkfifo error: %d: %s\nreturning -1\n", errno, strerror(errno));
    return -1;
  }
  printf("server_setup: wkp created\nopening wkp for read, hanging until connection\n");
  //opening the well known pipe (WKP) - read only
  int fd = open("WKP", O_RDONLY); //blocks until write mode is opened
  if (fd == -1){
      printf("server_setup: wkp open error: %d: %s\nreturning -1\n", errno, strerror(errno));
      return -1;
  }
  printf("server_setup: wkp successfully connected\ndeleting wkp descriptor...\n");
  
  return from_client;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int from_client;
  server_setup();
  return from_client;
}

/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server;
  //grab pid
  int pid = getpid();
  char * pidC = malloc(6);
  sprintf(pidC, "%d", pid);
  //create named private pipe (name is client pid)
  if (mkfifo(pidC, 0650) == -1){
    printf("client_handshake: pid mkfifo error: %d: %s\nreturning -1\n", errno, strerror(errno));
    return -1;
  }
  printf("client_handshake: pp created\nopening wkp\n");
  int fd = open("WKP", O_WRONLY); //should unblock both ends
  if (fd == -1){
      printf("client_handshake: wkp open error: %d: %s\nreturning -1\n", errno, strerror(errno));
      return -1;
  }
  printf("client_handshake: wkp successfully connected\nwriting pp to wkp\n");
  write(fd, pidC, 6); //write the private pipe to the wkp
  //write pp to wkp
  return from_server;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}
