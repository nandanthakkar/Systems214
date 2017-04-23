#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

struct sockaddr_in *SD = NULL;
int sizeofSD = 0;
char* HOST_NAME = NULL;
enum error_msgs{
	HOST_NOT_FOUND = -1
};

enum flag{
	EACCES = 100, EINTR = 200, EISDIR = 300, ENOENT = 400, EROFS = 500

};

int netserverinit(char * hostname){
	int sockfd, n, portno;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   
   //extract port number
   int colonLoc = -1;
   for(colonLoc = 0; hostname[colonLoc] !=':' || hostname[colonLoc] !='\0'; colonLoc++);
   
   //if no colon, return failure
   if(colonLoc == strlen(hostname)){
      perror("ERROR connecting");
	  errno = HOST_NOT_FOUND;
	  perror(errno);
      return HOST_NOT_FOUND;// dont forget to set error know
   }
   
    //actually get the number
	char port_buffer[6];
	bzero(&port_buffer, 6);
	int index=0;
	for(colonLoc+=1; colonLoc <= strlen(hostname); colonLoc++, index++){
		port_buffer[index] = hostname[colonLoc];
	}
	
	portno = atoi(port_buffer);
   
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   
   server = gethostbyname(hostname);
   
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(portno);
   
   /* Now connect to the server */
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
	  errno = HOST_NOT_FOUND;
	  perror(errno);
      return HOST_NOT_FOUND;// dont forget to set error know
   }
   
   //if we get here, set the socket file descriptor & store the host name as a global variable  
   //HOST_NAME is to be used in functions like netread and netwrite
   SD = (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in));
   //SD->in_addr = (struct in_addr*)malloc(sizeof(struct in_addr));
   bzero((char*)&SD, sizeof(struct sockaddr_in));
   SD->sin_family = AF_INET;
   bcopy((char*)server->h_addr, (char*) &SD->sin_addr->s_addr, server->h_length);
   SD->sin_port = htons(portno);
	
   
   //copy the host name sent from the command line 
   HOST_NAME = (char*)malloc(sizeof(char)*strlen(hostname)+1);
   strcpy(HOST_NAME, hostname);
   
   return 0;
}


int netopen(const char *pathname, int flags){
	int sockfd;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
	if (connect(sockfd, SD, sizeof(struct sockaddr_in)) < 0) {
      perror("ERROR connecting");
	  errno = HOST_NOT_FOUND;
	  perror(errno);
      return HOST_NOT_FOUND;// dont forget to set error know
   }
   
	char buffer[256];
	char* str = "/open/";
	int size = 10 + sizeof(HOST_NAME);
	sprintf(buffer, "%d%s%d/%s", size, str, flag,HOST_NAME,);
	
	int n = write(sockfd, buffer, strlen(buffer));
   
   if (n < 0) {
      perror("ERROR writing to socket");
      // dont forget to set errno
	  return -1;
   }
   
   /* Now read server response */
   bzero(buffer,256);
   n = read(sockfd, buffer, 255);
   
   if (n < 0) {
      perror("ERROR reading from socket");
	  //dont forget to set errno
      return -1;
   }
	
   printf("%s\n",buffer);
   
   int separater = 0;
   for(separater = 0; buffer[separater] != '/' || buffer[separater] !='\0'; separater++);
   //buffer = "sizeofbuffer/filedescriptor"
   if(buffer[separater] !='\0'){
	   char * SIZE = (char *)malloc(separater +2);
   }
   else{
	   //error were not able to read completely.
   }
   
   SIZE = bcopy(buffer,SIZE, separater + 1);
   SIZE[separater +1] = '\0';
   
   int i = atoi(SIZE);
   int j = 0;
   for(j =0; (j < i)  & buffer[separater +1+ j] != '\0' ;j++);
   free(SIZE);
   if(j == i-1){
	   i = atoi(buffer[separater +1])
   }
   else{
	   //set errno
	   return -1;
   }
   
   return i;
	
}






int main(int argc, char *argv[]) {
   int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   
   char buffer[256];
   
   if (argc < 3) {
      fprintf(stderr,"usage %s hostname port\n", argv[0]);
      exit(0);
   }
	
   portno = atoi(argv[2]);
   
   /* Create a socket point */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
	
   server = gethostbyname(argv[1]);
   
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(portno);
   
   /* Now connect to the server */
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      exit(1);
   }
   
   /* Now ask for a message from the user, this message
      * will be read by server
   */
	
   printf("Please enter the message: ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   
   /* Send message to the server */
   n = write(sockfd, buffer, strlen(buffer));
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
   
   /* Now read server response */
   bzero(buffer,256);
   n = read(sockfd, buffer, 255);
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
	
   printf("%s\n",buffer);
   return 0;
}

size_t netread(int fildes, void * buf, size_t nbyte){
	int sockfd;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
	if (connect(sockfd, SD, sizeof(struct sockaddr_in)) < 0) {
      perror("ERROR connecting");
	  errno = HOST_NOT_FOUND;
	  perror(errno);
      return HOST_NOT_FOUND;// dont forget to set error know
   }
   
	char buffer[256];
	char* str = "/read/";
	char * fd = itoa(fildes);
	char * n = itoa(fildes);
	
	int size = 8 + sizeof(fd) + size(n);
	sprintf(buffer, "%d%s/%s/%s", size, str, fd, n);
	
	int n = write(sockfd, buffer, strlen(buffer));
   
   if (n < 0) {
      perror("ERROR writing to socket");
      // dont forget to set errno
	  return -1;
   }
   
   /* Now read server response */
   bzero(buffer,256);
   n = read(sockfd, buffer, 255);
   
   if (n < 0) {
      perror("ERROR reading from socket");
	  //dont forget to set errno
      return -1;
   }
	
   printf("%s\n",buffer);
   
   int separater = 0;
   for(separater = 0; buffer[separater] != '/' || buffer[separater] !='\0'; separater++);
   //buffer = "sizeofbuffer/filedescriptor"
   if(buffer[separater] !='\0'){
	   char * SIZE = (char *)malloc(separater +2);
   }
   else{
	   //error were not able to read completely.
	   return -1;
   }
   
   SIZE = bcopy(buffer,SIZE, separater + 1);
   SIZE[separater +1] = '\0';
   
   int i = atoi(SIZE);
   bcopy(buffer[separater +1], buf, i);
   
   
   return i;
	
}
