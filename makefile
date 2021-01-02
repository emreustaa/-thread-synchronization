all:matrixcalc
 
matrixcalc: matrixcalc.c
	gcc matrixcalc.c -o matrixcalc -l pthread