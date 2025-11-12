/*
 * Group 3
 * 
 * Name: Isaac Amedie, Michael Tiburcio, Ryan Vattuone, Guseerat Kakar
 * Email: iamedie@scu.edu, mtiburcio@scu.edu, rvattuone@scu.edu, gkakar@scu.edu
 * recipe for containers using C-style array
 */
#ifndef BAG_H
#define BAG_H
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <string.h>
#include <cstring>
namespace csen79
{
template<typename T>
  class Bag
  {
    static constexpr size_t DATASIZE = 5; // array size
  public:
    using Data = T; // create an alias for the data
    class BagIter{

      public: 
        BagIter(Data *i):ptr(i) {}
        Data operator*() {return *ptr;}
        BagIter &operator++() {++ptr; return *this;}
        BagIter operator++(int) {BagIter r(ptr); ++ptr; return r;}
        bool operator!=(const BagIter &x) const {return ptr != x.ptr;}
        bool operator==(const BagIter &x) const { return ptr == x.ptr; }
      private:
        Data *ptr;
    };
    Bag() : data{nullptr}, count{0}, capacity{DATASIZE} {}

    // rule of 5
    ~Bag();
    Bag(const Bag &);
    Bag(Bag &&);
    Bag &operator=(const Bag &);
    Bag &operator=(Bag &&rhs);

    // access functions
    const Data &getData(const Data) const;
    void setData(const int, const Data &);
    void insert(const Data &);
    void size() const;
    size_t getCount() const { return count; }
    void dump(const Data &);
    void print() const;
    bool toggleFail();
    BagIter begin() {return BagIter(data);}
    BagIter end() { return BagIter(data + count); }

  private:
    // data storage
    Data *data;
    bool fail;
    size_t count;
    size_t capacity;
  };

  //Destructor 
  template<typename T>
  Bag<T>::~Bag()
  {
    if (data != nullptr)
      delete[] data;
    count = 0;
    fail = false;
  }

  // assignment
  template<typename T>
  Bag<T> &Bag<T>::operator=(const Bag &rhs)
  {
    std::cout << "assign" << std::endl;
    memcpy(this->data, rhs.data, capacity);
    return *this;
  }

  // move constructor
  template<typename T>
  Bag<T>::Bag(Bag &&rhs)
  {
    std::cout << "move constructor; calling assignment" << std::endl;
    this->operator=(rhs);
  }

  // copy constructor
  template<typename T>
  Bag<T>::Bag(const Bag &rhs)
  {
    std::cout << "copy; calling assignment" << std::endl;
    this->operator=(rhs);
  }
  
  // move
  template<typename T>
  Bag<T> &Bag<T>::operator=(Bag &&rhs)
  {
    std::cout << "move; calling assign" << std::endl;
    return this->operator=(rhs);
  }

  // simple asssess functions
  // replace them with appropriate ones for assignments
  template<typename T>
  const Bag<T>::Data &Bag<T>::getData(const Data i) const
  {
    if (i < 0 || i >= DATASIZE)
      throw std::out_of_range(std::string("index out of range"));
    return data[i];
  };

  template<typename T>
  void Bag<T>::setData(const int i, const Data &d)
  {
    if (i < 0 || i >= DATASIZE)
      throw std::out_of_range(std::string("index out of range"));
    data[i] = (Data)d;
  }

  template<typename T>
  void Bag<T>::insert(const Data &value)
  {
	if (count == 0){
        try {data = new Data[DATASIZE]();}
        catch(std::bad_alloc &e){data = nullptr;}
  }
	
	std::cout << "Attempting to insert: " << value << std::endl;

	for (int i = 0; i < count; i++) {
		if (data[i] == value){
			std::cout << "Already in set at location : " << i << std::endl;
			return;
		}
	}
   	 //if capacity exceeded
   	 if (count == capacity){
		std::cout << "Increasing set capacity" << std::endl;
		if (fail)
			throw std::bad_alloc();
    capacity = capacity*2;
    Data* temp;
    try {temp = new Data[capacity]();} 
    catch (const std::bad_alloc& e) {
      std::cerr << "Memory allocation failed: " << e.what() << std::endl;}

    //copies data
    if constexpr (std::is_trivially_copyable<Data>::value) {
      std::memcpy(temp, data, (capacity/2) * sizeof(Data));
    } 
    else {
      // Non-trivial types
      for (size_t i = 0; i < count; ++i)
        temp[i] = std::move(data[i]);
    }

    delete[] data;
		data = temp;
    }
	
    	data[count] = value;
	count++;
  size();
  print();
  }

  template<typename T>
  void Bag<T>::dump(const Data &value)
  {
    	if (count == 0)
      	throw std::underflow_error("Queue underflow");
	
	std::cout << "Attempting to dump: " << value << std::endl;

    	for (int i = 0; i < count; i++)
		if (data[i] == value) {
    			data[i] = data[count-1];
    			count--;
			return;
		}

	std::cout << "There is no " << value << " in set" << std::endl;
  };

  template<typename T>
  void Bag<T>::size() const 
  {
    std::cout << "Size: " << count << std::endl;
  };

  template<typename T>
  void Bag<T>::print() const
  {
    	if (count == 0)
    	{
      		std::cout << "[Empty]" << std::endl;
      		return;
    	}
    	std::cout << "Set: ";
    	for (size_t i = 0; i < count; i++)
    		std::cout << data[i] << " ";
	
	std::cout << std::endl;
  }

  template<typename T>
  bool Bag<T>::toggleFail() {
	fail = !fail;
	return fail;
  };
}
#endif // BAG_H
