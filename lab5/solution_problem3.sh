#!/bin/bash


for file in `find $1`; do
	if [ -e $file ] && [ -f $file ] && [ -r $file ]; then
		if [ $(cat $file | wc -l) > 10 ]; then
			head -n 5 $file
			tail -n 5 $file
		else
			cat $file
		fi
	fi
done
