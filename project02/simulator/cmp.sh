#!/bin/bash
filename=list.txt
index=0
echo $filename
while read line
do
	VARS[$index]="$line"
	index=$(($index+1))
done < $filename

for((index=0; index<${#VARS[@]}; index++)); do
	echo ${VARS[$index]}
	cp ../student/${VARS[$index]}/*.bin .
	./pipeline
	diff -q snapshot.rpt ../student/${VARS[$index]}/snapshot.rpt
	diff -q error_dump.rpt ../student/${VARS[$index]}/error_dump.rpt
done
