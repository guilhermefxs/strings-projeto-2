#!/bin/bash

PATTERN="TCTCAAAAAAAAGAAAAA"
algoritmos=('wu_manber' 'sellers')
PATTERNL=${#PATTERN}
for count in $(seq 1 ${PATTERNL});
do
	echo "count"
	echo ${count}
	time grep -c ${PATTERN} dna
done



