//Name: Jackson E. Rollins
//Date: 2/21/2022
//ID: 932932878

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

void put_buff_1(char *uInput);
void put_buff_2(char *uInput);
void put_buff_3(char *uInput);

//Creates and initializes the variables for the first buffer that shares resources
//between the input threat and the line seperation thread. Referenced from sample program.
char buffer_1[50][1000];
int count_1 = 0;
int prod_idx_1 = 0;
int con_idx_1 = 0;
pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full_1 = PTHREAD_COND_INITIALIZER;

//Creates and initializes the variables for the second buffer that shares resources between 
//the line seperation thread and and caret replacement thread. Referenced from sample program.
char buffer_2[50][1000];
int count_2 = 0;
int prod_idx_2 = 0;
int con_idx_2 = 0;
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full_2 = PTHREAD_COND_INITIALIZER;

//Creates and initializes the variables for the third buffer that shares resources
//between the caret replacement thread and the output thread. Referenced from sample program
char buffer_3[50][1000];
int count_3 = 0;
int prod_idx_3 = 0;
int con_idx_3 = 0;
pthread_mutex_t mutex_3 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full_3 = PTHREAD_COND_INITIALIZER;

//Function to get input from the user. Referenced from sample program.
char *get_user_input(){
	char *uInput = NULL;
	size_t length = 1000;
	getline(&uInput, &length, stdin);
	return uInput;
}

//Function to stop processing the current line. Takes the input and if it is "STOP", 
//then the input gets put into the next buffer.
int stopping(char *uInput, int getBuff){
	if(strcmp(uInput, "STOP\n") == 0){
		if(getBuff == 1){
			put_buff_2(uInput);
		}else if(getBuff == 2){
			put_buff_3(uInput);
		}else if(getBuff == 3){
			return 2;
		}
		return 1;
	}else{
		return 0;
	}
}

//Function to put the user input into the first buffer. Refrenced from sample program.
//Lock the mutex, put the character into the buffer, increment to next character, signal
//if full, and then unlock the mutex.
void put_buff_1(char *uInput){
	pthread_mutex_lock(&mutex_1);
	strcpy(buffer_1[prod_idx_1], uInput);
	prod_idx_1 = prod_idx_1 + 1;
	count_1++;
	pthread_cond_signal(&full_1);
	pthread_mutex_unlock(&mutex_1);
}

//Function that the input thread runs to get the user input. Referenced from sample program.
void *get_input(void *args){
	for (int i = 0; i < 50; i++){
		char *uInput = get_user_input();
		if(strcmp(uInput, "STOP\n") == 0){
			put_buff_1(uInput);
			return NULL;
		}
		put_buff_1(uInput);
		free(uInput);
	}
	return NULL;
}

//Function that gets the characters from the first buffer. Referenced from sample program.
//Locks the mutex, while buffer is empty it waits for a signal that buffer is being filled
//and then picks up characters, increments, unlocks the mutex, returns the characters.
char *get_buff_1(){
	pthread_mutex_lock(&mutex_1);
	while (count_1 == 0){
		pthread_cond_wait(&full_1, &mutex_1);
	}
	char *uInput  = buffer_1[con_idx_1];
	con_idx_1 = con_idx_1 + 1;
	count_1--;
	pthread_mutex_unlock(&mutex_1);
	return uInput;
}

//Function to put the user input into the first buffer. Referenced from sample program.
//Lock the mutex, put the character into the buffer, increment to next character, signal if
//full, and then unlock the mutex.
void put_buff_2(char *uInput){
	pthread_mutex_lock(&mutex_2);
	strcpy(buffer_2[prod_idx_2], uInput);
	prod_idx_2 = prod_idx_2 + 1;
	count_2++;
	pthread_cond_signal(&full_2);
	pthread_mutex_unlock(&mutex_2);
}

//Function that the replace Sep thread runs to replace all the line seperators with a single
//space. Grabs the unput from the buffer, checks to see if there is a stop command, if not
//interates through the input replacing any line seperators with a space.
void *replaceSep(void *args){
	char *uInput;
	for(int i = 0; i < 50; i++){
		uInput = get_buff_1();
		if(stopping(uInput, 1) == 1){
			return NULL;
		}else{
			for(int k = 0; uInput[k] != '\0'; k++){
				if(uInput[k] == '\n'){
					uInput[k] = ' ';
				}
			}
			put_buff_2(uInput);
		}
	}
	return NULL;
}

//Function that get the characters from the second buffer. Referenced from sample program.
//Lock the mutex, while buffer is empty it waits for a signal that buffer is being filled
//and then picks up characters, increments, unlocks the mutex, returns the characters.
char *get_buff_2(){
	pthread_mutex_lock(&mutex_2);
	while (count_2 == 0){
		pthread_cond_wait(&full_2, &mutex_2);
	}
	char *uInput = buffer_2[con_idx_2];
	con_idx_2 = con_idx_2 + 1;
	count_2--;
	pthread_mutex_unlock(&mutex_2);
	return uInput;
}

//Function to put the user input into the third buffer. Referenced from sample program.
//Lock the mutex, put the character into the buffer, increment to next character, signal if
//full, and then unlock the mutex.
void put_buff_3(char *uInput){
	pthread_mutex_lock(&mutex_3);
	strcpy(buffer_3[prod_idx_3], uInput);
	prod_idx_3 = prod_idx_3 + 1;
	count_3++;
	pthread_cond_signal(&full_3);
	pthread_mutex_unlock(&mutex_3);
}

//Functiont hat the replace caret thread runs to replace all the double plus signs with a
//single caret. Grabs the input from the buffer, checks to see if there is a stop command,
//if not it iterates through the input replacing any '++' with a '^'.
void *replaceCaret(void *args){
	char *uInput;
	for(int i = 0; i < 50; i++){
		uInput = get_buff_2();
		if(stopping(uInput, 2) == 1){
			return NULL;
		}else{
			for(int k = 0; uInput[k] != '\0'; k++){
				if(uInput[k] == '+' && uInput[k+1] == '+'){
					uInput[k] = '^';
					for(int j = k + 1; j < 1000; j++){
						uInput[j] = uInput[j + 1];
					}
				}
			}
			put_buff_3(uInput);
		}
	}
	return NULL;
}

//Function that gets the characters from the third buffer. Referenced from sample program.
//Lock the mutex, while the buffer is empty it waits for a signal that buffer is being filled
//and then picks up characters, increments, unlocks the mutex, returns the characters.
char *get_buff_3(){
	pthread_mutex_lock(&mutex_3);
	while(count_3 == 0){
		pthread_cond_wait(&full_3, &mutex_3);
	}
	char *uInput = buffer_3[con_idx_3];
	con_idx_3 = con_idx_3 + 1;
	count_3--;
	pthread_mutex_unlock(&mutex_3);
	return uInput;
}

//Function that output thread runs to give the resulting output from the user. Grabs the
//input, creates an array, checks to see if there is a stop command, if not it iterates
//through the input putting characters into the array, when 79 characters have been placed,
//print out the array, and then repeat.
void *write_output(void *args){
	char *uInput;
	char printArray[80] = {"\0"};
	int index = 0;
	for(int i = 0; i < 50; i++){
		uInput = get_buff_3();
		if(stopping(uInput, 3) == 2){
			return NULL;
		}
		
		for(int k = 0; k < (strlen(uInput)); k++){
			printArray[index] = uInput[k];
			index++;

			if(index > 79){
				printf("%s\n", printArray);
				index = 0;
			}
		}
	}
	return NULL;
}

//Main function that runs the progam. Creates all of the threads, and then runs them until
//they terminate.
int main(){
	pthread_t input_t, replaceSep_t, replaceCaret_t, output_t;

	pthread_create(&input_t, NULL, get_input, NULL);
	pthread_create(&replaceSep_t, NULL, replaceSep, NULL);
	pthread_create(&replaceCaret_t, NULL, replaceCaret, NULL);
	pthread_create(&output_t, NULL, write_output, NULL);

	pthread_join(input_t, NULL);
	pthread_join(replaceSep_t, NULL);
	pthread_join(replaceCaret_t, NULL);
	pthread_join(output_t, NULL);

	return EXIT_SUCCESS;
}
