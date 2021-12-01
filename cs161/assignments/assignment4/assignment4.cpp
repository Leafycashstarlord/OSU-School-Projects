/********************
 *Name: Jackson E. Rollins
 *Program: Assignment 4
 *Date: March 1/2020
 * */
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;


void purge_string(char *str, char *new_string){
	int j = 0;
   	for(int i = 0; str[i] != '\0'; i++){
		if((str[i] >= 'a' && str[i] <= 'z') or (str[i] >= 'A' && str[i] <= 'Z')){
			new_string[j++] = str[i];
		}
	}
	new_string[j] = '\0';
}

bool vowel_consonant(char *str){
	int countVowel = 0;
	int countConsonant = 0;

	for(int i = 0; str[i] != '\0'; i++){
		if(str[i] == 'a' or str[i] == 'e' or str[i] == 'i' or str[i] == 'o' or str[i] == 'u' or str[i] == 'A' or str[i] == 'E' or str[i] == 'I' or str[i] == 'O' or str[i] == 'U'){
			countVowel = countVowel + 1;
		}else{
			countConsonant = countConsonant + 1;
		}
	}
	if(countVowel == countConsonant){
   		return true;
	}else{
		return false;
	}
}

void letterSwap(char *str, char letterOne, char letterTwo){
	for(int i = 0; str[i] != '\0'; i++){
		if(str[i] == letterOne){
			str[i] = letterTwo;
		}
		if(str[i] == (letterOne - 32)){
			str[i] = letterTwo - 32;
		}
	}
}

void reverse(char *str, char *flippedString, int length){
	int value = length - 1;
	for(int i = 0; str[i] != '\0'; i++){
		flippedString[i] = str[value];
		value = value - 1;
	}
}

bool palindrome(char *str, char *palinString){
	for(int i = 0; str[i] != '\0'; i++){
		if((str[i] >= 65) && (str[i] <= 90)){
			str[i] = str[i] + 32;
		}
		if((palinString[i] >= 65) && (palinString[i] <= 90)){
			palinString[i] = palinString[i] + 32;
		}
	}
	for(int j = 0; str[j] != '\0'; j++){
		if(str[j] != palinString[j]){
			return false;
		}
	}

	return true;
} 

void frequency(char *str, string *wordList, int words){
	int length;
	int plength = strlen(str); 
	string word;
	int counter = 0;
	bool same = true;

	for(int i = 0; i < words; i++){
	   length = wordList[i].length();
	   word = wordList[i];
	   //cout << "WORD LIST LENGTH: " << strlen(str)  << endl;
	   for(int x = 0; x < plength-length; x++){
	      for(int j = 0; j < length; j++){
		 if(word[j] != str[x+j]){
		    same = false;
		    break;
		 }	
	      }
	      if(same == true){
		 counter++;
		 same = false;
	      } 

	   }
	      cout << wordList[i] << ": " << counter << endl;
	}
}

void swapping(char *strings);
void vowCon(char *str); 
void flipping(char *str);
void palinDetector(char *str);
void wordCount(char *str);

int main(){
   char *strings = new char [1024];
   char *purgedString = new char[1024];
	int whatToDo;
   cout << "Give a sentence/paragraph no longer than 1023 characters: " << endl;
   cin.getline(strings, 1024);

   if(cin.fail()){
      cin.ignore(1024, '\n');
      cin.clear();
   }

   purge_string(strings, purgedString); 
	cout << "1 for word count, 2 fo palindrome, 3 for reverse, 4, for voewl/consonant, 5 for swapping: " << endl;
	cin >> whatToDo;
   
	if(whatToDo == 1){
		wordCount(strings);
	}else if(whatToDo == 2){ 
   		palinDetector(purgedString);
	}else if(whatToDo == 3){  
   		flipping(strings); 
	}else if(whatToDo == 4){ 
   		vowCon(purgedString); 
	}else if(whatToDo == 5){  
   		swapping(strings); 
	}

   return 0;
}

void palinDetector(char *str){
   int length = 0;
   for(int i= 0; str[i] != '\0'; i++){
      length = length + 1;
   }
   char *palinString = new char[length];

   reverse(str, palinString, length);

   if(palindrome(str, palinString) == true){
      cout << "This is a palindrome." << endl;
   }else{
      cout << "This is not a palindrome." << endl;
   }
}

void flipping(char *str){
   int length = 0;
   for(int i = 0; str[i] != '\0'; i++){
      length = length + 1;
   }
   char *flippedString = new char[length];

   reverse(str, flippedString, length);

   cout << flippedString << endl;
}

void swapping(char *strings){
   char letterOne;
   char letterTwo;
   cout << "What letter do you want to replace?: " << endl;
   cin >> letterOne;
   cout << "What letter do you want to replace it with?: " << endl;
   cin >> letterTwo;
   if((letterOne >= 65) && (letterOne <= 90)){
      letterOne = letterOne + 32;
   }
   if((letterTwo >= 65) && (letterTwo <= 90)){
      letterTwo = letterTwo +32;
   }
   letterSwap(strings, letterOne, letterTwo); 
   cout << strings << endl;
}


void vowCon(char *str){
   if((vowel_consonant(str)) == true){
      cout << "Number of vowels equals number of consonants."  << endl;
   }else{
      cout << "Number of vowels does not equal number of consonants" << endl;
   }
}


void wordCount(char *str){
   int words;
   string word;

   cout << "How many words do you want to check? (positive integer): " << endl;
   cin >> words;

   string wordList[words];

   for(int i = 0; i < words; i++){	
      cout << "Please give a word: " << endl;
      while(true){
	 cin >> word;
	 if(cin.fail()){
	    cin.clear();
	    cin.ignore(1000000, '\n'); 	
	 }else{
	    break;
	 }	
      }
      wordList[i] = word;
   }
   frequency(str, wordList, words);
}
