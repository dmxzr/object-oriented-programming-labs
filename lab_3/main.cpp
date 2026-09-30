#include "lib/Menu.hpp"
#include "lib/AgencyTable.hpp"

int main() {
    AgencyTable agencies(10);
    
    Menu menu(agencies);
    
    menu.run();
    
    return 0;
}
