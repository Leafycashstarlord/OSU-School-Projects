//Name: Jackson E. Rollins
//Date: 1/17/2021
//ID: 932932878

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

//Movie Struct that stores all the the info for a given movie
struct movie{
	char *title;
	int year;
	char *lang;
	float rating;
	struct movie* next;
};

//Parse the current line and create a movie struct with the data in a line
struct movie* createMovie(char *currLine){
	struct movie *currMovie = malloc(sizeof(struct movie));

	char *saveptr;

	char *token = strtok_r(currLine, ",", &saveptr);
	currMovie->title = calloc(strlen(token) + 1, sizeof(char));
	strcpy(currMovie->title, token);

	token = strtok_r(NULL, ",", &saveptr);
	currMovie->year = atoi(token);

	token = strtok_r(NULL, ",", &saveptr);
	currMovie->lang = calloc(strlen(token) + 1, sizeof(char));
	strcpy(currMovie->lang, token);

	token = strtok_r(NULL, ",", &saveptr);
	currMovie->rating = atof(token);

	currMovie->next = NULL;

	return currMovie;
}

//Creat a linked list of the movies
struct movie* processFile(char *filePath){
	FILE* movieFile = fopen(filePath, "r");

	char* currLine = NULL;
	size_t len = 0;
	ssize_t nread;
	int num = 0;

	struct movie* head = NULL;
	struct movie*tail = NULL;

	while((nread = getline(&currLine, &len, movieFile)) != -1){
		if(num == 0){
			num++;
			continue;
		}

		struct movie* newNode = createMovie(currLine);

		if(head == NULL){
			head = newNode;
			tail = newNode;
		}else{
			tail->next = newNode;
			tail = newNode;
		}
	}
	free(currLine);
	fclose(movieFile);
	return head;
}       

//Creat a direcotry using my onid and a random number. Also create the files
//in the directory that list all of the movies released in a given year
void createDirectory(struct movie* list){
	srand(time(0));
	int randNum = (rand() % 100000);
	char *dir = malloc(23*sizeof(char));
	sprintf(dir, "rollijac.movies.%d", randNum);
	mkdir(dir, 0750);
	printf("Created Directory with name %s\n", dir);

	int year = 0;

	for(int x = 1900; x<=2022; x++){
		struct movie* newList = list;

		while(newList != NULL){
			if(newList->year == x){
				if(newList->year == year){
					char yearS[20];
					const char* textExten = ".txt";
					snprintf(yearS, 20, "%d", x);

				//	DIR* currDir = opendir(dir);
					char* fileName = strcat(yearS, textExten);

					FILE *fptr;
					fptr = fopen(fileName, "a");
					fprintf(fptr, "%s\n", newList->title);
					fclose(fptr);

					newList = newList->next;
				}else{
					char yearS[20];
					const char* textExten = ".txt";
					snprintf(yearS, 20, "%d", x);
					
					//DIR* currDir = opendir(dir);
					int file;
					char* fileName = strcat(yearS, textExten);

					file = open(fileName, O_RDWR | O_CREAT | O_APPEND, 0640);
					FILE* fptr;
					fptr = fopen(fileName, "a");
					fprintf(fptr, "%s\n", newList->title);
					fclose(fptr);

					year = x;
					newList = newList->next;
				}
			}else{
				newList = newList->next;
			}
		}
	}
	printf("Done\n");
}

//Find the largest data file within the directory
void findLargest(){
	struct dirent* ptr;
	struct stat data;
	DIR* dir;
	dir = opendir(".");
	int i = 0;
	char* fileName;
	char movies[] = "movies_";
	char csv[] = ".csv";

	while((ptr = readdir(dir)) != NULL){
		if(strncmp(movies, ptr->d_name, strlen(movies)) == 0){
			char dot = '.';
			const char *string = (ptr->d_name);
			char* extension = strrchr(string, dot);

			if(extension != NULL){
				if(strcmp(extension, csv) == 0){
					stat(ptr->d_name, &data);
					if(data.st_size> i){
						i = data.st_size;
						fileName = ptr->d_name;
					}
				}
			}
		}
	}
	printf("Now processing the chosen file named %s\n", fileName);
	printf("\n");

	struct movie* list = processFile(fileName);
	createDirectory(list);
	closedir(dir);
}

//Find the smallest data file within the directory
void findSmallest(){
	struct dirent* ptr;
	struct stat data;
	DIR* dir;
	dir = opendir(".");
	int i = 100000;
	char* fileName;
	char movies[] = "movies_";
	char csv[] = ".csv";

	while((ptr = readdir(dir)) != NULL){
		if(strncmp(movies, ptr->d_name, strlen(movies)) == 0){
			char dot = '.';
			const char* string = (ptr->d_name);
			char* extension = strrchr(string, dot);

			if(extension != NULL){
				if(strcmp(extension, csv) == 0){
					stat(ptr->d_name, &data);
					if(data.st_size < i){
						i = data.st_size;
						fileName = ptr->d_name;
					}
				}
			}
		}
	}
	printf("Now processing the chosen file named %s\n", fileName);
	printf("\n");

	struct movie* list = processFile(fileName);
	createDirectory(list);
	closedir(dir);
}

//Find a file specified by the user
void findSpecific(){
	char fileName[256];
	printf("Enter the complete file name: ");
	scanf("%s", fileName);
	printf("\n");

	if(access(fileName, F_OK) == 0){
		printf("Now processing the chosen file named %s\n", fileName);
		printf("\n");
		
		struct movie* list = processFile(fileName);
		createDirectory(list);
		printf("\n");
	}else{
		printf("The file %s was not found.\n", fileName);
	}
}

//Main Function. Asks the user if they want to process a file, and how they want to process it.
int main(){
	int question = 1;
	int response1 = 0;
	int response2 = 0;

	while(1){
		printf("\n1. Select file to process\n");
		printf("2. Exit Program\n\n");
		scanf("%d", &response1);

		if(response1 == 1){
			while(question == 1){
				printf("\nWhich file do you want to process?\n");
				printf("1. Pick the largest file.\n");
				printf("2. Pick the smallest file.\n");
				printf("3, Specify the name of a file.\n");
				scanf("%d", &response2);

				if(response2 == 1){
					findLargest();
					question = 0;
				}else if(response2 == 2){
					findSmallest();
					question = 0;
				}else if(response2 == 3){
					findSpecific();
					question = 0;
				}else{
					printf("Invalid Option.\n");
				}
			}
		}else if(response1 == 2){
			exit(0);
		}else{
			printf("Invalid Option.\n");
		}
	}
}
