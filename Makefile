all: tranform.exe
tranform.exe: 
	g++ -g -o tranform.exe -O3 -DLOGGER_LEVEL=LL_WARN -Wall -g -I./include ./trans_gbk_to_utf8.cpp EncodingConverter.cpp -DCPPJIEBA_GBK -std=c++11 
.PHNOY:clean
clean:
	rm -f *.o *.a *.exe
