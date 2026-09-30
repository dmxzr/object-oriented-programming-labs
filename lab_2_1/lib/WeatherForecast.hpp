#ifndef _WEATER_FORECAST_HPP_
#define _WEATER_FORECAST_HPP_

#include <iostream>
#include "DailyForecast.hpp"
#include <vector>


enum class Month {
	January,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};


class WeatherForecast {
private:
	std::vector<DailyForecast> forecasts;

public:
	WeatherForecast() = default;
	WeatherForecast(const std::vector<DailyForecast>& forecasts); // +
	WeatherForecast(const DailyForecast& forecast); // +

//	size_t GetSize() const{ return forecasts.size();}; //+
//	const std::vector<DailyForecast>& GetForecasts() const{return forecasts;}; //+


	void AddForecast(const DailyForecast& forecast); // +
	void DeleteForecast(size_t index); // +
	DailyForecast FindColdestDay(time_t start_date, time_t end_date) const; // +
	DailyForecast FindeNearestSunnyDay(time_t date) const; // +
	void DeleteAllIncorrectForecasts(); // +
	void MergeDuplicateForetasts();
	void SortDailyForecastsByDate(); // +
	std::vector<DailyForecast> GetMonthlyForecasts(int year, Month month) const; // +
	

	WeatherForecast& operator+=(const DailyForecast& forecast); // +
 	const DailyForecast& operator[](size_t index) const; // +



	WeatherForecast operator+(const WeatherForecast& other) const;//бин - объединение прогонозов
	WeatherForecast operator-() const;//унарный - хз че
	WeatherForecast& operator-=(const DailyForecast& forecast);//+ модифицирующие присваивание - удаление
	const DailyForecast& operator()(time_t date) const; //+ получение прогноза по дате
	WeatherForecast& operator++(); //преф инкремент - хз че
	WeatherForecast operator++(int); //пост инкремент - хз че
	


	friend std::ostream& operator<<(std::ostream& os, const WeatherForecast& forecast);

};





#endif /* _WEATER_FORECAST_HPP_ */
