#include <iostream>
#include <list>
using namespace std;

namespace dayofyear {

	class DayOfYearSet {										// 		order-based set class		 // 

	public:	

		class DayOfYear {	


			public:	

				DayOfYear(int _day = 1,int _month = 1);					//constructor
				int getday() const;							// *						*
				int getmonth() const;							// *						*
				int getyear() const;							// 		accessors and mutators		*
				void setday(int) ;							// *						*
				void setmonth(int) ;							// *   						*
				void set();								// fixes the invalid dates
				void input ();
				friend ostream& operator<<(ostream&, const DayOfYearSet::DayOfYear&);
				bool operator>(const DayOfYearSet::DayOfYear&)const ;			//overloaded to compare
				bool operator<(const DayOfYearSet::DayOfYear&)const ;			// "         "   "
				bool operator==(const DayOfYearSet::DayOfYear&)const ;			// "         "   "
				bool operator!=(const DayOfYearSet::DayOfYear&)const ;			// "         "   "
				DayOfYear& operator++();						// overloaded to help for finding to complement of a set
				DayOfYear* next;							// it has a pointer to link objects each other  !!! for linkedlist 
	
			protected:

				int day;
				int month;
				int year;


			};
		
		DayOfYearSet(list<DayOfYear>);								//list initiliziater constructor
		DayOfYearSet();										//no param constructro
		DayOfYearSet(const DayOfYearSet& list);							// copy constructor
		~DayOfYearSet();									// destructor 				// BIG THREE IS OKEY
		friend ostream& operator<<(ostream&, const DayOfYearSet&) ;
		bool operator==(const DayOfYearSet&) const ;
		bool operator!=(const DayOfYearSet&) const ;
		const DayOfYearSet& operator+(const DayOfYearSet::DayOfYear&) ;
		const DayOfYearSet operator+(const DayOfYearSet&)const ;
		const DayOfYearSet& operator-(const DayOfYearSet::DayOfYear&) ;
		const DayOfYearSet operator-(const DayOfYearSet&);
		const DayOfYearSet operator^(const DayOfYearSet&)const ;
		const DayOfYearSet& operator=(const DayOfYearSet&);
		const DayOfYearSet operator!() const;
		DayOfYear& operator[](int) const;
		void remove(const DayOfYear&);
		int size() const;
		void setsize(int _size){ size_v = _size ;}
		bool gozat(const DayOfYearSet::DayOfYear& ) const;					//helps to find whether a set has a dayofyear object 
	private:
		
		DayOfYear *obje;									//a head pointer for linkedlist
		int size_v;
	};
	
}
