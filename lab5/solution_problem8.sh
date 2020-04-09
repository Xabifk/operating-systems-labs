#!/bin/bash


for file in `find $1`; do
	if [ -e $file ] && [ -f $file ] && [ -r $file ]; then
		if [  $(echo $file | wc -c) -le 8 ]; then
			echo $file
			if file $file | grep -q "ASCII"; then
				head -n 10 $file
			fi
		fi
	fi
done
