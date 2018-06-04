#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#define BUFFEr_SIZE 4096

void error(char *msg)
{
  perror(msg);
  exit(0);
}

int main(int argc, char *argv[])
{
 int sockfd, portno, n;
 struct sockaddr_in serv_addr;
 struct hostent *server;

 char buffer[BUFFEr_SIZE];
 if (argc < 3) {
    fprintf(stderr,"usage %s hostname port\n", argv[0]);
    exit(0);
 }
 portno = atoi(argv[2]);
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) 
    error("ERROR opening socket");
server = gethostbyname(argv[1]);
if (server == NULL) {
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
}

bzero((char *) &serv_addr, sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
bcopy((char *)server->h_addr, 
     (char *)&serv_addr.sin_addr.s_addr,
     server->h_length);
serv_addr.sin_port = htons(portno);
if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0) 
    error("ERROR connecting");

n = read(sockfd,buffer,BUFFEr_SIZE-1);
if (n < 0) 
     error("ERROR reading from socket");
printf("%s\n",buffer);

bzero(buffer,BUFFEr_SIZE);

/*------------------------------*/
printf("\nDONE\n");
printf("EHLO");

strcpy(buffer,"ehlo smtp.gmail.com\n");

n = write(sockfd,buffer,strlen(buffer));
if (n < 0) 
     error("ERROR writing to socket");
bzero(buffer,BUFFEr_SIZE);
n = read(sockfd,buffer,BUFFEr_SIZE-1);
if (n < 0) 
     error("ERROR reading from socket");
printf("%s\n",buffer);

/*------------------------------*/    

/*------------------------------*/
printf("\nDONE EHLO\n");
printf("AUTH");

strcpy(buffer,"AUTH LOGIN\n");

n = write(sockfd,buffer,strlen(buffer)+1);
if (n < 0) 
     error("ERROR writing to socket");
bzero(buffer,BUFFEr_SIZE);
n = read(sockfd,buffer,BUFFEr_SIZE-1);
if (n < 0) 
     error("ERROR reading from socket");
printf("%s\n",buffer);

/*------------------------------*/ 

/*------------------------------*/
printf("\nDONE AUTH\n");
printf("AUTH UID");

strcpy(buffer,"xxxx@gmail.com");

n = write(sockfd,buffer,strlen(buffer));
if (n < 0) 
     error("ERROR writing to socket");
bzero(buffer,BUFFEr_SIZE);
n = read(sockfd,buffer,BUFFEr_SIZE-1);
if (n < 0) 
     error("ERROR reading from socket");
printf("%s\n",buffer);

/*------------------------------*/ 

/*------------------------------*/
printf("\nDONE UID\n");
printf("AUTH PWD");

strcpy(buffer,"xxxxxx");

n = write(sockfd,buffer,strlen(buffer)+1);
if (n < 0) 
     error("ERROR writing to socket");
bzero(buffer,BUFFEr_SIZE);
n = read(sockfd,buffer,BUFFEr_SIZE-1);
if (n < 0) 
     error("ERROR reading from socket");
printf("%s\n",buffer);

/*------------------------------*/ 

/*------------------------------*/

printf("MAIL FROM");

strcpy(buffer,"MAIL FROM: xxxxx@gmail.com");

n = write(sockfd,buffer,strlen(buffer));
if (n < 0) 
     error("ERROR writing to socket");
bzero(buffer,BUFFEr_SIZE);
n = read(sockfd,buffer,BUFFEr_SIZE-1);
if (n < 0) 
     error("ERROR reading from socket");
printf("%s\n",buffer);

/*------------------------------*/ 

/*------------------------------*/

 printf("MAIL TO");


strcpy(buffer,"RCPT TO: aaaaa@gmail.com");

n = write(sockfd,buffer,strlen(buffer));
if (n < 0) 
     error("ERROR writing to socket");
bzero(buffer,BUFFEr_SIZE);
n = read(sockfd,buffer,BUFFEr_SIZE-1);
if (n < 0) 
     error("ERROR reading from socket");
printf("%s\n",buffer);

/*------------------------------*/       

/*------------------------------*/
printf("DONE MAILTO\n");

printf("DATA");

strcpy(buffer,"DATA\r\n");

n = write(sockfd,buffer,strlen(buffer));

strcpy(buffer,"Subject: test\r\n");

n = write(sockfd,buffer,strlen(buffer));

strcpy(buffer,"SMTP MAIL TOOL TEST WORKS!!!\r\n");

n = write(sockfd,buffer,strlen(buffer));

strcpy(buffer,"\n\n");

n = write(sockfd,buffer,strlen(buffer));

strcpy(buffer,".\n");

n = write(sockfd,buffer,strlen(buffer));


/*------------------------------*/ 

/*------------------------------*/ 
printf("SON DONE");
strcpy(buffer,"quit\n");

n = write(sockfd,buffer,strlen(buffer));
if (n < 0) 
     error("ERROR writing to socket");
bzero(buffer,BUFFEr_SIZE);
n = read(sockfd,buffer,BUFFEr_SIZE-1);
if (n < 0) 
     error("ERROR reading from socket");
puts(buffer);

/*------------------------------*/

return 0;
}
