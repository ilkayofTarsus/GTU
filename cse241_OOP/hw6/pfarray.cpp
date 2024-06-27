#include"pfarray.h"

	namespace ilkay{
	template<typename T> pfarray<T>::pfarray() : _size(2) , used(0){

		shared_ptr<T[]> ptr(new T[_size]);
	}
	template<typename T> bool pfarray<T>::empty()const{
		bool ret;
		
		if( 0 == get_used() ) ret = true;
		else if( 0 > get_used() ) throw "size is negative";
		else ret = false;
		
		return ret;
	}
	template<typename T> void pfarray<T>::add(T value){

		if (0 == used){
			shared_ptr<T> temp(new T[_size]);
			ptr = temp;
		}

		else if (_size == used){
			
			_size *= 2;
			shared_ptr<T> newPtr(new T[_size]);
			for (int i = 0; i < used; i++)
			    newPtr.get()[i] = ptr.get()[i];
				
			ptr.reset();
			ptr = newPtr;
		}

		ptr.get()[used++] = value;	
	}
	template<typename T> T& pfarray<T>::operator[](int index)const{

		if(index == get_used()) throw "index is big";
		if(index < 0 ) throw "index is negative";

		return ptr.get()[index];
	}
	template<typename T> void pfarray<T>::erase(const Iterator& pf_iter){

	bool kontrol = false;
		for(int a = 0; a < used; a++){
		
			if( (*this)[a] == *(pf_iter.get_iter())){
				
				for(int b = a; b < used-1; b++) ptr.get()[b] = ptr.get()[b+1];
				
				ptr.get()[(used--)-1] = 0;
				
				kontrol = true;
			}	
			
			if(kontrol) break;
		}

	if(!kontrol) throw "Can not find";
	}
	template<typename T> pfarray<T>::pfarray(const pfarray& other){
		
		shared_ptr<T[]> ptr(new T[other.size()]);
		for(int a = 0; a < other.get_used(); a++) (*this).add(other[a]);
		set_size(other.size());
		set_used(other.get_used());
	}

	template<typename T> void pfarray<T>::operator=(const pfarray& other){
		if(&other == this) throw "assigning same class objects";
		else{
			shared_ptr<T[]> ptr(new T[other.size()]);
			for(int a = 0; a < other.get_used(); a++) (*this).add(other[a]);
				set_size(other.size());
				set_used(other.get_used());
		}
	}
	template<typename T> 
	typename pfarray<T>::Iterator pfarray<T>::begin()const{
		if(0 == used) throw "There is no begin pointer";
		return Iterator (ptr.get()[0]);
	}
	template<typename T> 
	typename pfarray<T>::Iterator pfarray<T>::end()const{
		if(0 == used) throw "There is no end pointer";
		Iterator x(ptr.get()[0]);
		for(int a = 0; a < used; a++) x++;
		return x;
	}
	template<typename T> 
	const typename pfarray<T>::Iterator pfarray<T>::cbegin()const{
		if(0 == used) throw "There is no begin pointer";
		return Iterator (ptr.get()[0]);
	}
	template<typename T> 
	const typename pfarray<T>::Iterator pfarray<T>::cend()const{
		if(0 == used) throw "There is no end pointer";
		Iterator x(ptr.get()[0]);
		for(int a = 0; a < used; a++) x++;
		return x;
	}
	template<typename T> pfarray<T>::Iterator::Iterator(){
		iter = new T;
	}
	template<typename T> pfarray<T>::Iterator::Iterator(T* other){
		iter = new T;
		iter = other;
	}
	template<typename T> pfarray<T>::Iterator::Iterator(T& other){
		iter = new T;
		iter = &other;
	}
	template<typename T> T& pfarray<T>::Iterator::operator*() const{
		return *iter;
	}
	template<typename T>T* pfarray<T>::Iterator::operator->() const{
		return iter;
	}
	template<typename T> 
	typename pfarray<T>::Iterator& pfarray<T>::Iterator::operator++(){
		(iter)++;
		return *this;
	}
	template<typename T>
	typename pfarray<T>::Iterator pfarray<T>::Iterator::operator++(int){
		auto* temp = new T;
		temp = iter;
		iter++;
		return Iterator(temp);
	}
	template<typename T>
	typename pfarray<T>::Iterator& pfarray<T>::Iterator::operator--(){
		iter--;
		return *this;
	}
	template<typename T>
	typename pfarray<T>::Iterator pfarray<T>::Iterator::operator--(int){
		auto temp = make_shared(iter);
		iter--;
		return temp;
	}
	template<typename T>
	typename pfarray<T>::Iterator& pfarray<T>::Iterator::operator=(const Iterator& other){
		iter = other.get_other();
		return *this;
	}
	template<typename T>bool pfarray<T>::Iterator::operator==(const Iterator &other) const{
		return (iter == other.get_iter());
	}
	template<typename T>bool pfarray<T>::Iterator::operator!=(const Iterator &other) const{
		return (iter != other.get_iter());
	}
			
} // end of namespace
