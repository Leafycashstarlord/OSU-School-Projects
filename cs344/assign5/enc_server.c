//Jackson E. Rollins
//Date: 3/10/2022
//ID: 932932878

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <netdb.h>
#include <signal.h>

//Function that converts an integer into a character
char itoc(int i){
    i -= 1;
    if (i == 26){
        return ' ';
    }else{
        return (i + 65);
    }
}

//Function that converts a characters into an integer
int ctoi(char c){
    if(c == ' '){
        return 27;
    }else{
        return (c - 65) + 1;
    }
}

//Function that takes the plaintext and keytext, and encrypts it into the ciphertext
int encrypt(char* plainText, char* cipherText, char* keyText){
    int num, i = 0;
    while(plainText[i] != '\0'){
        int plain = ctoi(plainText[i]);
        int keyT = ctoi(keyText[i]);
        num = plain + keyT;

        if(num > 27)
        {
            num-= 27;
        }
        cipherText[i] = itoc(num);
        i++;
    }
    cipherText[i++] = '\n';
    cipherText[i] = '\0';

    return strlen(cipherText);
}

// Error function used for reporting issues
void error(const char *msg) {
    perror(msg);
    exit(1);
} 

// Set up the address struct for the server socket
void setupAddressStruct(struct sockaddr_in* address, int portNumber){
    // Clear out the address struct
    memset((char*) address, '\0', sizeof(*address)); 
    // The address should be network capable
    address->sin_family = AF_INET;
    // Store the port number
    address->sin_port = htons(portNumber);
    // Allow a client at any address to connect to this server
    address->sin_addr.s_addr = INADDR_ANY;
}

//Main function that runs the encryption server
int main(int argc, char *argv[]){
    struct sockaddr_in serverAddress, clientAddress;
    int serverSock, connectSock;
    socklen_t clientSize = sizeof(clientAddress);
    int msgSize;
    int pidStatus;
    pid_t pid;
    char plainText[70000], keyText[70000], cipherText[70000];
    char buffer[1024];
    char msgBuffer[140000];
    int bufferSize;
    char* contextptr;
    char confirm[] = "Encrypt";
    ssize_t sendSize;
    int received, left, sent;

    // Check usage & args
    if (argc < 2) { 
        fprintf(stderr,"USAGE: %s port\n", argv[0]); 
        exit(1);
    } 

    // Set up the address struct for the server socket
    setupAddressStruct(&serverAddress, atoi(argv[1]));

    // Create the socket that will listen for connections
    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock < 0) {
        error("ERROR opening socket");
    }

    // Associate the socket to the port
    if (bind(serverSock, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
        error("ERROR on binding");
    }

    // Start listening for connetions. Allow up to 5 connections to queue up
    listen(serverSock, 5); 
  
    // Accept a connection, blocking if one is not available until one connects
    while(1){
        // Accept the connection request which creates a connection socket
        connectSock = accept(serverSock, (struct sockaddr *)&clientAddress, &clientSize); 
        if (connectSock < 0){
            perror("ERROR on accept");
            continue;
        }

        //Fork the server
        pid = fork();
        switch(pid){
            //Error case
            case -1:
                perror("ERROR on forking");
                break;
            
            //Case that runs the server
            case 0:
                memset(buffer, '\0', 1024);
                memset(plainText, '\0', 70000);
                memset(msgBuffer, '\0', 140000);
                bufferSize = 0;
                char* token;

                //Receive message form client with length
                bufferSize += recv(connectSock, buffer, 1024, 0);
                msgSize = atoi(buffer);
                send(connectSock, confirm, strlen(confirm), 0);

                //Recieve message into buffer
                received = 0;
                left = msgSize;
                int j;
                while(received < msgSize){
                    j = recv(connectSock, buffer + received, left, 0);
                    if(j == -1){
                        perror("ERROR on data reception");
                        exit(EXIT_FAILURE);
                    }
                    received += j;
                    left -= j;
                }

                //Split the different strings that came form the client
                token = strtok_r(buffer, "\n", &contextptr);
                strcpy(plainText, token);
                token = strtok_r(NULL, "\n", &contextptr);

                //Encrypt the plaintext into the ciphertext
                sendSize = encrypt(plainText, cipherText, token);

                //Send the encrypted message back to the clinet
                sent = 0;
                left = sendSize;
                j = 0;
                while(sent < sendSize){
                    j = send(connectSock, cipherText, sendSize, 0);
                    if(j == -1){
                        perror("ERROR on data reception");
                        exit(EXIT_FAILURE);
                    }
                    sent += j;
                    left -= j;
                }

                //Close the connection socket
                close(connectSock);
                break;

            //Default Case
            default:
                pid = waitpid(pid, &pidStatus, WNOHANG);
                break;
        }
    }

    //Close the server socket
    close(serverSock);
    return 0;
}