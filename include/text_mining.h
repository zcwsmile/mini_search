/*************************************************************************
	> File Name: text_mining.h
	> Author: MarkWoo
	> Mail:wcgwuxinwei@gmail.com 
	> Created Time: Wed 07 May 2014 10:29:35 PM CST
 ************************************************************************/

#ifndef _TEXT_MINING_H_
#define _TEXT_MINING_H_

/* c puls puls lib */
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>

/* linux system call */
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>

#define MAXLEN 1024*1024*32
#define MAXSIZE 1024*1024
#define DEBUG std::cout << "_____DEBUG____" << std::endl; std::cout << "file_name: " << __FILE__ << std::endl; std::cout << "line: " << __LINE__ << std::endl;

#endif //text_mining.h
