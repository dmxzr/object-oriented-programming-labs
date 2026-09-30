#include "../lib/carriage.hpp"


Carriage::Carriage():
	type(CarriageType::UNDEFINED), capacity(0), occupied(0) {}


Carriage::Carriage(CarriageType type, size_t capacity, size_t occupied):
	type(type), capacity(capacity), occupied(occupied) {
		if(occupied > capacity) {
			std::cout << "Occupied seats cannot exceed capacity" << std::endl;
		}
	}


Carriage::Carriage(CarriageType type):
	type(type), capacity(GetCapacityOfCarriage()), occupied(0) {}


Carriage::Carriage(const Carriage& other):
	type(other.type), capacity(other.capacity), occupied(other.occupied) {}


Carriage::Carriage(Carriage&& other):
	type(CarriageType::UNDEFINED), capacity(other.capacity = 0), occupied(other.occupied = 0) {}





size_t Carriage::GetCapacityOfCarriage() const {
	switch(type) {
		case CarriageType::SEDENTARY:
			return 100;
		case CarriageType::ECONOMY:
			return 50;
		case CarriageType::LUXURY:
			return 20;
		case CarriageType::RESTAURANT:
			return 30;
		default:
			return 0;
	}
}


std::string Carriage::GetTypeNameOfCarriage() const {
	switch (type) {
		case CarriageType::SEDENTARY:
			return "Сидячий";
		case CarriageType::ECONOMY:
			return "Эконом";
		case CarriageType::LUXURY:
			return "Люкс";
		case CarriageType::RESTAURANT:
			return "Ресторан";
		default:
			return "Не определен";
	    }
}


double Carriage::GetPercent() const {
	return capacity == 0 ? 0 : (static_cast<double>(occupied) / capacity) * 100;
}


CarriageType Carriage::GetTypeOfCarriage() const {
	return type;
}


size_t Carriage::GetOccupiedSeats() const {
	return occupied;
}


size_t Carriage::GetMaxCapacity() const {
	return capacity;
}




bool Carriage::IsBoarding(size_t count) { 
	if(occupied + count <= capacity) {
		occupied += count;
		return true;
	}
	return false;
}


bool Carriage::IsDropOff(size_t count) {
	if(count <= occupied) {
		occupied -= count;
		return true;
	}
	return false;
}




Carriage& Carriage::operator=(const Carriage& other) {
	if(this != &other) {
		type = other.type;
		capacity = other.capacity;
		occupied = other.occupied;
	}
	return *this;
}


Carriage& Carriage::operator=(Carriage&& other) {
	if (this != &other) {
		type = other.type;
		capacity = other.capacity;
		occupied = other.occupied;
	        
		other.type = CarriageType::UNDEFINED;
		other.capacity = 0;
		other.occupied = 0;
	}
	return *this;
}


void operator>>(Carriage& A, Carriage& B){
	if(A.type != B.type) {
		std::cout << "Cannot transfer passengers between different carriage types" << std::endl;
	}

	size_t available = B.capacity - B.occupied;
	size_t transfer = std::min(A.occupied, available);

	A.occupied -= transfer;
	B.occupied += transfer;
}


std::ostream& operator<<(std::ostream& out, const Carriage& carriage) {
	out << "Тип: " << carriage.GetTypeNameOfCarriage() << "\n"
		<< "Вместимость: " << carriage.capacity << "\n"
		<< "Занято мест: " << carriage.occupied	<< "\n"
		<< "Заполняемость: " << carriage.GetPercent() << "%";
	return out;		
}


std::istream& operator>>(std::istream& in, Carriage& carriage) {
	int type_int;
	std::cout << "Выберите тип вагона (0 - Сидячий, 1 - Плацкарт, 2 - Люкс, 3 - Ресторан): ";
	in >> type_int;

	carriage.type = static_cast<CarriageType>(type_int);
	carriage.capacity = carriage.GetCapacityOfCarriage();

	std::cout << "Введите количество занятых мест (максимум " << carriage.capacity << "): ";
	in >> carriage.occupied;

	if(carriage.occupied > carriage.capacity) {
		std::cout << "Occupied seats cannot exceed capacity" << std::endl;
	}

	return in;
}
