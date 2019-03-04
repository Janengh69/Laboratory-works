#include "argz.h"

int main()
{
	char *argz;
	size_t argz_lenth;
	int counter;
	const char * string = "SHELL=/bin/bash:usr=monty:PWD=/bin/monty:LANG=en_US.UTF-8";
	char *entry = NULL;

	printf(" Testing function \"argz_create_sep\": \n");
	argz_create_sep(string, 58, &argz, &argz_lenth);
	printf(" argz_len = %d\n", argz_lenth + 1);
	printf(" Vector: ");
	argz_print(argz, argz_lenth);
	printf("\n");

	printf("\n Testing function \"argz_count\": \n");
	printf(" The amount of arguments = %d", argz_count(argz, argz_lenth));

	printf("\n\n Testing function \"argz_add\": \n");
	printf(" Add : C = USR/VS/:repos \n");
	argz_add(&argz, &argz_lenth, "C = USR/VS/:repos");
	argz_print(argz, argz_lenth);

	printf("\n\n Testing function \"argz_delete\": \n");
	argz_print(argz, argz_lenth);
	printf("\n");
	printf(" Delete PWD=/bin/monty: \n");
	argz_delete(&argz, &argz_lenth, "PWD=/bin/monty");
	argz_print(argz, argz_lenth);

	printf("\n\n Testing function \"argz_insert:\"\n");
	printf(" Old vector: \n");
	argz_print(argz, argz_lenth);
	argz_insert(&argz, &argz_lenth, "usr=monty", "new");
	printf("\n New vector: \n");
	argz_print(argz, argz_lenth);

	printf("\n\n Testing function \"argz_replace\": \n");
	printf(" Replace string en_US to ru_RUS: \n");
	argz_replace(&argz, &argz_lenth, "en_US", "ru_RUS");
	argz_print(argz, argz_lenth);

	printf("\n\n Testing function argz_print\": \n");
	argz_print(argz, argz_lenth);

	printf("\n\n Testing function \"argz_next\": \n");
	counter = 0;
	while ((entry = argz_next(argz, argz_lenth, entry))&& (counter < argz_count(argz, argz_lenth))) {
		printf("\t\t");
		printf(entry, argz_lenth);
		counter++;
		printf("\n");
	}
	system("pause");
	return 0;

}