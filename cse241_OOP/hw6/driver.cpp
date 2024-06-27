#include<iostream>
#include<functional>
#include"pfarray.cpp"

using namespace std;
using namespace ilkay;

void print(pfarray<int>::Iterator);					// to test whether std::for_each can run 
void printc(pfarray<char>::Iterator);					

int main(){

try{

	pfarray<int> arr1, arr2;	
	pfarray<char> str1, str2;
	
	for(int a = 0; a < 5; a++) arr1.add(a*2);
	for(int a = 1; a < 10; a += 2) arr2.add(a);
	str1.add('i');
	str1.add('l');
	str1.add('k');
	str1.add('a');
	str1.add('y');

	str2.add('T');
	str2.add('a');
	str2.add('r');
	str2.add('s');
	str2.add('u');
	str2.add('s');

	cout <<"arr1 == "; 
	for(pfarray<int>::Iterator a : arr1 ) cout << *a << " ";
	cout << endl;

	cout <<"arr2 == "; 
	for(pfarray<int>::Iterator a : arr2 ) cout << *a << " ";
	cout << endl;

	cout <<"str1 == "; 
	for(pfarray<char>::Iterator a : str1 ) cout << *a << " ";
	cout << endl;

	cout <<"str2 == "; 
	for(pfarray<char>::Iterator a : str2 ) cout << *a << " ";
	cout << endl;

	cout << endl << "	Pfarray printed by range based for loop		" <<endl<< endl
	             << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;
	
	cout << "Erasing an element by erase functıon that takes Iterator class as an argument" << endl << endl;
	
	auto it1 = arr1.begin();
	auto it2 = str1.begin();
	
	for (int a = 0; a < 2; a++){
		it1++;																// post_increment operator 
		++it2;																// pre_increment operator		
	}
	
	cout << " 4 from arr1 has been erased "<< endl
	     << " k from str1 has been erased " << endl<< endl
	      		     << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;
	arr1.erase(it1);															//erase functions take Iterator
	str1.erase(it2);
	
	cout << "arr1 = ";
	for_each(arr1.cbegin(),arr1.cend(),print);												// for_each
	cout << endl<< "str1 = ";
	for_each(str1.begin(),str1.end(),printc);
	cout << endl << endl << "	 Values printed by std::for_each" << endl << endl
		             << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;

	auto p = find(arr1.begin().get_iter(),arr1.end().get_iter(),6);										//find
	cout << "The value of '6' has been found at " << p << " by std::find" << endl <<endl 
		             << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;

	cout << "str1 before the std::sort = " ;
	for_each(str1.begin(),str1.end(),printc);
	sort(str1.begin().get_iter(),str1.end().get_iter());
	cout << endl << endl<< "str1 after the std::sort = ";	
	for_each(str1.begin(),str1.end(),printc);
        cout <<endl <<endl
        			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;

	cout << "str1 assigned str2 by move assıgnment operator" << endl << endl;
	str1 = static_cast<pfarray<char>&&>(str2);												//move assıgnment operator
	cout <<endl <<  "str1 == ";
	for_each(str1.begin(),str1.end(),printc);
	cout <<endl << endl 
				<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;
	
	cout << "the arr1 before arr1=std::move(arr2) = " ;
	for_each(arr1.begin(),arr1.end(),print);	
	cout << endl;
	arr1 = move(arr2);															//move copy constructor
	cout << "the arr1 after arr1=std::move(arr2) = ";
	for_each(arr1.begin(),arr1.end(),print);
	cout <<endl << endl 
				<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;
	
	cout << "Time to throw exceptions" << endl;
	cout << endl<<arr1[-1] << endl;	
}

catch(const char* exp){

	cout << "catched = " << exp <<endl;
}

return 0;
}
void print(pfarray<int>::Iterator it){
	cout << *it << " ";
}
void printc(pfarray<char>::Iterator it){
	cout << *it << " ";
}
