#include "database.h"


database::database(string s) {
	if (exists_test("database.db")) {
		cout << "database file has been established" << endl;
	}
	else {
		cout << "initializing database file" << endl;
		init();
	}

}

void database::init() {
	read_from_txt();
	restore();
}
void database::restore() {

	cout << "sorting the data with keys" << endl;
	sort(data.begin(), data.end() - 1, comp);
	cout << "finish sorting" << endl;

	cout << "write data into database.db" << endl;
	ofstream outfile;
	string records = "";
	int i = 0, j = 0, offset = 0; // ��i�����ݣ���j������,ƫ����



	while (i < data.size()) {
		
		// if database.db does not exist, then create one; otherwise edit the block
		outfile.open("database.db", ios::ate | ios::in | ios::binary);
		if (outfile.is_open() == 0) {
			outfile.open("database.db", ios::out | ios::binary);
		}


		// refresh datablock 
		block_t datablock;
		int k = 0; // kth record in datablock

		while (records.size() < 810 * 0.8) {
			datablock.index[k].offset = offset;
			strcpy_s(datablock.index[k].key, data[i].key.c_str());
			k++;
			index.push_back(offset);
			records = records + data[i].key + " " + data[i].rest;
			offset = j * 1024 + records.size();
			i++;
			if (i >= data.size())
				break;
		}
		if (k < INDEX_NUMBER) {
			datablock.index[k].offset = offset;
		}
		else
		{
			cerr << "the header is overflowed";
		}
		// total number of index
		datablock.n = k;

		// put records into block
		strcpy(datablock.record, records.c_str());

		// write datablock j into file 
		outfile.seekp(1024 * j, ios::beg);
		outfile.write(reinterpret_cast<char*> (&datablock), sizeof(datablock));
		outfile.close();

		// begin of j+1 block
		j++;
		records = "";
	}
	cout << "finish writing" << endl;
}

void database::read_from_txt()
{
	cout << "reading" << endl;
	ifstream infile;
	infile.open(file.data()); // ���ļ�
	assert(infile.is_open()); //�ж��Ƿ���ļ�

	string s;
	int n; // �ض�string�ĵط�
	int i = 0;

	record_t read;
	int maxlen_k = 0, maxlen_r = 0;

	while (getline(infile, s))  // ��һ��
	{
		if (i == 10) //��ȡǰ1000������
			break;
		i++;
		n = s.find(" ");
		read.key = s.substr(0, n);
		read.rest = s.substr(n + 1);
		data.push_back(read);
		if (read.key.size() > maxlen_k) {
			maxlen_k = read.key.size(); // 9
		}
		if (read.rest.size() > maxlen_r) {
			maxlen_r = read.rest.size(); // 111
		}
	}
	infile.close();

	cout << "reading complete" << endl;
}
block_t database::read_block(int i) { // read ith block
	block_t block;
	ifstream infile;
	int block_size = 1024;
	infile.open("database.db", ios::binary);
	infile.seekg(i*block_size, ios::beg);
	infile.read(reinterpret_cast<char*> (&block), sizeof(block));
	infile.close();
	return block;
}
string database::search_record(char key[10], block_t block) {

	index_t b(key, 0);

	int i = lower_bound(block.index, block.index + block.n, b) - block.index; // 
	
	int off_set = block.index[i].offset; 
	int size = block.index[i+1].offset - block.index[i].offset;

	string s;
	s = block.record;
	s = s.substr(off_set, size);
	return s;
}

bool comp(const record_t &a, const record_t &b) {
	if (a.key.compare(b.key) <= 0)
		return true;
	else
		return false;
}



string display() {
	cout << "С�ɰ�����������Ҫ�ķ���" << endl;
	cout << "����0����ȡԭʼ����" << endl;
	cout << "input 1��search a record by entering a key value" << endl;
	cout << "input 2��range search by using the index" << endl;
	cout << "input 3, insert a new record" << endl;
	cout << "input 4, delete a record with a key value" << endl;
	cout << "input 5, display all the records sequentially ordered by the first field" << endl;

	string msg;
	cin >> msg;
	if (msg == "0") {
		cout << "��������Ҫ��ȡ���ļ������ļ�����ͬһĿ¼�£�" << endl;
		cin >> msg;
		if (msg == "A1_data.txt") {
			return msg;
		}
		else {
			cout << "С�ɰ�,��������Ӧ�����룺��A1_data.txt��" << endl;
			cerr << "С�ɰ�̫���������򲻽��ܷ���" << endl;
			return msg;
		}
	}
	else if (msg == "1") {
		return msg;
	}
	else if (msg == "2") {
		return msg;
	}
	else if (msg == "3") {
		return msg;
	}
	else if (msg == "4") {
		return msg;
	}
	else if (msg == "5") {
		return msg;
	}
	else
		cerr << "input is not legal";
	return "error";
}

