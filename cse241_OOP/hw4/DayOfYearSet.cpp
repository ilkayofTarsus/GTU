#include <iostream>
#include"DayOfYearSet.h"
using namespace std;

namespace dayofyear{


	typedef DayOfYearSet::DayOfYear  tarsus;

		DayOfYearSet::DayOfYearSet(list <tarsus> l){
			
			size_v = 0;
			
			obje = new tarsus;

			auto iter = l.begin();

			while(l.size() != 0){
				iter = l.begin();
				(*this) + *iter;
				l.pop_front();
			}
		
		}

		DayOfYearSet::DayOfYearSet(){
		
			size_v = 0;	
			obje = new DayOfYear;
			obje->next = nullptr;
			
		}
		
		DayOfYearSet::~DayOfYearSet(){
		
			while(obje != nullptr){
			
				tarsus* temp = obje;          
	      			obje = obje->next;      
	      			delete temp;  

			}
		}
		
		
		DayOfYearSet::DayOfYearSet(const DayOfYearSet& list){

			if (list.obje == nullptr) {
			    obje = nullptr;
			    size_v = 0;	
			    return;
			}			

			auto iter = new tarsus;
			decltype(iter) temp = new tarsus;
			obje = new tarsus;
			temp = list.obje->next;			
			iter = obje;			
			
			
			while(temp != nullptr){
				
				decltype(iter) newNode = new tarsus;
				newNode->setday(temp->getday());
				newNode->setmonth(temp->getmonth());
				iter->next = new tarsus;
				iter->next = newNode;			
				
				iter = newNode;
 				size_v++;
 				temp = temp->next;
			}
		}
		
		
		const DayOfYearSet& DayOfYearSet::operator=(const DayOfYearSet& other){
			
			if (other.obje == nullptr) {
				    obje = nullptr;
				    size_v = 0;	
				}			
			else{
			
				while(obje != nullptr){
			
					tarsus* temp1 = obje;          
	      				obje = obje->next;      
	      				delete temp1;  

				}
				
				auto iter = new tarsus;
				decltype(iter) temp = new tarsus;
				obje = new tarsus;
				temp = other.obje->next;			
				iter = obje;			
				
				while(temp != nullptr){
					
					decltype(iter) newNode = new tarsus;
					newNode->setday(temp->getday());
					newNode->setmonth(temp->getmonth());
					iter->next = new tarsus;
					iter->next = newNode;			
					
					iter = newNode;
	 				size_v++;
	 				temp = temp->next;
				}
			
				size_v = other.size();			
			}
		
		return (*this);
		
		
		}
		
		
		ostream& operator<<(ostream& os, const DayOfYearSet& set){
		
			auto iter = new tarsus;
			iter = set.obje;

			os << " { " ;
			
			iter = iter->next;
			
			while(iter != nullptr){

				os << " '"<< *iter << "' ";	
				iter = iter->next;
			}
			
			os << " } " ;
			
			return os;
		}
		
		bool DayOfYearSet::operator==(const DayOfYearSet& other) const {
			
			if(size_v != other.size()) return false;
			
			for(int a = 0; a < size_v; a++){
				if(other[a] != (*this)[a]) return false ;
			}
			return true;
		}
		
		bool DayOfYearSet::operator!=(const DayOfYearSet& other ) const {
		
			if(size_v != other.size()) return true;
				
				for(int a = 0; a < size_v; a++){
					if(other[a] != (*this)[a]) return true ;
				}
			return false;
		}
		
		const DayOfYearSet& DayOfYearSet::operator+(const tarsus& other){
		
		tarsus* temp = new tarsus;
		auto iter1 = obje;
		DayOfYearSet kume ;
		
		temp->setday(other.getday());
		temp->setmonth(other.getmonth());

			
		if(gozat(other)){	
			
			if(size_v == 0){

				obje->next = temp;
				obje->next->next = nullptr;
				size_v++;
			
			}
			else if(size_v == 1){
				
				if(other > *this->obje->next){
					
					obje->next->next = new tarsus;		
					obje->next->next = temp;
					obje->next->next->next = nullptr;
					size_v++;
				}
				else if(other < *this->obje->next){
					
					
					temp->next = new tarsus;
					temp->next = obje->next;
					obje->next = temp;
					obje->next->next->next = nullptr;
					size_v++;
				}
			}	
			else{
				tarsus* iter = new tarsus;
				iter = obje;
				
				while(iter->next != nullptr && *temp > *iter->next){
				
					iter = iter->next;
				}	
				if(iter->next == nullptr){		
					
					iter->next = new tarsus;				
					iter->next = temp;
					iter->next->next = nullptr;
					size_v++;
				}
				else{
			
					temp->next = new tarsus;
					temp->next = iter->next;
					iter->next = temp;
					size_v++;
				}
			}
		
		}
		
		
		return *this;
		
		}
		
		const DayOfYearSet& DayOfYearSet::operator-(const tarsus& other) {
			
			tarsus* iter = new tarsus;
			tarsus* temp = new tarsus;
			iter = obje;

			while(iter != nullptr && *iter->next != other){
			
			iter=iter->next;
			
			
			}

		
			temp = iter->next;
			iter->next = iter->next->next;
			delete temp;
			size_v--;

			return *this;
		}
		
		const DayOfYearSet DayOfYearSet::operator-(const DayOfYearSet& other) {
			
			DayOfYearSet kume;
			bool kontrol = true;
			
			for(int a=0; a < size_v; a++){
				
				kontrol = true;
				
				for(int b=0; b < other.size(); b++){
			
					if((*this)[a] == other[b]) kontrol = false;
				}
				
				if(kontrol) kume + (*this)[a];

			}
			return kume;
		}	
		
		const DayOfYearSet DayOfYearSet::operator^(const DayOfYearSet& other) const{
		
			DayOfYearSet temp,yedek;
			int k_size=0, durum = 0;
			tarsus iter1,iter2;
			
			if(size_v == 0){
				return *this;
			}
			else if(other.size() == 0){
				return other;
			}
			
			
			if(size_v > other.size()){
				k_size = other.size();
				durum = 2;
			}
			else{
				k_size = size_v;
				durum = 1;
			}
			
			switch(durum){
			
			case 2:
				
				for(int a = 0; a < k_size; a++){
	
					for(int b = 0; b < size_v; b++){

						if( (*this)[b] == other[a] ){
							temp+(other)[a];			
						}
					}
				}
			break;
			
			case 1:
				

				for(int a = 0; a <k_size; a++){
					for(int b = 0; b < other.size(); b++){
						if((*this)[a] == other[b]) temp+(other)[b];			
					}
				}



			break;
			
			
			}
			
			return temp;
		}
			
		const DayOfYearSet DayOfYearSet::operator!() const{
			
			tarsus kontrol;
			DayOfYearSet kume;
			bool bl = true;
							
			for(int a = 0; a < 365-size_v; a++){
			
				bl = true;
				
				for(int b = 0; b < size_v; b++){
					
					if(kontrol == (*this)[b]) bl = false;
					
				}
				
				if(bl) kume + kontrol ;
				++kontrol;
			
			}
			
			return kume;
		}
			
		tarsus& DayOfYearSet::operator[](int index) const{
			if(index >= size_v){
			
			 	cerr << "index is too big" << endl;
			 	exit(1);
					
			}	
			
			else if(index < 0){

			 	cerr << "index is too small" << endl;
			 	exit(1);
			}
			
			else{
				
				tarsus* iter = new tarsus;
				iter = obje->next;
				
				for(int a = 0; a < index ; a++){
				
					iter = iter->next;			
				
				}
				
				return *iter;
				
			}
		
		
		}
		
		void DayOfYearSet::remove(const tarsus& other){
		
		
		tarsus* iter = new tarsus;
		tarsus* temp = new tarsus;
		iter = obje;
		
		while(iter != nullptr && *iter->next != other){
		
			iter=iter->next;
		
		
		}
			
		temp = iter->next->next;
		delete temp;
		iter->next = temp;
		size_v--;
				
		}
		
		int DayOfYearSet::size() const{ return size_v; }
		
		
		
		const DayOfYearSet DayOfYearSet::operator+(const DayOfYearSet& other) const{
		
			DayOfYearSet birlesim;
			
			for(int a = 0; a < size_v; a++){
				birlesim + (*this)[a];
			}
		
			for(int a = 0; a < other.size(); a++){
				birlesim + (other)[a];
			}
		
			return birlesim;		
		
		
		}


		bool DayOfYearSet::gozat(const DayOfYearSet::DayOfYear& other ) const{
		
			for (int a = 0; a < size_v; a++){
			
				if((*this)[a] == other) return false;
			
			}
		return true;
		
		}

									/////////////////////////  	end of member-functıons of set  /////////////////////////////

	tarsus::DayOfYear(int _day,int _month ){

		setday(_day);
		setmonth(_month);
		set();



	}

	void tarsus::input( ) {
		
		
		int _day = 1;
		int _month = 1;
		
		cout << "Enter the day :" ;
		cin >> _day;
		
		cout << "Enter the month :" ;
		cin >> _month;
		
		
		
		setday(_day);
		setmonth(_month);
		set();
		
	}


	void tarsus::set( ) {
		
		int _day = day;
		int _month = month;
		
		if((day > 31) && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||month == 10 || month == 12) ){   // eger gun sayısı fazla ıse ayarlama yapar
		
			setday(_day % 31);
			
			if(_month + _day/31 == 13) setmonth(1);
			else setmonth(_month + _day/31);
			
				
		
		}

		else if((day > 30) && (month == 4 || month == 6 || month == 9 || month == 11) ){   // eger gun sayısı fazla ıse ayarlama yapar
		
			setday(_day % 30);
			setmonth(_month + _day/30);
				
		
		}
		
		else if((day > 28) && (month==2) ){ 				//subat ayı ıcın ayar
		
			setday(_day % 28);
			setmonth(_month + _day/28);
		
		}
		
	}


	int tarsus::getday() const{ return day;}

	int tarsus::getmonth() const{return month;}

	void tarsus::setday(int d) {
		
		day = d;

	}

	void tarsus::setmonth(int m) {

		month = m;

	}

	ostream& operator<<(ostream& os , const tarsus& obje) {

		
		os << obje.getday() << " " ;
		
		switch (obje.month)
		
		{

			case 1:

				cout << "Ocak "; break;

			case 2:

				cout << "Subat "; break;

			case 3:

				cout << "Mart "; break;

			case 4:

				cout << "Nisan "; break;

			case 5:

				cout << "Mayis "; break;

			case 6:
				
				cout << "Haziran "; break;

			case 7:

				cout << "Temmuz "; break;

			case 8:

				cout << "Agustos "; break;

			case 9:
				cout << "Eylul "; break;

			case 10:

				cout << "Ekim "; break;

			case 11:

				cout << "Kasim "; break;

			case 12:

				cout << "Aralik "; break;

		}	
		
		return os;

	}


	bool tarsus::operator>(const tarsus& other)const{

		if( month > other.getmonth() )	 return true;

		else if( month == other.getmonth() && day > other.getday())	 return true;
	return false;

	}

	bool tarsus::operator<(const tarsus& other)const{


			if(month < other.getmonth() ) return true;
			
			else if( month == other.getmonth() && day < other.getday()) return true;


	return false;
	}	
	bool tarsus::operator==(const tarsus& other)const{


	return (other.getmonth() == month && other.getday() == day) ;
	}
	bool tarsus::operator!=(const tarsus& other)const{

	return ( other.getmonth() != month && other.getday() != day) ;
	}

	tarsus& tarsus::operator++(){

		setday(getday()+1);
		set();
		return *this;	
	}
}

