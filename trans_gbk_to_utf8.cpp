/*************************************************************************
	> File Name: trans_gbk_to_utf8.cpp
	> Author: MarkWoo
	> Mail:wcgwuxinwei@gmail.com 
	> Created Time: Thu 15 May 2014 02:35:59 PM CST
 ************************************************************************/

#include "./include/text_mining.h"
#include "./include/MixSegment.hpp"
#include "./include/EncodingConverter.h"

std::ofstream log_file("/home/markwoo/Documents/my_project/0515_trans_gbk_to_utf8/log.dat");

/* 去掉后面的/r */
size_t TrimR(std::string &line) {
	size_t len = line.size();
	for (size_t i = 0; i != line.size(); ++i) {
		if ('\r' == line[i])
			line.erase(i, 1);
	}
	return len - line.size();
}


/* 判断是否是标题 */
/*
void TranformTitle(std::string &title, std::string &line) {
		if (strncmp(line.c_str(), "【 标  题 】", 16) == 0) {
			//title.clear();
			//title = std::string(text_title);
			title.clear();
			title = line;
		}
}
*/

//read word_lib function
std::ifstream &OpenInFile(std::ifstream &read_stream, std::string &file_name) {
	//read_stream.open(file_name.c_str(), std::ifstream::in);
	read_stream.open(file_name.c_str(), std::ofstream::in);

	if (!read_stream) {
		throw std::runtime_error("unable to open in file");
	}
	return read_stream;
}

//write word function
std::ofstream &OpenOutFile(std::ofstream &write_stream, std::string &file_name) {
	write_stream.open(file_name.c_str(), std::ofstream::out | std::ofstream::app);
	//write_stream.open(file_name.c_str());

	if (!write_stream) {
		throw std::runtime_error("unable to open out file");
	}
	return write_stream;
}

//transform lib function
//void StringParse(ifstream &ifs, string &in_file_name, vector<string> vec_str) {
void StringParse(std::string &in_file_name) {
	//cut words sector
	EncodingConverter trans;
	std::vector<std::string> word_vec; //store word into vector
	std::vector<std::string>::iterator iter_word_vec;

	std::string line; //读入行
	std::string content; //一次性读入全部
	std::string out_file_name = in_file_name; //生成新的文件名,就是替换替换txt为utf8
	std::ifstream ifs; //文本输入流
	std::ofstream ofs; //文本输出流

	out_file_name.erase(out_file_name.size() - 3, out_file_name.npos);
	out_file_name += "utf8";

	OpenInFile(ifs, in_file_name);
	OpenOutFile(ofs, out_file_name);

	while (getline(ifs, line)) {
		content += line + "\n";
	}
	ofs << trans.gbk_to_utf8(content) << std::endl;
	log_file << "tranform complete " << out_file_name << std::endl;

	ofs.close();
	ifs.close();
}

void BuildPageLib(std::string &in_file_name, std::vector<std::string> &lib_vec) {
	std::string line; //读入行
	std::string content; //一次性读入全部
	std::string title; //title
	std::ofstream ofs;
	std::ifstream ifs; //文本输入流

	OpenInFile(ifs, in_file_name);
	log_file << " processing file name: " << in_file_name << std::endl;

	getline(ifs, title, '\r'); //先取第一行作为标题
	TrimR(title);
	content += title;

	while (getline(ifs, line, '\r')) {
		if (strncmp(line.c_str(), "\n【 标  题 】", 17) == 0) {
			//title.clear();
			//title = std::string(text_title);
			title.clear();
			title = line;
			std::cout << "titile: ~~~~~~" << line << std::endl;
		}

		/* 每行后面添加换行符 */
		if (TrimR(line)) {
			content += line + "\n";
		} else {
			content += line;
		}

		/* 每行后面不添加换行符, 整篇为一行 */
		//content +=line;

		//char text_title[MAXSIZE];
		//bzero(text_title, MAXSIZE);
		//strcpy(text_title, line.c_str());
		//if (strncmp(text_title, "【 标  题 】", 16) == 0) {
	}

	std::string doc;
	char id[8];
	bzero(id, 8);
	sprintf(id, "%d", (int)(lib_vec.size() + 1));
	doc = "<doc><docid>" + std::string(id) + "</docid><url>" + in_file_name + "</url><title>" + title + "</title><content>" + content + "</content></doc>\n";
	lib_vec.push_back(doc);

	ifs.close();
}

	//scan all content of the directory which is language resource
	void ScanFile(char* dir_name, std::vector<std::string> &lib_vec) {
		DIR* curr_dir;
		struct dirent* curr_dirp;
		struct stat stat_buffer;

		if (NULL == (curr_dir = opendir(dir_name))) {
			throw std::runtime_error("opendir");
		}

		chdir(dir_name);
		while (NULL != (curr_dirp = readdir(curr_dir))) {
			lstat(curr_dirp->d_name, &stat_buffer);
			if (S_ISDIR(stat_buffer.st_mode)) { //if current file is directory then recuisely jump in this directory
				if (0 == strcmp(".", curr_dirp->d_name) || 0 == strcmp("..", curr_dirp->d_name))
					continue;
				ScanFile(curr_dirp->d_name, lib_vec);
			} else { //if current file is regular file then write info into list
				std::string file_name(curr_dirp->d_name);
				BuildPageLib(file_name, lib_vec);
				//std::cout << file_name << std::endl;
				/*
					 std::string end_name = file_name.substr(file_name.size() - 4, file_name.npos);
					 log_file << "end_name: " << end_name << std::endl;
					 */
				/* 判断是否是已经转过的文件，判断后缀名是否为UTF8 */
				/*
					 if (std::string("utf8") != end_name) {
					 log_file << "file_name: " << file_name << std::endl;
					 StringParse(file_name);
					 }
					 */
			}
		}

		chdir("..");
		closedir(curr_dir);
	}

/* 通过输入DocId搜索页面，借助索引可以快速找到docid */
	void SearchIndex(std::string &index_file_name, std::string &lib_file_name) {
		std::ifstream ifs_index;
		std::vector<std::string> index;
		std::string line;

		OpenInFile(ifs_index, index_file_name);

		while (getline(ifs_index, line)) {
			index.push_back(line);
		}
		ifs_index.close();

		int num;
		while (std::cin >> num) {
			if (num > (int)index.size() || num < 1) {
				std::cout << "out of index range" << std::endl;
				continue;
			}

			int doc_id;
			int start;
			int size_;
			std::istringstream iss(index[num - 1].c_str());
			iss >> doc_id >> start >> size_;
			//std::cout << doc_id << start << size_;
			std::ifstream ifs_lib;
			OpenInFile(ifs_lib, lib_file_name);
			ifs_lib.seekg(start);
			std::string content;
			while (getline(ifs_lib, line) && ifs_lib.tellg() <= (start + size_)) {
				content += line + "\n";
			}
			//std::cout << content << std::endl;
			ifs_lib.close();
		}
	}

	int main(int argc, char **argv) {
		std::map<std::string, int> map_word;
		std::vector<std::string> lib_vec; 
		std::ofstream ofs_lib;
		std::ofstream ofs_index;
		char* source_name = strdup("./language_lib");
		std::string lib_file_name("/home/markwoo/Documents/my_project/0515_0516_mini_search/lib_page/ripepage.lib"); //build_lib file name
		std::string index_file_name("/home/markwoo/Documents/my_project/0515_0516_mini_search/index/ripepage.index"); //index file file name
		
		/* 扫描语料库 */
		ScanFile(source_name, lib_vec);
		
		/* 写入文件，同时制作索引 */
		OpenOutFile(ofs_lib, lib_file_name);
		OpenOutFile(ofs_index, index_file_name);
		size_t vec_index = 1; //存储页面的容器vector下标

		for (auto &i : lib_vec) {
			ofs_index << vec_index << " " << ofs_lib.tellp(); //取得当前文件指针的位置
			ofs_lib << i;
			ofs_index << " " << i.size() << std::endl; //Doc文件的大小
			++vec_index;
		}

		ofs_index.close();
		ofs_lib.close();
		log_file.close();
		std::cout << "language lib and index builded" << std::endl;

		SearchIndex(index_file_name, lib_file_name);

		return 0;
	}
