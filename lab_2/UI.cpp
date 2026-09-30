#include "UI.hpp"
#include <limits>
#include <iostream>

void display_menu(){
	std::cout << "___TRAIN MANAGER SYSTEM___";

	std::cout << "1. Add Wagon\n";

	std::cout << "2. Remove Wagon\n";

	std::cout << "3. Board Passengers\n";

	std::cout << "4. Disembark Passengers\n";

	std::cout << "5. Redistribute Passengers\n";

	std::cout << "6. Optimize Wagons\n";

	std::cout << "7. Place Restaurant Wagon\n";

	std::cout << "8. Display Train\n";

	std::cout << "9. Exit\n";

	std::cout << "=====================================\n";

	std::cout << "Select an option: ";
}


CarriageType select_carriage_type(){
	std::cout << "Select Wagon Type:\n";

	std::cout << "1. Sedentary\n";

	std::cout << "2. Economy\n";

	std::cout << "3. Luxury\n";

	std::cout << "4. Restaurant\n";

	int choice;

	std::cin >> choice;

	return static_cast<CarriageType>(choice - 1);
}


void handle_menu_choice(int choice, Train& train) {
	switch(choice){
		case 1: // add wagon
		{
			CarriageType type = select_carriage_type();
			Carriage carriage(type);
			train+=carriage;
			std::cout << "Wagon added.\n";
			break;
}
		case 2: // remove wagon
		{
			std::cout << "Enter Wagon index to remove: ";
			int index;
			std::cin >> index;
			train.DeleteCarriage(index + 1);
			std::cout << "Wagon removed.\n";
			break;
}
		case 3:
		{
			std::cout << "Enter Number of Passengers: ";
			int passengers;
			std::cin >> passengers;
			CarriageType type = select_carriage_type();
			train.Boarding(passengers, type);
			std::cout << "Passengers boarded.\n";
			break;
		}
		case 4: //высадить но нет функции
		{
			std::cout << "Enter Wagon index: ";
			int index;
			std::cin >> index;
			std::cout << "Enter Number of Passenger to Disembark: ";
			int passengers; 
			std::cin >> passengers;
			train[index+1].IsDropOff(passengers);
			std::cout << "Passengers disembraked.\n";
			break;
		}

		case 5: // redistribute
		{
			train.Redistribute();
			std::cout << "Rassengers redistrebuted.\n";
			break;
		}

		case 6: //optimize
		{
			train.OptimizeCarriages();
			std::cout << "Wagon optimized.\n";
			break;
		}

		case 7: // restautant
		{
			train.PlaceRestaurantOptimally();
			std::cout << "Restaurant wagon placed.\n";
			break;
		}

		case 8: // print train
		{
			std::cout << train;
			break;
		}

		case 9:
		{
			std::cout << "Exiting..\n";
			return ;
		}

		default:
		{
			std::cout << "Invalid option\n";
			}
			
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


int main() {
	Train *train;
	int choice;
	train = new struct Train; 
	display_menu();
	while(cin >> choice){
		
		handle_menu_choice(choice, *train);
		display_menu();
	}
	delete[] train;
	return 0;
}
