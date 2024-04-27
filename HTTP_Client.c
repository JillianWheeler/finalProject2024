#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\n\nHello, world! Method: %s, URL: %s, Protocol: %s\n\n";
    char buffer[1024] = {0};
    char method[17], url[1025], protocol[17]; // Method, URL, and Protocol variables with specified lengths
    ssize_t read_size;
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    send(sock , hello , strlen(hello) , 0 );
    printf("GET message sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );

    // Read the server response
    valread = read(sock, buffer, sizeof(buffer));
    printf("Server Response:\n%s\n", buffer);
    
    close(sock);
    
    return 0;
}
