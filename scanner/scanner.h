#pragma once
#ifndef _SCANNER_H_
#define _SCANNER_H_
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int id;//unic id
	char *manufacturer;
	int year;  
	char *model;
	float price;
	int x_size;
	int y_size;
} SCAN_INFO;

typedef struct {
	int rec_nmb;//number of records
	SCAN_INFO *recs;//records
}RECORD_SET;

int create_db(const char* csv, const char *db);
void print_db(const char *db);
int make_index(const char *db, const char *field_name);
void sortingi(int *arr,int *arr_index, int n);
void sortingf(float *arr, int *arr_index, int n);
void sortingc(char **arr, int *arr_index, int n);
RECORD_SET *get_recs_by_index(char *dba, char *indx_field);
void reindex(char *file_name_dba);
void del_scanner(const char *db, int id);
void add_scanner(const char *db, const char* scanner_str);
RECORD_SET* select(const char *db, const char *field, const char *value);
void print_rec_set(RECORD_SET *rs);


#endif