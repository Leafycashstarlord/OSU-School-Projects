//Name: Jackson E. Rollins
//Date: 3/10/2022
//ID: 932932878

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <netdb.h>
#include <signal.h>

//Function that converts a characters into an integer
int ctoi(char c){
    if(c == ' '){
        return 26;
    }else{                            
        return (c - 'A');
    }
}

//Function that validates wether or not a string has valid characters in it
int validation(char* string){
    for(int i = 0; i < strlen(string) - 1; i++){
        if((ctoi(string[i]) < 0) || (ctoi(string[i]) > 27)){
            return -1;
        }
    }
    return strlen(string);
}

// Error function used for reporting issues
void error(const char *msg) { 
    perror(msg); 
    exit(0); 
} 

// Set up the address struct
void setupAddressStruct(struct sockaddr_in* address, int portNumber, char* hostname){

    // Clear out the address struct
    memset((char*) address, '\0', sizeof(*address)); 

    // The address should be network capable
    address->sin_family = AF_INET;
    // Store the port number
    address->sin_port = htons(portNumber);

    // Get the DNS entry for this host name
    struct hostent* hostInfo = gethostbyname(hostname); 
        if (hostInfo == NULL) { 
        fprintf(stderr, "CLIENT: ERROR, no such host\n"); 
        exit(0); 
    }
    // Copy the first IP address from the DNS entry to sin_addr.s_addr
    memcpy((char*) &address->sin_addr.s_addr, hostInfo->h_addr_list[0], hostInfo->h_length);
}

//Main function that runs the decryption client
int main(int argc, char *argv[]) {
    struct sockaddr_in serverAddress;
    int clientSock;
    char hostName[] = "localhost";
    FILE* ptFile;
    FILE* ktFile;
    char message[140000], cipherText[70000], recBuff[70000], keyText[70000];
    char mLENGTH[1024];
    int msgLength;
    char confirm[] = "Decrypt";
    int received, left, sent;

    // Check usage & args
    if (argc < 4) { 
        fprintf(stderr,"USAGE: %s hostname port\n", argv[0]); 
        exit(0); 
    } 

    // Create a socket
    clientSock = socket(AF_INET, SOCK_STREAM, 0); 
    if (clientSock < 0){
        error("CLIENT: ERROR opening socket\n");
    }

    // Set up the server address struct
    setupAddressStruct(&serverAddress, atoi(argv[3]), hostName);

    // Connect to server
    if (connect(clientSock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
        error("CLIENT: ERROR connecting");
    }

    memset(cipherText, '\0', 70000);
    memset(keyText, '\0', 70000);
    memset(message, '\0', 70000);

    //Grabbing the plaintext and keytext
    ptFile = fopen(argv[1], "r");
    fgets(cipherText, 140000, ptFile);
    ktFile = fopen(argv[2], "r");
    fgets(keyText, 140000, ktFile);

    //Checking the validity of the plaintext and keytext
    if(strlen(keyText) < strlen(cipherText)){
        perror("CLIENT: ERROR key too small");
        exit(EXIT_FAILURE);
    }

    if(validation(cipherText) < 0){
        perror("CLIENT: ERROR invalid cipherText");
        exit(EXIT_FAILURE);
    }
    if(validation(keyText) < 0){
        perror("CLIENT: ERROR invalid key");
        exit(EXIT_FAILURE);
    }

    //Create the message to be sent to the decryption server
    strcat(message, cipherText);
    strcat(message, keyText);

    msgLength = strlen(message);
    sprintf(mLENGTH, "%d", msgLength);

    //Send the message to the server with the message length
    sent = send(clientSock, mLENGTH, strlen(mLENGTH), 0);
    if(sent < 0){
        perror("CLIENT: ERROR sending to server");
        exit(EXIT_FAILURE);
    }

    //Get the confirmation message from the server
    memset(recBuff, '\0', 70000);
    recv(clientSock, recBuff, 70000, 0);
    if(strcmp(recBuff, confirm) != 0){
        perror("CLIENT: ERROR wrong server");
        exit(EXIT_FAILURE);
    }
    memset(recBuff, '\0', 70000);

    //Send the message to the server
    sent = 0;
    left = msgLength;
    int j;
    while(sent < left){
        j = send(clientSock, message + sent, left, 0);
        if(j == -1){
            perror("CLIENT: ERROR on data sending");
            exit(EXIT_FAILURE);
        }
        sent += j;
        left -= j;
    }

    if(sent < 0){
        perror("CLIENT: ERROR sending to server");
        exit(EXIT_FAILURE);
    }

    //Retrieve the message from the server
    memset(recBuff, '\0', 70000);
    msgLength = strlen(cipherText) - 1;
    received = 0;
    left = msgLength;
    while(received < msgLength){
        j = recv(clientSock, recBuff + received, left, 0);
        if(j == -1){
            perror("ERROR on data reception");
            exit(EXIT_FAILURE);
        }
        received += j;
        left -= j;
    }
    printf("%s\n", recBuff);

    //Close the socket
    close(clientSock);
    return 0;
}