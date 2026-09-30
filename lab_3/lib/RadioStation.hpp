#pragma once
#include "includes.hpp"
#include "Agency.hpp"


/**
 * @struct Frequency
 * @brief Структура для представления частоты радиостанции.
 */
struct Frequency {
    std::string band; ///< Диапазон частот (например, FM, AM).
    std::string frequency; ///< Частота (например, 101.5).
    /**
     * @brief Конструктор структуры Frequency.
     * @param band Диапазон частот.
     * @param frequency Частота.
     */
    Frequency(const std::string& band, const std::string& frequency):
        band(band), frequency(frequency) {}
};

/**
 * @class RadioStation
 * @brief Класс для представления радиостанции.
 *
 * Класс RadioStation наследует класс Agency и добавляет специфические атрибуты
 * и методы для радиостанций, такие как частоты вещания.
 */
class RadioStation: public Agency {
private:
    std::vector<Frequency> frequencies; ///< Вектор частот радиостанции.

public:
/**
     * @brief Конструктор класса RadioStation.
     * @param name Название радиостанции.
     * @param profile Профиль деятельности радиостанции.
     * @param license_number Номер лицензии радиостанции.
     * @param location Местоположение радиостанции.
     * @param frequencies Вектор частот радиостанции.
     */
    RadioStation(const std::string& name, const std::string& profile,
                const std::string& license_number, const std::string& location,
                const std::vector<Frequency>& frequencies):
        Agency(name, profile, license_number, location),
        frequencies(frequencies) {}
    /**
     * @brief Деструктор класса RadioStation.
     */
    ~RadioStation() override = default;

/**
     * @brief Возвращает тип агентства.
     * @return Тип агентства в виде строки.
     */
    std::string get_type() const override { return "RadioStation"; }
    /**
     * @brief Возвращает частоты радиостанции.
     * @return Вектор частот радиостанции.
     */
    std::vector<Frequency> get_frequencies() const { return frequencies; }
    /**
     * @brief Устанавливает новые частоты радиостанции.
     * @param new_frequencies Новый вектор частот радиостанции.
     */
    void set_frequencies(const std::vector<Frequency>& new_frequencies) { frequencies = new_frequencies; }
};
