#!/bin/bash

directory="/home/null/desktop/iconv/gb18030"

f_encoding="gb18030"
t_encoding="utf-8"

for dir in `ls $directory`
do
    if [ -d "$directory/$dir" ]
    then
	for file in `ls $directory/$dir`
	do
	    if [ -f "$directory/$dir/$file" ]
	    then
		iconv -f $f_encoding -t $t_encoding $directory/$dir/$file -o /home/null/desktop/iconv/utf8/$file
	    fi
	done
    fi
done
