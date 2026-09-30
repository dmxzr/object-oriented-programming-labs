#pragma once
#include "Agency.hpp"
#include "AgencyTable.hpp"
#include "RegionIterator.hpp"
#include "includes.hpp"

/**
 * @class Menu
 * @brief Класс для управления меню системы управления агентствами.
 *
 * Класс Menu предоставляет интерфейс для взаимодействия с пользователем,
 * позволяя регистрировать новые агентства, изменять информацию об агентствах,
 * отображать агентства по типу и региону, а также аннулировать лицензии агентств.
 */
class Menu {
private:
    AgencyTable& agencies; ///< Ссылка на таблицу агентств.
    
  
    mutable std::mutex output_mutex; ///< Мьютекс для синхронизации вывода.

public:
    /**
     * @brief Конструктор класса Menu.
     * @param agencies Ссылка на таблицу агентств.
     */
    Menu(AgencyTable& agencies): agencies(agencies) {}
 /**
     * @brief Отображает меню системы управления агентствами.
     */
    void display_menu() const;
    /**
     * @brief Создает новое агентство на основе ввода пользователя.
     * @return Указатель на созданное агентство или nullptr в случае ошибки.
     */
    Agency* create_agency() const;
    /**
     * @brief Регистрирует новое агентство в таблице агентств.
     */
    void register_new_agency();
    /**
     * @brief Изменяет информацию об агентстве на основе ввода пользователя.
     */
    void modify_agency_info();
    /**
     * @brief Отображает агентства по типу.
     */
    void display_agencies_by_type() const;
    /**
     * @brief Аннулирует лицензию агентства на основе ввода пользователя.
     */
    void revoke_license();
    /**
     * @brief Отображает агентства по региону.
     */
    void display_agencies_by_region() const;
    /**
     * @brief Отображает все зарегистрированные агентства.
     */
    void display_all_agencies() const;
    /**
     * @brief Возвращает вектор всех зарегистрированных агентств.
     * @return Вектор всех агентств.
     */
    std::vector<Agency*> get_all_agencies() const;
    /**
     * @brief Запускает меню системы управления агентствами.
     */
    void run();
    
};
