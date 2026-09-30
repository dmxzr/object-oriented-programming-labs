#pragma once
#include "includes.hpp"
#include "Agency.hpp"



/**
 * @class PublishingMedia
 * @brief Класс для представления издательского агентства.
 *
 * Класс PublishingMedia наследует класс Agency и добавляет специфические атрибуты
 * и методы для издательских агентств, такие как период издания и тираж.
 */
class PublishingMedia: public Agency {
private:
    std::vector<std::string> period; ///< Период издания.
    int circulation;    ///< Тираж.

public:
        /**
     * @brief Конструктор класса PublishingMedia.
     * @param name Название агентства.
     * @param profile Профиль деятельности агентства.
     * @param license_number Номер лицензии агентства.
     * @param location Местоположение агентства.
     * @param period Период издания.
     * @param circulation Тираж.
     */
    PublishingMedia(const std::string& name, const std::string& profile,
                   const std::string& license_number, const std::string& location,
                   const std::vector<std::string>& period, int circulation):
        Agency(name, profile, license_number, location),
        period(period), circulation(circulation) {}
     /**
     * @brief Деструктор класса PublishingMedia.
     */
    ~PublishingMedia() override = default;
    

    /**
     * @brief Возвращает тип агентства.
     * @return Тип агентства в виде строки.
     */
    std::string get_type() const override { return "PublishingMedia"; }
        /**
     * @brief Возвращает период издания.
     * @return Период издания.
     */
    std::vector<std::string> get_period() const { return period; }
    /**
     * @brief Возвращает тираж.
     * @return Тираж.
     */
    int get_circulation() const { return circulation; }
    /**
     * @brief Устанавливает новый период издания.
     * @param new_period Новый период издания.
     */
    void set_period(const std::vector<std::string>& new_period) { period = new_period; }
    /**
     * @brief Устанавливает новый тираж.
     * @param new_circulation Новый тираж.
     */
    void set_circulation(int new_circulation) { circulation = new_circulation; }
};
