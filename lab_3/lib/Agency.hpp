#pragma once
#include "includes.hpp"



/**
 * @brief Базовый класс для представления агентства.
 * 
 * Класс `Agency` содержит информацию об агентстве, такую как его название, профиль, номер лицензии и местоположение. 
 * Этот класс является абстрактным, так как имеет чисто виртуальный метод `get_type`.
 */
class Agency {
protected:
    std::string name;					///< Название агентства.
    std::string profile;				///< Профиль деятельности агентства.
    std::string license_number;			///< Номер лицензии агентства.
    std::string location;				///< Местоположение агентства.

public:
/**
	* @brief Конструктор класса Agency.
	* 
	* @param name Название агентства.
	* @param profile Профиль деятельности агентства.
	* @param license_number Номер лицензии агентства.
	* @param location Местоположение агентства.
	*/
    Agency(const std::string& name, const std::string& profile,
           const std::string& license_number, const std::string& location):
        name(name), profile(profile), license_number(license_number), location(location) {}

/**
	* @brief Виртуальный деструктор класса Agency.
	*/
    virtual ~Agency() = default;
/**
	* @brief Получить название агентства.
	* @return Название агентства.
	*/
    std::string get_name() const { return name; }

/**
	* @brief Получить профиль агентства.
	* @return Профиль агентства.
	*/
    std::string get_profile() const { return profile; }

/**
	* @brief Получить номер лицензии агентства.
	* @return Номер лицензии.
	*/
    std::string get_license_number() const { return license_number; }

/**
	* @brief Получить местоположение агентства.
	* @return Местоположение агентства.
	*/
    std::string get_location() const { return location; }


/**
	* @brief Установить новый профиль агентства.
	* @param new_profile Новый профиль агенства.
	*/
    void set_profile(const std::string& new_profile) { profile = new_profile; }


/**
	* @brief Установить новое местоположение агентства.
	* @param new_location Новое местоположение.
	*/
    void set_location(const std::string& new_location) { location = new_location; }


/**
	* @brief Установить новый номер лицензии агентства.
	* @param new_license Новый номер лицензии.
	*/
    void set_license_number(const std::string& new_license) { license_number = new_license; }


/**
	* @brief Получить тип агентства.
	* 
	* Чисто виртуальная функция, которая должна быть реализована в производных классах.
	* 
	* @return Тип агентства в виде строки.
	*/
    virtual std::string get_type() const = 0;


/**
	 * @brief Отобразить информацию об агентстве.
	* 
	* Выводит название, профиль, номер лицензии и местоположение агентства в консоль.
	*/
    virtual void display_info() const {
        std::cout << "Name: " << name << "\n";
        std::cout << "Profile: " << profile << "\n";
        std::cout << "License Number: " << license_number << "\n";
        std::cout << "Location: " << location << "\n";
    }
};

