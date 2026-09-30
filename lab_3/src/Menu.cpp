#include "../lib/Menu.hpp"

void Menu::display_menu() const {
    std::cout << "\nMedia Agency Management System\n";
    std::cout << "1. Register new agency\n";
    std::cout << "2. Modify agency information\n";
    std::cout << "3. Display agencies by type\n";
    std::cout << "4. Revoke agency license\n";
    std::cout << "5. Display agencies by region\n";
    std::cout << "6. Display all agencies\n";
    std::cout << "7. Exit\n";
    std::cout << "Enter your choice: ";
}

Agency* Menu::create_agency() const {
    std::string name, profile, license_number, location;
    
    std::cout << "Enter agency name: ";
    std::getline(std::cin, name);
    std::cout << "Enter agency profile: ";
    std::getline(std::cin, profile);
    std::cout << "Enter license number: ";
    std::getline(std::cin, license_number);
    std::cout << "Enter location: ";
    std::getline(std::cin, location);
    
    std::cout << "Select agency type:\n";
    std::cout << "1. Publishing Media\n";
    std::cout << "2. Radio Station\n";
    std::cout << "3. TV Company\n";
    std::cout << "Enter choice: ";
    
    int type;
    std::cin >> type;
    std::cin.ignore();
    
    switch(type) {
        case 1: {
            std::vector<std::string> period;
            std::string day;
            std::cout << "Enter publication days (enter 'done' when finished):\n";
            while(true) {
                std::getline(std::cin, day);
                if(day == "done") break;
                period.push_back(day);
            }
            
            int circulation;
            std::cout << "Enter circulation: ";
            std::cin >> circulation;
            std::cin.ignore();
            
            return new PublishingMedia(name, profile, license_number, location, period, circulation);
        }
        case 2: {
            std::vector<Frequency> frequencies;
            std::string band, freq;
            std::cout << "Enter frequencies (enter 'done' for band when finished):\n";
            while(true) {
                std::cout << "Enter band: ";
                std::getline(std::cin, band);
                if(band == "done") break;
                std::cout << "Enter frequency: ";
                std::getline(std::cin, freq);
                frequencies.emplace_back(band, freq);
            }
            
            return new RadioStation(name, profile, license_number, location, frequencies);
        }
        case 3: {
            std::string channel;
            std::cout << "Enter channel: ";
            std::getline(std::cin, channel);
            
            return new TVCompany(name, profile, license_number, location, channel);
        }
        default:
            std::cout << "Invalid agency type.\n";
            return nullptr;
    }
}


void Menu::register_new_agency() {
    Agency* new_agency = create_agency();
    if (new_agency) {
        if (agencies.add(new_agency)) {
            std::cout << "New agency registered successfully.\n";
        } else {
            std::cout << "Failed to register agency.\n";
        }
    } else {
        std::cout << "Failed to create agency.\n";
    }
}

    
    


void Menu::display_agencies_by_type() const {
    int type;
    std::cout << "Select agency type:\n";
    std::cout << "1. Publishing Media\n";
    std::cout << "2. Radio Station\n";
    std::cout << "3. TV Company\n";
    std::cout << "Enter choice: ";
    std::cin >> type;
    
    std::string type_str;
    switch(type) {
        case 1:
            type_str = "PublishingMedia";
            break;
        case 2:
            type_str = "RadioStation";
            break;
        case 3:
            type_str = "TVCompany";
            break;
        default:
            std::cout << "Invalid type\n";
            return;
    }
    
    std::cout << "\nAgencies of type " << type_str << ":\n";
    for(size_t i = 0; i < agencies.get_capacity(); i++) {
        const auto& table = agencies.get_table();
        if(table[i].occupied && table[i].agency &&
           table[i].agency->get_type() == type_str) {
            std::cout << "\n-------------------------\n";
            if(type == 1) {
                auto* pm = dynamic_cast<PublishingMedia*>(table[i].agency);
                pm->display_info();
                std::cout << "Publication days: ";
                for(const auto& day : pm->get_period()) {
                    std::cout << day << " ";
                }
                std::cout << "\nCirculation: " << pm->get_circulation() << "\n";
            }
            else if(type == 2) {
                auto* rs = dynamic_cast<RadioStation*>(table[i].agency);
                rs->display_info();
                std::cout << "Frequencies:\n";
                for(const auto& freq : rs->get_frequencies()) {
                    std::cout << "Band: " << freq.band
                             << ", Frequency: " << freq.frequency << "\n";
                }
            }
            else if(type == 3) {
                auto* tv = dynamic_cast<TVCompany*>(table[i].agency);
                tv->display_info();
                std::cout << "Channel: " << tv->get_channel() << "\n";
            }
        }
    }
}

void Menu::revoke_license() {
    std::string name;
    std::cout << "Enter agency name: ";
    std::getline(std::cin, name);
    if(agencies.remove(name.c_str())) {
        std::cout << "License revoked successfully!\n";
    } else {
        std::cout << "Agency not found.\n";
    }
}

std::vector<Agency*> Menu::get_all_agencies() const {
    std::vector<Agency*> all_agencies;
    const auto& table = agencies.get_table();
    for(size_t i = 0; i < agencies.get_capacity(); i++) {
        if(table[i].occupied && table[i].agency) {
            all_agencies.push_back(table[i].agency);
        }
    }
    return all_agencies;
}

void Menu::display_agencies_by_region() const {
    auto all_agencies = get_all_agencies();
    RegionIterator iterator(all_agencies);

    std::cout << "\nAgencies by region:\n";
    std::cout << "-------------------------\n";

    std::vector<std::thread> threads;
    while (iterator.hasNext()) {
        auto pair = iterator.next();
        std::string location = pair.first;
        int count = pair.second;

        threads.emplace_back([this, location, count, &all_agencies]() {
            std::vector<Agency*> agencies_in_region;
            for (const auto& agency : all_agencies) {
                if (agency->get_location() == location) {
                    agencies_in_region.push_back(agency);
                }
            }

            std::lock_guard<std::mutex> lock(output_mutex);
            std::cout << location << ": " << count << " agencies\n";
            for (const auto& agency : agencies_in_region) {
                std::cout << "\n  " << agency->get_name() << " ("
                          << agency->get_type() << ")\n";
                std::cout << "  Profile: " << agency->get_profile() << "\n";
                std::cout << "  License: " << agency->get_license_number() << "\n";
            }
            std::cout << "-------------------------\n";
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }
}
void Menu::display_all_agencies() const {
    const auto& table = agencies.get_table();
    bool found = false;
    
    std::cout << "\nAll registered agencies:\n";
    for(size_t i = 0; i < agencies.get_capacity(); i++) {
        if(table[i].occupied && table[i].agency) {
            found = true;
            std::cout << "\n-------------------------\n";
            Agency* agency = table[i].agency;
            
            if(auto* pm = dynamic_cast<PublishingMedia*>(agency)) {
                std::cout << "Type: Publishing Media\n";
                pm->display_info();
                std::cout << "Publication days: ";
                for(const auto& day : pm->get_period()) {
                    std::cout << day << " ";
                }
                std::cout << "\nCirculation: " << pm->get_circulation() << "\n";
            }
            else if(auto* rs = dynamic_cast<RadioStation*>(agency)) {
                std::cout << "Type: Radio Station\n";
                rs->display_info();
                std::cout << "Frequencies:\n";
                for(const auto& freq : rs->get_frequencies()) {
                    std::cout << "Band: " << freq.band
                             << ", Frequency: " << freq.frequency << "\n";
                }
            }
            else if(auto* tv = dynamic_cast<TVCompany*>(agency)) {
                std::cout << "Type: TV Company\n";
                tv->display_info();
                std::cout << "Channel: " << tv->get_channel() << "\n";
            }
        }
    }
    
    if(!found) {
        std::cout << "No agencies registered yet.\n";
    }
}


void Menu::modify_agency_info() {
    std::string name;
    std::cout << "Enter the name of the agency you want to modify: ";
    std::getline(std::cin, name);

    Agency* agency = agencies.find(name.c_str());
    
    if (agency) {
        std::cout << "Agency found: " << agency->get_name() << "\n";
        std::cout << "1. Modify profile\n";
        std::cout << "2. Modify location\n";
        std::cout << "3. Modify license number\n";
        int choice;
        std::cout << "Choose an option: ";
        std::cin >> choice;
        std::cin.ignore();

        switch(choice) {
            case 1:
                {
                    std::string new_profile;
                    std::cout << "Enter new profile: ";
                    std::getline(std::cin, new_profile);
                    agency->set_profile(new_profile);
                    std::cout << "Profile updated successfully.\n";
                    break;
                }
            case 2:
                {
                    std::string new_location;
                    std::cout << "Enter new location: ";
                    std::getline(std::cin, new_location);
                    agency->set_location(new_location);
                    std::cout << "Location updated successfully.\n";
                    break;
                }
            case 3:
                {
                    std::string new_license;
                    std::cout << "Enter new license number: ";
                    std::getline(std::cin, new_license);
                    agency->set_license_number(new_license);
                    std::cout << "License number updated successfully.\n";
                    break;
                }
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    } else {
        std::cout << "Agency not found.\n";
    }
}


void Menu::run() {
    int choice;
    while(true) {
        display_menu();
        std::cin >> choice;
        std::cin.ignore();
        
        switch(choice) {
            case 1:
                register_new_agency();
                break;
            case 2:
                modify_agency_info();
                break;
            case 3:
                display_agencies_by_type();
                break;
            case 4:
                revoke_license();
                break;
            case 5:
                display_agencies_by_region();
                break;
            case 6:
                display_all_agencies();
                break;
            case 7:
                std::cout << "Exiting program.\n";
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}
