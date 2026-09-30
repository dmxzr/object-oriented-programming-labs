#pragma once
#include "Agency.hpp"


/**
 * @class TestAgency
 * @brief Класс для тестирования агентств.
 *
 * Класс TestAgency наследует класс Agency и используется для тестирования
 * функциональности базового класса и производных классов.
 */
class TestAgency : public Agency {
public:
    /**
     * @brief Конструктор класса TestAgency.
     * @param name Название агентства.
     * @param profile Профиль деятельности агентства.
     * @param license_number Номер лицензии агентства.
     * @param location Местоположение агентства.
     */
    TestAgency(const std::string& name, const std::string& profile,
               const std::string& license_number, const std::string& location)
        : Agency(name, profile, license_number, location) {}

    /**
     * @brief Возвращает тип агентства.
     * @return Тип агентства в виде строки.
     */
    std::string get_type() const override {
        return "TestAgency";
    }
};
