#!/bin/bash

sum=0
count=0

for file in `find $1`; do
	if [ -e $file ] && [ -r $file ] && [ -f $file ]; then

		sum=`expr $(cat $file | wc -l) + $sum`

		count=`expr $count + 1`
	fi
done

echo $(expr $sum / $count)
