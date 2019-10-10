#pragma once
#include "database.h"
# define M_ORDER 8
# define NODE_SIZE 512

//info of b+ tree
struct meta_t {
	int order = M_ORDER;
	int internal_node_num = 0;
	int leaf_node_num = 0;
	int height = 0;
	int slot = 0; // where to store new block
	int root_offset = 0;
	int leaf_offset = 0;
}; //7 * 4 = 28 bytes


struct node_t {
	int parent;
	int next;
	int prev;
	int n;  // how many nodes in this node
	index_t children[M_ORDER];
}; // 4 * 4 + (10 + 4) * 8 = 128 bytes 


class bpt {
public:
	meta_t meta;

	bpt();
	void init();
	// insert function
	int insert(char key[10], int offset);
	int search_index(char key[10]);
	int search_leaf(int parent, char key[10]);
	void node_create(int offset, node_t node, node_t next);





	template <class T>
	inline void save(int off_set, T block)
	{
		ofstream outfile;
		outfile.open("btree.db", ios::ate | ios::in | ios::binary);
		if (outfile.is_open() == 0) {
			outfile.open("btree.db", ios::out | ios::binary);
		}
		outfile.seekp(off_set, ios::beg);
		outfile.write(reinterpret_cast<char*> (&block), sizeof(block));
		outfile.close();

	}
	template <class T>
	inline T load(int off_set, T block)
	{
		ifstream infile;
		infile.open("btree.db");
		infile.seekg(off_set, ios::beg);
		infile.read(reinterpret_cast<char*> (&block), sizeof(block));
		infile.close();
		return block;
	}
};