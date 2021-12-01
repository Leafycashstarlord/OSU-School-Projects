#include <iostream>
#include <fstream>
#include <string>
#include "lab2.h"

using namespace std;


student* create_student_db(int num_students){
	student* student_db = new student[num_students];
	return student_db;
}

void get_student_db_info(student* student_db, int num_students, fstream &input_file){
	for(int i = 0; i < num_students; i++){
		input_file >> student_db[i].id;
		input_file >> student_db[i].first;
		input_file >> student_db[i].last;
		input_file >> student_db[i].major;
	}
	input_file.close();
}

void delete_student_db_info(student* student_db){
	delete [] student_db;
}

int get_number(fstream &input_file){
	int num_students;
	input_file.open("inputs.txt", ios::in);
	input_file >> num_students;
	return num_students;
}

student* id_sort(student* student_db, int num_students){
	student* student_id = new student[num_students];
	int num = 0;
	for(int i = 0; i < num_students; i++){
		for(int j = 0; j < num_students; j++){
			if(student_db[i].id > student_db[j].id){
				num++;
			}
		}
		student_id[num_students - num - 1] = student_db[i];
		num = 0;
	}
	return student_id;
}

student* last_name_sort(student* student_db, int num_students){
	student* student_last_name = new student[num_students];
	int num = 0;
	for(int i = 0; i < num_students; i++){
		for(int j = 0; j < num_students; j++){
			if(student_db[i].last[0] < student_db[j].last[0]){
				num++;
			}
		}
		student_last_name[num_students - num - 1] = student_db[i];
		num = 0;
	}
	return student_last_name;
}

void file_print(student* student_id, student* student_last_name, int num_students, fstream &input_file){
	if(input_file.is_open()){
		cout << "I'm Open" << endl;
	}
	string new_file;
	cout << "What is the New File name?: " << endl;
	cin >> new_file;
	input_file.open(new_file.c_str(), ios::out);

	input_file << "Sort By ID: " << endl;
	for(int i = 0; i < num_students; i++){
		input_file << student_id[i].id << " " << student_id[i].first << " " << student_id[i].last << " " << student_id[i].major << endl;
	}

	input_file << "Sort By Last Name: " << endl;
	for(int i = 0; i < num_students; i++){
		input_file << student_last_name[i].last << ", " << student_last_name[i].first << " " << student_last_name[i].major << " " << student_last_name[i].id << endl;
	}

	input_file.close();
}
