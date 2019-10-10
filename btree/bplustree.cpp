#include "bplustree.h"
#include "database.h"
bpt::bpt() {
	init();
}

int bpt::insert(char key[10], int offset) {

	int parent = search_index(key);
	int offset = search_leaf(parent, key);
	node_t leaf;
	
	if (binary_search(leaf.children, leaf.children + leaf.n, index_t(key, 0))) {
		return 1;
	}
	if (leaf.n == meta.order) { // split
		node_t new_leaf;
		node_create(offset, leaf, new_leaf);

		int point = leaf.n / 2;
		bool place_right = strcmp(key, leaf.children[point].key) > 0;
		if (place_right)
			point++;

		copy(leaf.children + point, leaf.children + leaf.n, new_leaf.children);
		new_leaf.n = leaf.n - point;
		leaf.n = point;

	}
	return 0;
}

int bpt::search_index(char key[10]) {
	int offset = meta.root_offset;
	int height = meta.height;
	while (height > 1) {
		node_t node;
		node = load(offset, node);
		index_t b(key, 0);
		int i = lower_bound(node.children, node.children + node.n, b) - node.children; // 
		offset = node.children[0].offset;
		--height;
	}
	return offset;
}

int bpt::search_leaf(int offset, char key[10]) {
	node_t node;
	node = load(offset, node);
	index_t b(key, 0);
	int i = lower_bound(node.children, node.children + node.n, b) - node.children; // 
	offset = node.children[i].offset;
	return offset;
}

void bpt::node_create(int offset, node_t node, node_t next) {
	meta.slot = meta.slot + sizeof(node);
	next.parent = node.parent;
	next.next = node.next;
	next.prev = offset;
	node.next = meta.slot;



	if (next.next != 0) {
		node_t old_next;

		
	}
}
void bpt::init() {
	// meta.order = M_ORDER;
	meta.internal_node_num = 1;
	meta.leaf_node_num = 1;
	meta.height = 1;
	meta.slot = 0; // where to store new block
	meta.root_offset = sizeof(meta_t);
	meta.leaf_offset = sizeof(meta_t);

	save(meta.slot, meta);
	meta.slot = meta.slot + sizeof(meta_t);

	// init root node;
	node_t root;
	memset(&root, 0, sizeof(root));
	save(meta.slot, root);
	meta.slot = meta.slot + NODE_SIZE;

	// init leaf node;
	node_t leaf_node;
	memset(&leaf_node, 0, sizeof(leaf_node));
	save(meta.slot, leaf_node);
	meta.slot = meta.slot + NODE_SIZE;
	meta.leaf_offset = root.children[0].offset = meta.slot;

}

