//Name: Jackson E. Rollins
//Date: 3/10/2022
//ID: 932932878

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

//Main function that takes in the user arguments to generate a random key.
int main(int argc, char* argv[]){
    srand(time(NULL));

    if(argc != 2){
        printf("Invalid number of arguments!");
        return EXIT_SUCCESS;
    }

    int length = atoi(argv[1]);
    char key[length + 1];
    char* array = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

    for(int i = 0; i < length; i++){
        key[i] = array[random() % 27];
    }

    key[length] = '\0';
    printf("%s\n", key);

    return 0;
}