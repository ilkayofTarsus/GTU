#include <iostream>
#include "DayOfYearSet.h"
#include <list>

using namespace std;
using namespace dayofyear;

int main(){

DayOfYearSet::DayOfYear d1{20,8},d2{15,8},d3{2,7},d4{3,1},d5{13},d6;



cout	 << "5 Dayofyear objects are created, (one of them created by no parameter constructor)"<< endl << endl
	<< "Objects are :" << endl << endl
	<< "d1 == " << d1 << endl
	<< "d2 == " << d2 << endl
	<< "d3 == " << d3 << endl
	<< "d4 == " << d4 << endl
	<< "d5 == " << d5 << endl
	<< "d6 == " << d6 << endl;

list <DayOfYearSet::DayOfYear> l1 {d1,d2,d3} ;
list <DayOfYearSet::DayOfYear> l2 {d4,d5};

DayOfYearSet s1(l1), s2(l2), s3,s4(l1);

cout 	<< endl << endl
	<<"4 sets of Dayofyear are created " << endl 
	<< endl << "Objects are : " << endl << endl
	<<"s1 == " << s1 << endl
	<<"s2 == " << s2 << endl
	<<"s3 == " << s3 << endl
	<<"s4 == " << s4 << endl << endl;

cout    << "s1 = s1 + s2 " << (s1+s2) << endl
	<< "s3 = s3 + s4 " << (s3+s4) << endl << endl
	<< "	(DayOfYearSet keep the dates in order)" << endl << endl
	<< "s1 = s1 + d6 " << (s1+d6) << endl
	<< "s3 = s3 + d2 " << (s3 + d2) << endl << endl
	<< "s1 = s1 - d6" << (s1-d6) << endl
	<< "s2 = s2 - d4" << (s2-d4) << endl << endl
	<< "s1 == " << s1 << endl << "s2 == " << s2 << endl << "s3 == " << s3 << endl << "s4 == " << s4 << endl<< endl
	<< "s1 ^ s4 == " << (s1^s4) << endl
	<< "s2 ^ s3 == " << (s2^s3)<< endl << endl
	<<"s1 - s3 "<< s1 - (s3) << endl 
	<<"s3 - s1 "<< s3 -s1 << endl
	<<"s1[0] == " << s1[0] << endl
	<<"s4[2] == " << s4[2] << endl
	<< "!s1 == "<< !s1 << endl << endl << endl
	<< "!s4 == " << !s4 << endl<< endl << endl << endl
	<< "if user gives a invalid dayofyear values, set functıon fixes it"<< endl;
	
	decltype(d1) d7(29,2), d8(32,12);
cout    <<endl <<endl << "/******************"  <<endl << endl 
	<< "*d7 is 29 subat and d8 is 32 aralik but set functıon fixes them so -->"<< endl
	<< "*d7 == " << d7 << endl
	<< "*d8 == " << d8 << endl
	<<" 				           	******************/"<<endl;
return 0;
}

