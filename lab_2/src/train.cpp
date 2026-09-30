#include "../lib/train.hpp"


Train::Train():
	carriages(new Carriage[1]), size(0), capacity(1) {}

Train::Train(const Carriage* cars, size_t count):
	carriages(new Carriage[count]), size(count), capacity(count) {
		for(size_t i = 0; i < size; i++){
			carriages[i] = cars[i];
		}
	}

Train::Train(const Carriage& carriage):
	carriages(new Carriage[1]), size(1), capacity(1) {
		carriages[0] = carriage;
	}

Train::Train(const Train& other):
	carriages(new  Carriage[other.capacity]), size(other.size), capacity(other.capacity) {
		for(size_t i = 0; i < size; i++) {
			carriages[i] = other.carriages[i];
		}
	}

Train::Train(Train&& other):
	carriages(other.carriages = nullptr), size(other.size = 0), capacity(other.capacity = 0) {}

Train::~Train() {
	delete[] carriages;
}




std::ostream& operator<<(std::ostream& out, const Train& train) {
	out << "В поезде " << train.size << " вагонов:\n";
	for(size_t i = 0; i < train.size; i++){
		out << "Вагон " << i + 1 << ":\n" << train.carriages[i] << "\n";
	}
	return out;
}

std::istream& operator>>(std::istream& in, Train& train) {
	size_t count;
	std::cout << "Введите кол-во вагонов: ";
	in >> count;

	delete[] train.carriages;
	train.capacity = count;
	train.size = 0;
	train.carriages = new Carriage[count];

	for(size_t i = 0; i < count; i ++) {
		std::cout << "\nВведите информацию для вагона " << i + 1 << ":\n";
		in >> train.carriages[train.size++];
	}

	return in;
}


Train& Train::operator=(const Train& other) {
	if(this != &other) {
		delete[] carriages;
		capacity = other.capacity;
		size = other.size;
		carriages = new Carriage[capacity];
		for(size_t i = 0; i < size; i++) {
			carriages[i] = other.carriages[i];
		}
	}
	return *this;
}


Train& Train::operator=(Train&& other) {
	if(this != &other) {
		delete[] carriages;
		carriages = other.carriages;
		size = other.size;
		capacity = other.capacity;
		other.carriages = nullptr;
		other.size = 0;
		other.capacity = 0;
	}
	return *this;
}


Train& Train::operator+=(const Carriage& carriage) {
	if(size == capacity) {
		Resize(size * 2);
	}

	carriages[size] = carriage;
	size+=1;
	return *this;
}


Carriage& Train::operator[](size_t index) {
	if(index > size) {
		std::cout << "Invalid index" << std::endl;
	}
	return carriages[index];
}

const Carriage& Train::operator[](size_t index) const {
	if(index > size) {
		std::cout << "Invalid index" << std::endl;
	}

	return carriages[index];
}


void Train::Resize(size_t new_capacity) {
	if(capacity >= new_capacity) {
		std::cout << "Input new capacity more than existing" << std::endl;
	}

	Carriage* old_carriages = carriages;
	Carriage* new_carriages = new Carriage[new_capacity];

	for(size_t i = 0; i < size; i++) {
		new_carriages[i] = old_carriages[i];
	}

	delete[] old_carriages;
	carriages = new_carriages;
	capacity = new_capacity;
}


size_t Train::GetMostEmptyCarriage(CarriageType type) const {
	double min_occupancy = 100.0;
	size_t index = size;

	for(size_t i = 0; i < size; i++) {
		if(carriages[i].GetTypeOfCarriage() == type) {
			double occupancy = carriages[i].GetPercent();
			if(occupancy <= min_occupancy) {
				min_occupancy = occupancy;
				index = i;
			}
		}
	}
	return index;
}


double Train::GetAvarageOccupancy() const {
	if(size == 0) return 0.0;

	double total = 0.0;
	size_t count = 0;
	for(size_t i = 0; i < size; i++) {
		if(carriages[i].GetTypeOfCarriage() != CarriageType::RESTAURANT && carriages[i].GetTypeOfCarriage() != CarriageType::LUXURY) {
			total += carriages[i].GetPercent();
			count++;
		}
	}
	return count > 0 ? total / count : 0.0;
}


void Train::DeleteCarriage(size_t index) {
	if( index >= size) {
		std::cout << "Invalid carriage index" << std::endl;
	}

	for (size_t i = index; i < size - 1; i++) {
		carriages[i] = std::move(carriages[i+1]);
	}
	size--;
}


bool Train::Boarding(size_t count, CarriageType type) {
	size_t target = GetMostEmptyCarriage(type);
	if(target == size) return false;
	return carriages[target].IsBoarding(count);
}





size_t Train::GetSize() const {
	return size;
}



void Train::OptimizeCarriages() {
	bool optimized;
	do {
		optimized = false;
		for(size_t i = 0; i < size; i++) {
			for(size_t j = i + 1; j < size; j++ ) {
				if(carriages[i].GetTypeOfCarriage() == carriages[j].GetTypeOfCarriage() &&
				 carriages[i].GetTypeOfCarriage() != CarriageType::RESTAURANT) {
					carriages[i] >> carriages[j];
					if(carriages[i].GetPercent() == 0) {
						DeleteCarriage(i);
						optimized = true;
						break;
					}
					if(carriages[j].GetPercent() == 0) {
						DeleteCarriage(j);
						optimized = true;
						break;
					}
				}
				
			}
			if(optimized) break;
		
		}
	}
		while(optimized);
}




void Train::Redistribute() {
	for(CarriageType type : {CarriageType::SEDENTARY, CarriageType::ECONOMY, CarriageType::LUXURY}) {
		size_t total_passengers = 0;
		size_t total_capacity = 0;
		size_t count_type = 0;

		for(size_t i = 0; i < size; i++) {
			if(carriages[i].GetTypeOfCarriage() == type) {
				total_passengers += carriages[i].GetOccupiedSeats();
				total_capacity += carriages[i].GetCapacityOfCarriage();
				count_type++;
			}
		}
		if(count_type == 0) continue;

		double target_occupancy = static_cast<double>(total_passengers) / count_type;

		for(size_t i = 0; i < size; i++) {
			if(carriages[i].GetTypeOfCarriage() == type) {
				double current_occupancy = carriages[i].GetPercent();

				if(current_occupancy > target_occupancy) {
					size_t excess = static_cast<size_t>(carriages[i].GetOccupiedSeats() - target_occupancy * carriages[i].GetMaxCapacity() / 100.0);

					for(size_t j = 0; j < size && excess > 0; j++) {
						if(i != j && carriages[j].GetTypeOfCarriage() == type && carriages[j].GetPercent() < target_occupancy) {
							size_t transfer_amount = std::min(excess, static_cast<size_t>(target_occupancy * carriages[j].GetMaxCapacity() / 100.0) - carriages[j].GetOccupiedSeats());
							carriages[i].IsDropOff(transfer_amount);
							carriages[i].IsBoarding(transfer_amount);
							excess -= transfer_amount;
						}
					}
				}
			}
		}

		for(size_t i = 0; i < size; i++) { 
			if(carriages[i].GetTypeOfCarriage() == type && carriages[i].GetOccupiedSeats() == 0) { 
				DeleteCarriage(i);
				i--;
			}
		}
	}
}


void Train::PlaceRestaurantOptimally() {
	size_t restaurantIndex = size;
	double bestDifference = std::numeric_limits<double>::max();
	size_t bestPosition = 0;

	for(size_t i = 0; i < size; i++){
		if(carriages[i].GetTypeOfCarriage() == CarriageType::RESTAURANT) {
			restaurantIndex = i;
			break;
		}
	}

	Carriage restaurant(CarriageType::RESTAURANT);
	if(restaurantIndex < size) {
		restaurant = carriages[restaurantIndex];
		DeleteCarriage(restaurantIndex);
	}

	for(size_t i = 0; i <= size; i++){
		double beforeCount = 0, afterCount = 0;

		for(size_t j = 0; j < i; j++){
			if(carriages[j].GetTypeOfCarriage() != CarriageType::LUXURY) {
				beforeCount += carriages[j].GetPercent();
			}
		}
		for(size_t j = i; j < size; j++){
			if(carriages[j].GetTypeOfCarriage() != CarriageType::LUXURY) {
				afterCount += carriages[j].GetPercent();
			}
		}

		double difference = std::abs(beforeCount - afterCount);
		if(difference < bestDifference) {
			bestDifference = difference;
			bestPosition = i;
		}
	}

	if(size == capacity) {
		Resize(capacity * 2);
	}

	for(size_t i = size; i > bestPosition; i--){
		carriages[i] = std::move(carriages[i-1]);
	}

	carriages[bestPosition] = std::move(restaurant);
	size++;
}

