#pragma once
#include "Agency.hpp"
#include "includes.hpp"
#include <map>
#include <vector>
#include <string>
#include <utility>

/**
 * @class RegionIterator
 * @brief Класс итератора для обхода регионов агентств.
 *
 * Класс RegionIterator позволяет итерировать по регионам, в которых находятся агентства,
 * и подсчитывать количество агентств в каждом регионе.
 */
class RegionIterator {
private:
    std::map<std::string, int> location_counts; ///< Карта для подсчета количества агентств в каждом регионе.
    std::map<std::string, int>::iterator current; ///< Итератор для текущего региона.

public:
    /**
     * @brief Конструктор класса RegionIterator.
     * @param agencies Вектор агентств для подсчета регионов.
     */
    RegionIterator(const std::vector<Agency*>& agencies) {
        for (const auto& agency : agencies) {
            location_counts[agency->get_location()]++;
        }
        current = location_counts.begin();
    }
    /**
     * @brief Проверяет, есть ли еще регионы для итерации.
     * @return true, если есть еще регионы, иначе false.
     */
    bool hasNext() const {
        return current != location_counts.end();
    }
    /**
     * @brief Возвращает следующий регион и количество агентств в нем.
     * @return Пара, содержащая название региона и количество агентств в нем.
     */
    std::pair<std::string, int> next() {
        auto result = *current;
        ++current;
        return result;
    }
};
