#pragma once
#include "includes.hpp"
#include "Agency.hpp"

/**
 * @class TVCompany
 * @brief Класс для представления телевизионной компании.
 *
 * Класс TVCompany наследует класс Agency и добавляет специфические атрибуты
 * и методы для телевизионных компаний, такие как канал вещания.
 */
class TVCompany: public Agency {
private:
    std::string channel; ///< Канал вещания.

public:
    /**
     * @brief Конструктор класса TVCompany.
     * @param name Название телевизионной компании.
     * @param profile Профиль деятельности телевизионной компании.
     * @param license_number Номер лицензии телевизионной компании.
     * @param location Местоположение телевизионной компании.
     * @param channel Канал вещания.
     */
    TVCompany(const std::string& name, const std::string& profile,
              const std::string& license_number, const std::string& location,
              const std::string& channel):
        Agency(name, profile, license_number, location),
        channel(channel) {}
    /**
     * @brief Деструктор класса TVCompany.
     */
    ~TVCompany() override = default;

    /**
     * @brief Возвращает тип агентства.
     * @return Тип агентства в виде строки.
     */
    std::string get_type() const override { return "TVCompany"; }
    /**
     * @brief Возвращает канал вещания.
     * @return Канал вещания.
     */
    std::string get_channel() const { return channel; }
    /**
     * @brief Устанавливает новый канал вещания.
     * @param new_channel Новый канал вещания.
     */
    void set_channel(const std::string& new_channel) { channel = new_channel; }
};
