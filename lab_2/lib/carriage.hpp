#ifndef _CARRIAGE_HPP_
#define _CARRIAGE_HPP_

#include <iostream>



enum class CarriageType {
	SEDENTARY,
	ECONOMY,
	LUXURY,
	RESTAURANT,
	UNDEFINED
};

class Carriage {
private: 
	CarriageType type;
	size_t capacity;
	size_t occupied;

public:
	Carriage();
	Carriage(CarriageType type, size_t capacity, size_t occupied);
	Carriage(const Carriage& other);
	Carriage(Carriage&& other);
	Carriage(CarriageType type);
	
	//getters

	size_t GetCapacityOfCarriage() const;
	std::string GetTypeNameOfCarriage() const;
	double GetPercent() const;
	CarriageType GetTypeOfCarriage() const;
	size_t GetOccupiedSeats() const;
	size_t GetMaxCapacity() const;


	bool IsBoarding(size_t count);
	bool IsDropOff(size_t count);


	Carriage& operator=(const Carriage& other); 
	Carriage& operator=(Carriage&& other);

	friend void operator>>(Carriage& A, Carriage& B);
	friend std::ostream& operator<<(std::ostream& out, const Carriage& carriage);
	friend std::istream& operator>>(std::istream& in, Carriage& carriage);
};




#endif /* _CARRIAGE_HPP_ */
