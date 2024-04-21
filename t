#!/bin/sh
if [ -z $1 ]
then
	echo "err"
	exit 1
fi

file="$1.c"
touch $file
