//Name: Jackson E. Rollins
//Date: 1/17/2021
//ID: 932932878


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Movie Struct that stores all the info for a given movie
struct movie{
	char *title;
	char *year;
	char *lang;
	char *rating;
	struct movie* next;
};

//Parse the current line and create of movie struct with the data in a line
struct movie* createMovie(char *currLine){
	struct movie *currMovie = malloc(sizeof(struct movie));

	char *saveptr;

	//Title
	char *token = strtok_r(currLine, ",", &saveptr);
	currMovie->title = calloc(strlen(token) + 1, sizeof(char));
	strcpy(currMovie->title, token);

	//Year
	token = strtok_r(NULL, ",", &saveptr);
	currMovie->year = calloc(strlen(token) + 1, sizeof(char));
	strcpy(currMovie->year, token);

	//Language
	token = strtok_r(NULL, ",", &saveptr);
	currMovie->lang = calloc(strlen(token) + 1, sizeof(char));
	strcpy(currMovie->lang, token);

	//Rating
	token = strtok_r(NULL, ",", &saveptr);
	currMovie->rating = calloc(strlen(token) + 1, sizeof(char));
	strcpy(currMovie->rating, token);

	currMovie->next = NULL;

	return currMovie;
}

//Create a linked list of the movies
struct movie* processFile(char *filePath){
	FILE* movieFile = fopen(filePath, "r");

	char* currLine = NULL;
	size_t len = 0;
	ssize_t nread;

	struct movie* head = NULL;
	struct movie* tail = NULL;

	while((nread = getline(&currLine, &len, movieFile)) != -1){
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

//Function used to find each movie that came out in a given year, and prints them
void printMovieYear(struct movie* list){
	int year = 0;
	int found = 0;
	printf("Enter the year for which you want to see movies: ");
	scanf("%d", &year);
	printf("\n");

	while(list != NULL){
		if(atoi(list->year) == year){
			printf("%s\n", list->title);
			found = 1;
		}
		list = list->next;
	}

	if(found == 0){
		printf("No data about movies released in the year %d\n", year);
	}
}

//Function used to find the highest rated movie from each year, and print them
void printMovieRating(struct movie* list){
	int year;
	for(year = 1900; year <= 2021; year++){
		struct movie* highRate;
		struct movie* temp;
		struct movie* mainList = list;
		char* string;

		while(mainList != NULL){
			if(atoi(mainList->year) == year){
				temp = mainList;

				while(temp != NULL){
					if(temp->year == mainList->year){
						if(temp->rating >= mainList->rating){
							highRate = temp;
						}else{
							highRate = mainList;
						}
					}
					temp = temp->next;
				}
				printf("%s %.1f %s \n", highRate->year, strtod(highRate->rating, &string), highRate->title);
				break;
			}else{
				mainList = mainList->next;
			}
		}
	}
}

//Function used to find all movies that are offered in a given language, and print them
void printMovieLang(struct movie* list){
	char lang[20];
	int found = 0;
	printf("Enter the language for which you want to see movies: ");
	scanf("%s", lang);
	printf("\n");

	while(list != NULL){
		if(strstr(list->lang, lang)){
			printf("%s %s \n", list->year, list->title);
			found = 1;
		}
		list = list->next;
	}

	if(found == 0){
		printf("No data about movies released in %s\n", lang);
	}
}

//Function used to print out the prompt given to the user
void prompt(){
	printf("1. Show movies released in the specified year\n");
	printf("2. Show highest rated movie for each year\n");
	printf("3. Show the title and year of release of all movies in a specific language\n");
	printf("4. Exit from the program\n");
	printf("\n");
	printf("Enter an option from 1 to 4 inclusive: ");
}

//Function used to print out the data of a movie
void printMovie(struct movie* aMovie){
	printf("%s, %s, %s, %s\n", aMovie->title, aMovie->year, aMovie->lang, aMovie->rating);
}

//Function used print the entire given list of movies
void printMovieList(struct movie* list){
	while(list != NULL){
		printMovie(list);
		list = list->next;
	}
}

//Function to find and return the number of movies within the given list
int listLen(struct movie* list){
	int len = 0;
	
	while(list != NULL){
		len++;
		list = list->next;
	}

	return (len - 1);
}

//Main Function. Reads the givne file and puts it into a list. Then asks the user what they want to do with the list.
int main(int argc, char *argv[]){
	if (argc < 2){
		printf("You must provide the name of the fil to process\n");
		printf("Example usage: ./movies movie_sample_1.csv\n");
		return EXIT_FAILURE;
	}

	struct movie* list = processFile(argv[1]);
	printf("Processed file %s", argv[1]);
	printf(" and parsed data for %d movies\n", listLen(list));
	printf("\n");

	int option = -1;
	
	while(option != 4){
		prompt();
		scanf("%d", &option);
	
		if(option == 1){
			printMovieYear(list);
			printf("\n");
		}else if(option == 2){
			printMovieRating(list);
			printf("\n");
		}else if(option ==3){
			printMovieLang(list);
			printf("\n");
		}else if(option ==4){
			break;
		}else{
			printf("You enter an incorrect option. Try again.\n");
			printf("\n");
		}
	}

	return EXIT_SUCCESS;
}
