#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <ctype.h>
#define PORT 8080 

int main(int argc, char const *argv[]) 
{ char *test;
	
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
       char *hello = "Hello from server";
    int continu = 1;
    //tao socket
    // tao file mo ta soket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    }  
    //gan dia chi cho socket
    // gan cong port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT );  //gan cong la 8080   
    // bind 
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }
    //listen, chi dinh socket lang nghe ket noi
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    //accept, chap nhan ket noi
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
   while(continu == 1){  
	// gui tn
char mess_from_serv[255]={0};
char buffer[1024] = {0};
printf("nhap tin nhan cho client: ");
		gets(mess_from_serv);
		fflush(stdin);
		hello= &mess_from_serv;
	    send(new_socket, hello, strlen(hello), 0 ); 
		//chao tam biet
		if(strcmp(mess_from_serv,"bye")==0)
		{
		continu=0;
		close(new_socket);
		}
		fflush(stdin);
// lay va in ra dia chi ip  
		
	char str_cli_ip[INET_ADDRSTRLEN];
	    struct sockaddr_in* ip_client = (struct sockaddr_in*)&address;
	    inet_ntop(AF_INET, &ip_client->sin_addr, str_cli_ip, INET_ADDRSTRLEN);
	    printf("                         ipclient: %s,", str_cli_ip );
//

//lay va in ra port
	    char str_cli_port[INET_ADDRSTRLEN];
	    printf("port: %d\n", ntohs(ip_client->sin_port));
	    printf("                         Tin nhan ban nhan dc tu client: \n");
	    //read, doc du lieu gan vao bien valread tra ve so byte ma no doc duoc
	    valread = read( new_socket, buffer, 1024);
	    //viet hoa
	    ToUp(buffer); 
	    //gan bien hello tra ve cho client la buffer da viet hoa
	    
	    printf("                            %s\n",buffer ); 

    }
    close(new_socket);
    return 0; 
} 

void ToUp( char *p ) 
{ 
	while( *p ) 
	{ 
		*p=*p; 
		p++; 
	} 
} 
