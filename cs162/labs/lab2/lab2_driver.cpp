#include <iostream>
#include <fstream>
#include <string>
#include "lab2.h"

using namespace std;

int main(){
	fstream input_file;

	int num_students = get_number(input_file);

	student* student_db = create_student_db(num_students);

	get_student_db_info(student_db, num_students, input_file);

	student* student_id = id_sort(student_db, num_students);

	student* student_last_name = last_name_sort(student_db, num_students);

	file_print(student_id, student_last_name, num_students, input_file);

	delete_student_db_info(student_db);

	delete_student_db_info(student_id);

	delete_student_db_info(student_last_name);

	return 0;
}
