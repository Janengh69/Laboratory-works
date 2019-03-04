#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

int main() {
	create_db("Scanners.csv", "Scanners.db");
	print_db("Scanners.db");
	reindex("Scanners.db");
	
	print_db("Scanners.db");
	add_scanner("Scanners.db", "Dell;DellScan2;2005;999.99;210;297");

	print_db("Scanners.db");
	del_scanner("Scanners.db", 200);
	print_db("Scanners.db");
	RECORD_SET* rs = select("Scanners.db", "manufacturer", "ASUS");
	print_rec_set(rs);
	rs = get_recs_by_index("Scanners.db", "manufacturer");
	print_rec_set(rs);

	system("pause");
	return 0;
}
