#pragma once
#include "Agency.hpp"
#include "PublishingMedia.hpp"
#include "RadioStation.hpp"
#include "TVCompany.hpp"
#include "RegionIterator.hpp"
#include <mutex> // Подключение для использования std::mutex
#include <thread>
#include <vector>
#include <unordered_map>

/**
 * @struct TableEntry
 * @brief Структура для хранения записи в таблице агентств.
 */
struct TableEntry {
        char* name;
        Agency* agency;
        bool occupied;
        /**
     * @brief Конструктор по умолчанию.
     */
        TableEntry(): name(nullptr), agency(nullptr), occupied(false) {}
    };
/**
 * @class AgencyTable
 * @brief Класс для управления таблицей агентств.
 */
class AgencyTable {

private:
    
    
    TableEntry* table; ///< Указатель на массив записей таблицы.
    size_t size;    ///< Текущий размер таблицы.
    size_t capacity;    ///< Емкость таблицы.
    const double LOAD_FACTOR_THRESHOLD = 0.7;   ///< Пороговое значение коэффициента загрузки.
/**
     * @brief Хеш-функция для вычисления индекса по ключу.
     * @param key Ключ для вычисления индекса.
     * @return Индекс в таблице.
     */
    unsigned int hash_func(const char* key);

    /**
     * @brief Метод для изменения размера таблицы.
     */
    void resize();
    mutable std::mutex table_mutex; ///< Мьютекс для синхронизации доступа к таблице.
	mutable std::mutex region_count_mutex; ///< Мьютекс для синхронизации подсчета регионов.

public:
    /**
     * @brief Конструктор класса AgencyTable.
     * @param init_capacity Начальная емкость таблицы.
     */
    AgencyTable(size_t init_capacity = 10);
     /**
     * @brief Деструктор класса AgencyTable.
     */
    ~AgencyTable();
 /**
     * @brief Вставка агентства в таблицу.
     * @param name Имя агентства.
     * @param agency Указатель на агентство.
     */
    void insert(const char* name, Agency* agency);
/**
     * @brief Поиск агентства в таблице по имени.
     * @param name Имя агентства.
     * @return Указатель на найденное агентство или nullptr, если агентство не найдено.
     */
    Agency* search(const char* name);
   /**
     * @brief Удаление агентства из таблицы по имени.
     * @param name Имя агентства.
     * @return true, если агентство успешно удалено, иначе false.
     */
    bool remove(const char* name);
    /**
     * @brief Получение текущего размера таблицы.
     * @return Текущий размер таблицы.
     */
    size_t get_size() const { return size; }
    /**
     * @brief Получение емкости таблицы.
     * @return Емкость таблицы.
     */
    size_t get_capacity() const { return capacity; }
     /**
     * @brief Получение указателя на массив записей таблицы.
     * @return Указатель на массив записей таблицы.
     */
    const TableEntry* get_table() const { return table; }
    /**
     * @brief Добавление агентства в таблицу.
     * @param agency Указатель на агентство.
     * @return true, если агентство успешно добавлено, иначе false.
     */
    bool add(Agency* agency) {
        if (!agency) return false;
        insert(agency->get_name().c_str(), agency);
        return true;
    }
/**
     * @brief Поиск агентства в таблице по имени.
     * @param name Имя агентства.
     * @return Указатель на найденное агентство или nullptr, если агентство не найдено.
     */
    Agency* find(const char* name) {
        return search(name);
    }
/**
     * @brief Получение записи по индексу.
     * @param index Индекс записи.
     * @return Указатель на запись.
     */
	TableEntry* getEntry(size_t index); // Получить запись по индексу
/**
     * @brief Получение емкости таблицы.
     * @return Емкость таблицы.
     */
	size_t getCapacity() const;         // Получить емкость таблицы
    /**
     * @brief Подсчет количества агентств по регионам.
     * @return Map, содержащая количество агентств в каждом регионе.
     */
	std::unordered_map<std::string, int> countAgenciesByRegion() const;
/**
     * @brief Получение всех агентств в таблице.
     * @return Вектор всех агентств.
     */
	std::vector<Agency*> getAllAgencies() const;
};
