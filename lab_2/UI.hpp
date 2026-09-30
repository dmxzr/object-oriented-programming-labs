#ifndef _UI_HPP_
#define _UI_HPP_

#include "lib/train.hpp"
#include "lib/carriage.hpp"

void display_menu();
CarriageType select_carriage_type();
void handle_menu_choice(int choice, Train& train);


#endif
