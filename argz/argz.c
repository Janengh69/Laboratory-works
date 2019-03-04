/************************************************************************
*file: argz.c
*synopsis: The argz functions use malloc/realloc to allocate/grow argz vectors, and so any argz
* vector creating using these functions may be freed by using free; conversely, any argz
* function that may grow a string expects that string to have been allocated using malloc
* (those argz functions that only examine their arguments or modify them in place will work
* on any sort of memory). All argz functions that do memory allocation have a return type
* of error_t, and return 0 for success, and ENOMEM if an allocation error occurs.
* These functions are declared in the include file "argz.h".
*related files: none
*author: Karyna Dorosh
*written: 17.09.2018
*last modified: 02.10.2018
************************************************************************/
#include "argz.h"
/*
The argz_create_sep function converts the null-terminated string string into an
argz vector (returned in argz and argz len) by splitting it into elements at every
occurrence of the character sep.
*/

error_t argz_create_sep(const char *string, int sep, char **argz, size_t *argz_len) {
	*argz_len = strlen(string);
	*argz = (char*)malloc(strlen(string) * sizeof(char));
	if (**argz != NULL) {
		for (int i = 0; i < *argz_len; i++) {
			for (i = 0; i < *argz_len; i++) {
				(*argz)[i] = string[i];
			}
			int  j = 0;
			while (j < *argz_len) {
				while (((*argz)[j] != 58) && (j < *argz_len)) {
					j++;
				}
				(*argz)[j] = '\0';
				j++;
			}
			return OK;
		}
	}
	else {
		return ERROR;
	}
}

//Returns the number of elements in the argz vector.

size_t argz_count(const char *argz, size_t arg_len) {
	size_t counter = 0;
	for (int i = 0; i <= arg_len; i++) {
		if (argz[i] == '\0')
			counter++;
	}
	return counter;
}
//The argz_add function adds the string str to the end of the argz vector 
// *argz, and updates *argz and *argz_len accordingly.

error_t argz_add(char **argz, size_t *argz_len, const char *str) {
	if (str == NULL) {
		return ERROR;
	}
	else {
		int len_str = strlen(str);
		int len_argz = *argz_len;
		*argz_len += len_str + 1;
		*argz = (char*)realloc(*argz, *argz_len*(sizeof(char)));
		(*argz)[len_argz] = '\0';
		for (int i = 0; i < len_str; i++)
			(*argz)[len_argz + i + 1] = str[i];
		size_t i = 0;
		while (i < *argz_len) { //checking whether string has to be cut in substring 
			while (((*argz)[i] != 58) && (i < *argz_len)) {
				i++;
			}
			(*argz)[i] = '\0';
			i++;
		}
		return OK;
	}
}
/*the function str_idex returns the number of index of the first letter of string 2 in string1 */

int str_index(const char *str1, const char *str2, size_t argz_len) {
	int index, j, t, i;
	index = i = j = t = 0;
	while (i <= argz_len) {
		t = i;
		while ((str1[t] == str2[j]) && (str2[j] != '\0')) {
			t++;
			j++;
		}
		if (str2[j] != '\0') {
			j = 0;
			t = 0;
			i++;
		}
		else {
			index = t - j;
			return index;
		}
	}
}

/*
If entry points to the beginning of one of the elements in the argz vector *argz, the argz_delete function will
* remove this entry and reallocate *argz, modifying *argz and *argz_len accordingly. Note that as destructive argz
* functions usually reallocate their argz argument, pointers into argz vectors such as entry will then become invalid.
*/

void argz_delete(char **argz, size_t *argz_len, const char *entry) {//yeah
	int len_entry;
	if (argz[strlen(entry)] == '\0')  len_entry = strlen(entry) + 1; //in case u wanna delete the whole line
	else len_entry = strlen(entry);
	int i = str_index(*argz, entry, *argz_len) + len_entry;
	for (i; i < *argz_len; i++) {
		(*argz)[i - len_entry] = (*argz)[i];
	}
	*argz_len = *argz_len - len_entry;
	*argz = (char*)realloc(*argz, (*argz_len) * sizeof(char));
	i = 0;
	while (i < *argz_len) {
		while (((*argz)[i] != 58) && (i < *argz_len)) {
			i++;
		}
		(*argz)[i] = '\0';
		i++;
	}
}

/*
* If entry points to the beginning of one of the elements in the argz vector *argz,
* the argz_delete function will remove this entry and reallocate *argz, modifying *argz
* and *argz_len accordingly. Note that as destructive argz functions usually reallocate
* their argz argument, pointers into argz vectors such as entry will then become invalid.
*/

error_t argz_insert(char **argz, size_t *argz_len, const char *before, const char *entry) {
	if ((entry == NULL) | (before == NULL)) return ERROR;
	else {
		*argz_len += strlen(entry);
		*argz = (char*)realloc(*argz, *argz_len * sizeof(char));
		int i = str_index(*argz, before, *argz_len);
		int j = *argz_len;
		while (j >= i + strlen(entry)) {
			(*argz)[j] = (*argz)[j - strlen(entry)];
			j--;
		}
		j = 0;
		while (j < strlen(entry)) {
			(*argz)[i] = entry[j];
			i++; j++;
		}
		i = 0;
		while (i < *argz_len) {
			while (((*argz)[i] != 58) && (i < *argz_len)) {
				i++;
			}
			(*argz)[i] = '\0';
			i++;
		}
		return OK;
	}
}
/*
The argz_next function provides a convenient way of iterating over the elements in the argz vector argz.
* It returns a pointer to the next element in argz after the element entry, or 0 if there are no elements following entry.
* If entry is 0, the first element of argz is returned.
* This behavior suggests two styles of iteration:
* char *entry = 0;
* while ((entry = argz_next (argz, argz_len, entry)))
*					action;
* (the double parentheses are necessary to make some C compilers shut up about what they consider a questionable while-test) and:
* char *entry;
* for (entry = argz; entry; entry = argz_next (argz, argz_len, entry))
*				action;
* Note that the latter depends on argz having a value of 0 if it is empty (rather than a pointer to an empty block of memory);
* this invariant is maintained for argz vectors created by the functions here.
*/

char * argz_next(char *argz, size_t argz_len, const char *entry) {
		if (NULL != entry)
		{
			size_t index;
			char *p = argz;		
			index = str_index(argz, entry, argz_len);
			p += index + strlen(entry) + 1;
			if (p < argz + argz_len)
				return p;
			else 
				return NULL;
		}
		else return argz;
	}

/*
Replace the string str in argz with string with, reallocating argz as
necessary.
*/

error_t argz_replace(char **argz, size_t *argz_len, const char *str, const char *with) {
	if ((with == NULL) | (str == NULL)) return ERROR;
	else {
		argz_insert(argz, argz_len, str, with);
		argz_delete(argz, argz_len, str);
		return OK;
	}
}

/*prints argz vector */

void argz_print(const char *argz, size_t argz_len) {//yeah 
	size_t i = 0;
	printf(" ");
	while (i <= argz_len) {
		if (argz[i] != '\0')
			printf("%c", argz[i]);
		else printf(" \"\\0\" ");
		i++;
	}
}