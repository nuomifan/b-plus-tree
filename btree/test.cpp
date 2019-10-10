#include <stdio.h>
#include <stdlib.h>

#include "database.h"
#include "bplustree.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

#include <algorithm>
#include <list>



int main(int argc, char *argv[]) //输入参数数量，默认是1；
{
	string msg;
	////msg = display();
	msg = "A1_data.txt";
	database file(msg);
	block_t block;


	/*block = file.read_block(0);
	string s = file.search_record("kyhiddqsc", block);*/
	
	bpt btree;
	
	
	
	
	int j = 5;
	
	return 0;
}
