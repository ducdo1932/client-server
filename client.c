#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
   
int main(int argc, char const *argv[]) 
{ 
    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client";
    char add[225];
    int continu = 1;
    printf("Nhap dia chi server\n");
    gets(add);
    //tao socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, add, &serv_addr.sin_addr) <= 0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
    // connect
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    while(continu == 1){
        char mess_from_client[225]={0};
	char buffer[1024] = {0};
        printf("Nhap noi dung tin nhan gui den server\n");
        gets(mess_from_client);
        fflush(stdin);
        hello = &mess_from_client;
        
        send(sock , hello , strlen(hello) , 0 ); 
///
	if (strcmp(mess_from_client, "bye") == 0)
        {
            continu = 0;
	close(sock);
        }
        fflush(stdin);
	printf("                   Tin nhan ban nhan dc tu server: \n");
        // printf("Hello message sent\n"); 
        valread = read( sock , buffer, 1024); 
 	//ToUp(buffer);
        printf("                   %s\n",buffer );
        
      

    }
    close(sock);
    return 0; 
} 

