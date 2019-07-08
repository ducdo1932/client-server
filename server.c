#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <ctype.h>
#define kPort 8080 

int main(int argc, char const *argv[]) 
{ 
	
    int kServer_fd, kNew_socket, kValread; 
    struct sockaddr_in address; 
    int kOpt = 1; 
    int kAddrlen = sizeof(address); 
       char *kHello = "Hello from server";
    int kContinu = 1;
    //tao socket
    // tao file mo ta soket
    if ((kServer_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    }  
    //gan dia chi cho socket
    // gan cong port 8080 
    if (setsockopt(kServer_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &kOpt, sizeof(kOpt))) 
    { 
        perror("SetSockOpt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( kPort );  //gan cong la 8080   
    // bind 
    if (bind(kServer_fd, (struct sockaddr_in *)&address, sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }
    //listen, chi dinh socket lang nghe ket noi
    if (listen(kServer_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    //accept, chap nhan ket noi
    if ((kNew_socket = accept(kServer_fd, (struct sockaddr_in *)&address,(socklen_t*)&kAddrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
   while(kContinu == 1){  
	// gui tn
char Mess_from_serv[255]={0};
char Buffer[1024] = {0};
printf("nhap tin nhan cho client: ");
		gets(Mess_from_serv);
		fflush(stdin);
		kHello= &Mess_from_serv;
	    send(kNew_socket, kHello, strlen(kHello), 0 ); 
		//chao tam biet
		if(strcmp(Mess_from_serv,"bye")==0)
		{
		kContinu=0;
		close(kNew_socket);
		}
		fflush(stdin);
// lay va in ra dia chi ip  
		
	char Str_cli_ip[INET_ADDRSTRLEN];
	    struct sockaddr_in* ip_client = (struct sockaddr_in*)&address;
	    inet_ntop(AF_INET, &ip_client->sin_addr, Str_cli_ip, INET_ADDRSTRLEN);
	    printf("                         ipclient: %s,", Str_cli_ip );
//

//lay va in ra port
	    char Str_cli_port[INET_ADDRSTRLEN];
	    printf("port: %d\n", ntohs(ip_client->sin_port));
	    printf("                         Tin nhan ban nhan dc tu client: \n");
	    //read, doc du lieu gan vao bien kValread tra ve so byte ma no doc duoc
	    kValread = read( kNew_socket, Buffer, 1024);
	    //viet hoa
	    ToUp(Buffer); 
	    //gan bien hello tra ve cho client la Buffer da viet hoa
	    
	    printf("                            %s\n",Buffer ); 

    }
    close(kNew_socket);
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
