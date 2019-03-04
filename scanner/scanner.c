/**********************************************************************************
* file: scanner.c
* synopsis: Functions in that file use fopen/fclose in different modes to work with files, also use fread/fwrite
* to write of read records from binary file and fprinf to write in .txt file. All the functions 
* are declare in the include file "scanner.h"
* related files: none
* author: Karyna Dorosh
* written : 20.10.2018
* last modified: 29.10.2018
**********************************************************************************/
#include "scanner.h"

/* 
 Function creat_db records data about scanners from text file .csv in binary file db
 csv-file means that data in that file is separeted from each other by commas. In the first
 sizeof(int) bytes tha number of records is located, then records are located without any 
 omissions.
*/
int create_db(const char* csv, const char *db) {
	char str[512];
	char *str_tmp;
	char **str_array;
	str_array = (char*)malloc(512 * sizeof(char));
	for (int i = 0; i < 6; i++) {
		str_array[i] = (char**)malloc(512 * sizeof(char*));
	}
	int i;
	int counter = 0;
	int flag = 0;
	SCAN_INFO temp_records;
	SCAN_INFO temp_array[10];

	FILE *csv_f = fopen(csv, "r+");
	FILE *db_f = fopen(db, "wb+");
	int* arr_id = (int*)malloc(6 * sizeof(int));
	if (NULL == csv_f|| NULL == db_f)
	{
		printf("Unable to open the file\n");
		return 1;
	}
	else 
	{
		rewind(csv_f);
		rewind(db_f);
		fseek(db_f, sizeof(int), SEEK_SET);	
		while (fgets(str, sizeof(str), csv_f)) 
		{
			strcpy(str_array[counter], str);
			for (int k = 0; k < counter; k++) {
				if (strcmp(str_array[k], str) == 0) {
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				flag = 0;
				continue;
			}
			i = 0;
			str_tmp = strtok(str, ";");
			temp_records.manufacturer = (char*)malloc(64 * sizeof(char));
			temp_records.model = (char*)malloc(64 * sizeof(char));
			
			temp_records.id = counter;

			while (NULL != str_tmp && i <= 6) 
			{
				switch (i) {
					case 0: strcpy(temp_records.manufacturer, str_tmp); break;
					case 2: temp_records.year = atoi(str_tmp); break;
					case 1: strcpy(temp_records.model, str_tmp); break;
					case 3: temp_records.price = atof(str_tmp); break;
					case 4:	temp_records.x_size = atoi(str_tmp); break;
					case 5: temp_records.y_size = atoi(str_tmp); break;
				}
				str_tmp = strtok(NULL, ";");
				i++;
			}
				counter++;
				fwrite(&temp_records, sizeof(SCAN_INFO), 1, db_f);
		}
		rewind(db_f);
		fwrite(&counter, sizeof(int), 1, db_f);

		fclose(csv_f);
		fclose(db_f);
		return 0;
	}
}

	
/*
 Function make_index creates index file for db-file. Index file has numbers of records
 from db-file, sorted in non--decreasing by field_name. The name of idnex file is "field_name + .idx"
*/
int make_index(const char *db, const char *field_name) {
	FILE *db_file = fopen(db, "rb+");
	int counter;

	rewind(db_file);
	
	if (db_file == NULL) 
	{
		printf("Can't open binary file");
		return 1;
	}
	else {
		fread(&counter, sizeof(int), 1, db_file);

		SCAN_INFO *temp;
		temp = (SCAN_INFO*)malloc(counter * sizeof(SCAN_INFO));
		int *temp_int = (int*)malloc(counter * sizeof(int));
		float *temp_float = (float*)malloc(counter * sizeof(float));
		int *arr_index = (int*)malloc(counter * sizeof(int));
		char **temp_char = (char**)malloc(counter * sizeof(char*));

		for (int i = 0; i < counter; i++) 
			arr_index[i] = i;

		fread(temp, sizeof(SCAN_INFO), counter, db_file);
		for (int i = 0; i < counter; i++) 
		{
			if (field_name == "id") 
			{
				temp_int[i] = temp[i].id;
			}
			else if (field_name == "manufacturer") 
			{
				temp_char[i] = (char*)malloc(counter * sizeof(char));
				strcpy(temp_char[i], temp[i].manufacturer);
			}
			else if (field_name == "year") 
			{
				temp_int[i] = temp[i].year;
			}
			else if (field_name == "model") 
			{
				temp_char[i] = (char*)malloc(counter * sizeof(char));
				strcpy(temp_char[i], temp[i].model);
			}
			else if(field_name == "price")
			{
				temp_float[i] = temp[i].price;

			}
			else if (field_name == "x_size") 
			{
				temp_int[i] = temp[i].x_size;
			}
			else if (field_name == "y_size") 
			{
				temp_int[i] = temp[i].y_size;
			}
		}
		if ((field_name == "id") || (field_name == "year") || (field_name == "x_size") || (field_name == "y_size")) {
			sortingi(temp_int, arr_index, counter);
		}
		else if (field_name == "price") 
		{
			sortingf(temp_float, arr_index, counter);
		}
		else if ((field_name == "manufacturer") || (field_name == "model"))
		{
			sortingc(temp_char, arr_index, counter);
			
		}
		char *name = (char*)malloc(128 * sizeof(char));

		strcpy(name, field_name);
		strcat(name, ".idx");

		FILE * f = fopen(field_name, "wb+");
		fwrite(arr_index, counter * sizeof(int), 1, f);

		fclose(f);
		fclose(db_file);
		return 1;
	}
}
// Fuction sorts integers
void sortingi(int *arr, int *arr_index, int n) {
	int i, j, temp, temp_idx;
	for (i = 0; i < n; i++)
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1]) 
			{
				temp = arr[j];
				temp_idx = arr_index[j];
				arr[j + 1] = temp;
				arr_index[j] = arr_index[j + 1];
				arr_index[j + 1] = temp_idx;
				arr[j] = arr[j + 1];
			}
}
// Function sorts floats
void sortingf(float *arr, int *arr_index, int n) {
	int i, j, temp_idx;
	float temp;
	for (i = 0; i < n; i++)
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1]) 
			{
				temp = arr[j];
				temp_idx = arr_index[j];
				arr[j + 1] = temp;
				arr_index[j] = arr_index[j + 1];
				arr_index[j + 1] = temp_idx;
				arr[j] = arr[j + 1];
			}
}
// Function sorts strings
void sortingc(char **arr, int *arr_index, int n) {
	int i, j, temp_idx;
	char tmp[1][100];
	for (i = 0; i < n; i++)
		for (j = 0; j < n - 1; j++)
		{
			if (strcmp(arr[j], arr[j + 1]) > 0)
			{
				strcpy(tmp[0], arr[j + 1]);
				strcpy(arr[j + 1], arr[j]);
				strcpy(arr[j], tmp[0]);
				temp_idx = arr_index[j];
				arr_index[j] = arr_index[j + 1];
				arr_index[j + 1] = temp_idx;
			}
		}
}
/*
 Function print_db reads data about scanners from db-file and writes them in txt-file
 We use mode "a+" to add information in the end of the file.
*/

void print_db(const char *db) {
	FILE * db_file = fopen(db, "rb+");
	if (NULL == db_file) {
		printf("Unable to open %s\n", db);
		return;
	}
	FILE * out = fopen("Output.txt", "a+");
	int number_of_elem;
	fread(&number_of_elem, sizeof(int), 1, db_file);
	fprintf(out,"Number of elements %d\n", number_of_elem);
	SCAN_INFO record; 
	while (fread(&record, sizeof(SCAN_INFO), 1, db_file)) {
		fprintf(out, "Index: %d, manufacturer: %s, year: %d, model: %s, price: %.3f, x_size: %d, y_size: %d\n", record.id, 
			record.manufacturer, record.year, record.model, record.price, record.x_size, record.y_size);
	}
	fputc('\n', out);
	fclose(out);
	fclose(db_file);
}
/*
 Function *get_recs_by_index returns the pointer RECORD_SET* on the set of records, got 
 from index-file indx_file.idx
 */
RECORD_SET *get_recs_by_index(char *dba, char *indx_field) {
	int j = 0;
	FILE *db_file, *idx_file;
	RECORD_SET *rec1, *rec2;
	rec1 = (RECORD_SET*)malloc(sizeof(RECORD_SET));
	rec2 = (RECORD_SET*)malloc(sizeof(RECORD_SET));
	int counter;
	if (((db_file = fopen(dba, "rb+")) == NULL) || ((idx_file = fopen(indx_field, "rb+")) == NULL))
		return NULL;

	fread(&counter, sizeof(counter), 1, db_file);

	rec1->rec_nmb = counter;
	rec2->rec_nmb = counter;
	rec1->recs = (SCAN_INFO*)malloc(rec1->rec_nmb*(sizeof(SCAN_INFO)));
	rec2->recs = (SCAN_INFO*)malloc(rec2->rec_nmb*(sizeof(SCAN_INFO)));

	for (int i = 0; i < counter; i++)
		fread(&rec1->recs[i], sizeof(SCAN_INFO), 1, db_file);
	for (int i = 0; i < counter; i++) 
	{
		fread(&j, sizeof(int), 1, idx_file);
		rec2->recs[i] = rec1->recs[j];
	}
	fclose(db_file);
	fclose(idx_file);
	return rec2;
}

// Function reindex creates index files for all structure fields.

void reindex(char *file_name_dba) 
{
	make_index(file_name_dba, "id");

	make_index(file_name_dba, "manufacturer");

	make_index(file_name_dba, "year");

	make_index(file_name_dba, "model");

	make_index(file_name_dba, "price");

	make_index(file_name_dba, "x_size");

	make_index(file_name_dba, "y_size");
}
// Function del_scanner deletes record with specified id from db_file.
// After deleting function calls the function reindex.

void del_scanner(const char *db, int id) {
	FILE *db_file = fopen(db, "rb");
	FILE *tmp_file = fopen("tmp_file.db", "wb");
	if (NULL == db_file) 
	{
		printf("Unable to open %s\n", db);
		return;
	}
	else 
	{
		int j = 0;
		SCAN_INFO temp_records;
		int counter;
		fread(&counter, sizeof(int), 1, db_file);
		while (fread(&temp_records, sizeof(SCAN_INFO), 1, db_file)) {
			if (temp_records.id == id) {
				counter--;
				break;
			}
		}
		fwrite(&counter, sizeof(int), 1, tmp_file);

		fseek(db_file, sizeof(int), SEEK_SET);
		while (fread(&temp_records, sizeof(SCAN_INFO), 1, db_file)) {
			if (temp_records.id == id) continue;
			else fwrite(&temp_records, sizeof(SCAN_INFO), 1, tmp_file);
		}
		fclose(db_file);
		fclose(tmp_file);
		remove(db);
		rename("tmp_file.db", db);

		reindex(db);
	}
}
/*
 Function add_scanner adds record from csv string scanner_str to db-file. Moreover each "id" field is
 unique. After that function calls function reindex. This function uses strtok(char * str1, const char *delim) that
 divides str1 in pieces by separator delim
*/
void add_scanner(const char *db, const char* scanner_str) {
	srand(time(0));
	FILE *db_file = fopen(db, "a+");
	FILE *db_temp = fopen("temp.db", "wb");

	if (db_file == NULL) printf("\n Unable to open file");
	rewind(db_file);
	if (scanner_str == NULL) return;

	int counter;
	fread(&counter, sizeof(int), 1, db_file);// reading counter
	counter++;
	fwrite(&counter, sizeof(int), 1, db_temp);

	char *str = (char*) malloc(138 * sizeof(char));
	int i = 1;
	SCAN_INFO temp_records;		//dividing into structure 

	while (fread(&temp_records, sizeof(SCAN_INFO), 1, db_file)) {
		fwrite(&temp_records, sizeof(SCAN_INFO), 1, db_temp);
	}
	temp_records.manufacturer = (char*)malloc(64 * sizeof(char));
	temp_records.model = (char*)malloc(64 * sizeof(char));

	strcpy(str, scanner_str);
	char *str_tmp = strtok(str, ";");

	while (i <= counter && str_tmp != NULL) {
		switch (i) {
		case 1: strcpy(temp_records.manufacturer, str_tmp); break;
		case 3: temp_records.year = atoi(str_tmp); break;
		case 2: strcpy(temp_records.model, str_tmp); break;
		case 4: temp_records.price = atof(str_tmp); break;
		case 5:	temp_records.x_size = atoi(str_tmp); break;
		case 6: temp_records.y_size = atoi(str_tmp); break;
		}
		i++;
		str_tmp = strtok(NULL, ";");
	}
	int *arr = (int*)malloc(counter*(sizeof(int)));
	int flag = 0;
	SCAN_INFO check_record;
	fseek(db_file, sizeof(int), SEEK_SET);
	while (fread(&check_record, sizeof(SCAN_INFO), 1, db_file)) {
		if ((strcmp(temp_records.manufacturer, check_record.manufacturer) == 0)& (strcmp(temp_records.model, check_record.model) == 0)
				&(temp_records.price == check_record.price)
					&(temp_records.year == check_record.year)
						&(temp_records.x_size == check_record.x_size)
							&(temp_records.y_size == check_record.y_size)) { 
									printf(" Dubliates were found! Adding scanner was canceled. \n");
									flag = 1;
		}				
	}
	temp_records.id = counter;
	fwrite(&temp_records, sizeof(SCAN_INFO), 1, db_temp);
	
	fclose(db_file);
	fclose(db_temp);

	if (flag != 1) {
		remove(db);
		rename("temp.db", db);
	}
	reindex(db);
}

// Funcion select returs the pointer on the RECORD_SET* - set of records, that have the same
// meaning as the field "value"

RECORD_SET* select(const char *db, const char *field, const char *value) {

	RECORD_SET *rec1 = (RECORD_SET*)malloc(sizeof(RECORD_SET));
	RECORD_SET *rec2 = (RECORD_SET*)malloc(sizeof(RECORD_SET));
	rec2->rec_nmb = 0;
	rec1 = get_recs_by_index(db, (char*)field);

	char **str_arr = (char**)malloc(rec1->rec_nmb * sizeof(char*));
	float *float_arr = (float*)malloc(rec1->rec_nmb * sizeof(float));
	int *int_arr = (int*)malloc(rec1->rec_nmb * sizeof(int));

	int counter = 0;

	for (int i = 0; i < rec1->rec_nmb; i++) {
		if (strcmp(field, "id") == 0) {
			int_arr[i] = rec1->recs[i].id;
			if (value == int_arr[i])	
				rec2->rec_nmb += 1;
		}
		else if (strcmp(field, "manufacturer") == 0) {
			str_arr[i] = (char*)malloc(128 * sizeof(char));
			strcpy(str_arr[i], rec1->recs[i].manufacturer);
			if (strcmp(value, str_arr[i]) == 0)
				rec2->rec_nmb += 1;
		}
		else if (strcmp(field, "year") == 0) {
			int_arr[i] = rec1->recs[i].year;
			if (value == int_arr[i])
				rec2->rec_nmb += 1;
		}
		else if (0 == strcmp(field, "model")) {
			str_arr[i] = (char*)malloc(128 * sizeof(char));
			strcpy(str_arr[i], rec1->recs[i].model);
			if (0 == strcmp(value, str_arr[i]))
				rec2->rec_nmb += 1;
		}
		else if (0 == strcmp(field, "price")) {
			float_arr[i] = rec1->recs[i].price;
			if ((float)atof(value) == float_arr[i])	
				rec2->rec_nmb += 1;
		}
		else if (0 == strcmp(field, "x_size")) {
			float_arr[i] = (float)rec1->recs[i].x_size;
			if ((float)atof(value) == float_arr[i])	
				rec2->rec_nmb += 1;
		}
		else if (strcmp(field, "y_size") == 0) {
			int_arr[i] = rec1->recs[i].y_size;
			if (atoi(value) == int_arr[i])	
				rec2->rec_nmb += 1;
		}
		else return 1;
	}

	rec2->recs = (SCAN_INFO*)malloc(rec2->rec_nmb*(sizeof(SCAN_INFO)));

	if (strcmp(field, "id") == 0 || strcmp(field, "year") == 0 || strcmp(field, "x_size") == 0 || strcmp(field, "y_size") == 0)
	{
		for (int i = 0; i < rec1->rec_nmb; i++) {
			if (atoi(value) == int_arr[i]) {
				rec2->recs[counter] = rec1->recs[i];
				counter++;
			}
		}
	}
	else if (strcmp(field, "price") == 0) 
	{
		for (int i = 0; i < rec1->rec_nmb; i++) {
			if (atof(value) == float_arr[i]) {
				rec2->recs[counter] = rec1->recs[i];
				counter++;
			}
		}
	}
	else if (strcmp(field, "manufacturer") == 0 || (strcmp(field, "model") == 0)) {
		for (int i = 0; i < rec1->rec_nmb; i++) {
			if (strcmp(value, str_arr[i]) == 0) {
				rec2->recs[counter] = rec1->recs[i];
				counter++;
			}
		}
	}
	return rec2;
}
// Fuction print_rec_set printd record set 

void print_rec_set(RECORD_SET *rs) {
	printf("Number of record: %d \n", rs->rec_nmb);
	for (int i = 0; i < rs->rec_nmb; i++)
	{
		printf("Index: %d, manufacturer: %s, year: %d, model: %s, price: %.3f, x_size: %d, y_size: %d\n", rs->recs[i].id,
			rs->recs[i].manufacturer, rs->recs[i].year, rs->recs[i].model, rs->recs[i].price, rs->recs[i].x_size, rs->recs[i].y_size);
	}
}
