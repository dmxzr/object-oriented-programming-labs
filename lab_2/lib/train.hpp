#ifndef _TRAIN_HPP_
#define _TRAIN_HPP_
#include <limits>
#include "carriage.hpp"
using namespace std;

class Train {
private:
	Carriage *carriages;
	size_t size;
	size_t capacity;

	void Resize(size_t new_capacity); // dCarriageType select_carriage_type();
	
	size_t GetMostEmptyCarriage(CarriageType type) const; // d
	double GetAvarageOccupancy() const; //d

public:
	Train(); // d
	Train(const Carriage* cars, size_t count); // d
	Train(const Carriage& carriage); // d
	Train(const Train& other); // d
	Train(Train&& other); // d
	~Train(); // d

	Train& operator=(const Train& other); // d
	Train& operator=(Train&& other); // d
	Train& operator+=(const Carriage& carriage); // d
	Carriage& operator[](size_t index); // d
	const Carriage& operator[](size_t index) const; //d


	void DeleteCarriage(size_t index); //d 
	void Redistribute();
	bool Boarding(size_t count, CarriageType type); //d 
	void OptimizeCarriages(); // d
	void PlaceRestaurantOptimally();
	size_t GetSize() const; // d 

	friend ostream& operator<<(ostream& out, const Train& train); // d
	friend istream& operator>>(istream& in, Train& train); // d
	
};

#endif /* _TRAIN_HPP_ */
