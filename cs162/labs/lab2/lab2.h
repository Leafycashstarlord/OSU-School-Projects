#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct student{
	int id;
	string first;
	string last;
	string major;
};

student* create_student_db(int);

int get_number(fstream &);

void get_student_db_info(student *, int, fstream &);

void delete_student_db_info(student *);

student* id_sort(student *, int);

student* last_name_sort(student *, int);

void file_print(student*, student*, int, fstream &);
