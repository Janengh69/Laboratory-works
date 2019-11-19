#include "Header.h"

int main() {
	int* length = (int*)malloc(sizeof(int));
	vector<tab> iterNumb1;
	vector<tab> iterNumb2;

	range* temp = rangeSelection(length);
	if ((*length) > 0) {
		tableIter(temp, length, iterNumb1);
		tableTangent(temp, length, iterNumb2);
		tableCompare(iterNumb1, iterNumb2);
	}
	system("pause");
}