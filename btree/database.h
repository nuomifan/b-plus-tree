#ifndef database_h
#define database_h
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

// sort 所需
#include <algorithm>

// 宏定义
#define INDEX_NUMBER 15
#define RECORD_SIZE (1024 - INDEX_NUMBER * 14 - 4)
using namespace std;



/*每一行数据*/
struct record_t {
	string key;
	string rest;
};
struct index_t {
	char key[10];
	int offset;
	index_t() {}
	index_t(char s[10], int j) {
		strcpy_s(key, s);
		offset = j;
	}
	bool operator<(const index_t m)const {
		if (strcmp(key, m.key) < 0)
			return true;
		else
			return false; 
	}
};
struct block_t {
	int n = 0; // how many records in this block 4 bytes
	index_t index[INDEX_NUMBER]; // (10 + 4) * 15 = 210 bytes
	char record[RECORD_SIZE] = { 0 }; // 1024 - 214 = 810 bytes
};

string display();

bool comp(const record_t &a, const record_t &b);

class database {
public:
	vector<record_t>data;
	string file = "A1_data.txt";
	string database_file = "database.db";
	vector<int> size_j;
	vector<int> index;
	database(string s);
	~database() {
		cout << "Object is being deleted" << endl;
	}
	void init();
	void restore();
	void read_from_txt();
	inline bool exists_test(const std::string& name) {
		ifstream f(name.c_str());
		return f.good();
	}
	string search_record(char key[10], block_t block);
	block_t read_block(int i);

};

#endif // !database.h