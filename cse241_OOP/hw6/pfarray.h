#include <iostream>
#include<memory>
#include<typeinfo>
#include<algorithm>
using namespace std;

namespace ilkay{

	template<typename T>
	class pfarray{						

	public:
		
		pfarray();															// *		* //
		pfarray(pfarray&& other): _size(other.size()), used(other.get_used()), ptr(other.get_ptr()){ 					// *		* //
			other.get_ptr().reset();												// *		* //
			cout << "move cp constructor has been called" << endl;									// *		* //
		}																// *  big five	* //
		pfarray(const pfarray&);													// *		* //
		void operator=(const pfarray&);													// *		* //
																		// *		* //
		void operator=(pfarray&& other){ 												// *		* //
			
			set_size(other.size());										
			set_used(other.get_used());
			ptr = other.get_ptr();
			other.get_ptr().reset();
			cout << "move assıgnment has been called" << endl;
		}
		~pfarray(){};															//
		class Iterator{														//Inner Iterator class
			
		typedef Iterator iter_t;

		public:

			Iterator();
			Iterator(T&);
			Iterator(T*);
			~Iterator(){}
			
			T& operator*() const;
			T* operator->() const;
			iter_t&operator++();
			iter_t operator++(int);
			iter_t& operator--();
			iter_t operator--(int);
			iter_t& operator=(const iter_t&);
			bool operator==(const iter_t& ) const;
			bool operator!=(const iter_t& ) const;
			auto get_iter()const{return iter;}
			void set_iter(T& value){}
			void print(const iter_t& obje)const{
				cout << *(obje) << " ";
			}
			
		private:
			T* iter;
		};
		Iterator begin()const;
		Iterator end()const;
		const Iterator cbegin()const;
		const Iterator cend()const;
		T& operator[](int)const;
		void add(T value);
		auto get_ptr()const{ return ptr;}
		bool empty()const;
		int size()const{ return _size;}
		void erase(const Iterator&);
		int get_used()const {return used;}
		void set_used(int a){ used = a;}
		void set_size(int a){ _size = a;}	
	private:

		int _size;
		int used;
		shared_ptr<T> ptr;														//Array pointer by shared_ptr
		
	};
	
} 	// end of namespace	

