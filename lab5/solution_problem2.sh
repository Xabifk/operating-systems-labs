#!/bin/bash


for file in `find $1`; do
	if [ -e $file ] && [ -f $file ] && [ -r $file ]; then
		if grep -q '[0-9]\{5\}' $file; then
			echo $file
		fi
	fi
done
