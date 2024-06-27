#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gpp.h"

int gcd(int num1, int num2) {
	while (num1 != num2) {
	        if (num1 > num2)
	            num1 -= num2;
        	else
       		    num2 -= num1;
    	}

	if(num1 == 0) return 1;
	return num1;
}

void simplify(Valuef * v) {
	int div = gcd(v->first, v->second);
	v->first = v->first / div;
	v->second = v->second / div;
}

Valuef addV(Valuef v1, Valuef v2) {
	Valuef r;
	r.first = v1.first * v2.second + v2.first * v1.second;
	r.second = v1.second * v2.second;
	simplify(&r);
	return r;	
}

Valuef subV(Valuef v1, Valuef v2) {
	Valuef r;
	r.first = v1.first * v2.second - v2.first * v1.second;
	r.second = v1.second * v2.second;
	simplify(&r);
	return r;
}

Valuef multV(Valuef v1, Valuef v2) {
	Valuef r;
	r.first = v1.first * v2.first;
	r.second = v1.second * v2.second;
	simplify(&r);
	return r;
}

Valuef divV(Valuef v1, Valuef v2) {
	Valuef r;
	r.first = v1.first * v2.second;
	r.second = v1.second * v2.first;
	simplify(&r);
	return r;
}

Valuef valuefConverter(char * str) {
	char* str1 = str;
	char* str2, *strTemp;
	strTemp = str;
	while(*str1 != 'b'){
		str1++;
		str++;
	}
	*str = '\0';
	str1++;
	str2 = strTemp;
	Valuef tempV;
	tempV.first = atoi(str2);
	tempV.second = atoi(str1);
	return tempV;
}

Valuef tempValuefCreator(int a, int b){
	Valuef tempV;
	tempV.first = a;
	tempV.second = b;
	return tempV;

}

int valuef_eq(Valuef v1, Valuef v2) {
    return v1.first * v2.second == v2.first * v1.second;
}

int valuef_gt(Valuef v1, Valuef v2) {
    return v1.first * v2.second > v2.first * v1.second;
}
