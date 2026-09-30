#ifndef AGENCY_TABLE_ITERATOR_HPP
#define AGENCY_TABLE_ITERATOR_HPP

#include "AgencyTable.hpp"


/**
 * @class AgencyTableIterator
 * @brief Класс итератора для обхода таблицы агентств.
 */
class AgencyTableIterator {
private:
    AgencyTable& table; ///< Ссылка на таблицу агентств.
    size_t index;        ///< Текущий индекс итератора.

public:
    /**
     * @brief Конструктор класса AgencyTableIterator.
     * @param t Ссылка на таблицу агентств.
     */
    explicit AgencyTableIterator(AgencyTable& t) : table(t), index(0) {}

   /**
     * @brief Проверяет, есть ли еще элементы в таблице для итерации.
     * @return true, если есть еще элементы, иначе false.
     */
    bool hasNext() {
        while (index < table.getCapacity()) {
            TableEntry* entry = table.getEntry(index);
            if (entry && entry->occupied) {
                return true;
            }
            ++index;
        }
        return false;
    }
/**
     * @brief Возвращает следующий элемент в таблице.
     * @return Указатель на следующее агентство или nullptr, если элементов больше нет.
     */
    Agency* next() {
        if (hasNext()) {
            return table.getEntry(index++)->agency;
        }
        return nullptr;
    }
};

#endif // AGENCY_TABLE_ITERATOR_HPP
