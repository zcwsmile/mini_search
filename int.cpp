/*************************************************************************
	> File Name: int.cpp
	> Author: MarkWoo
	> Mail:wcgwuxinwei@gmail.com 
	> Created Time: Thu 15 May 2014 03:40:32 PM CST
 ************************************************************************/

#include <iostream>
#include <fstream>

int main() {
	std::ifstream openFile;
	std::string line; //读入行
	std::string content; //一次性读入全部
	openFile.open("/home/markwoo/Documents/my_project/0515_trans_gbk_to_utf8/language_lib/C7-History/C7-History155.txt");
	while (getline(openFile, line)) {
		std::cout << line << std::endl;
	}

	return 0;
}
