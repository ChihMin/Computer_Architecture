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
	#mkdir ${VARS[$index]}
	cp ../${VARS[$index]}/*.bin ${VARS[$index]}/
	cd ${VARS[$index]}/
	/home/archi/pipeline
	cd ..
done
