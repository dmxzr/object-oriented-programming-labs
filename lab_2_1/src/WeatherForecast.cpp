#include "../lib/WeatherForecast.hpp"
#include <algorithm>
#include <limits>
#include <ctime>


WeatherForecast::WeatherForecast(const std::vector<DailyForecast>& forecasts):
	forecasts(forecasts) {}

WeatherForecast::WeatherForecast(const DailyForecast& forecast) {
	forecasts.push_back(forecast);
}


void WeatherForecast::AddForecast(const DailyForecast& forecast) {
	forecasts.push_back(forecast);
}

void WeatherForecast::DeleteForecast(size_t index) {
	if(index >= forecasts.size()) throw std::out_of_range("Индекс вышел за пределы");
	forecasts.erase(forecasts.begin() + index);
}


void WeatherForecast::DeleteAllIncorrectForecasts() {
	auto lambda = [](const DailyForecast& f){ return f.IsCorrect();};
	auto iter = std::remove_if(forecasts.begin(), forecasts.end(), lambda);
	forecasts.erase(iter, forecasts.end());
}

void WeatherForecast::SortDailyForecastsByDate() {
	auto lambda = [](const DailyForecast& a, const DailyForecast& b){
		return a.GetDate() < b.GetDate();
	};
	std::sort(forecasts.begin(), forecasts.end(), lambda);
}



WeatherForecast& WeatherForecast::operator+=(const DailyForecast& forecast) {
	forecasts.push_back(forecast);
	return *this;
}

const DailyForecast& WeatherForecast::operator[](size_t index) const	{
	if(index >= forecasts.size()) throw std::out_of_range("Индекс вышел за пределы");
	return forecasts[index];
}


/*
WeatherForecast WeatherForecast::operator+(const WeatherForecast& other) const {
	WeatherForecast = 
}


WeatherForecast WeatherForecast::operator-() const{
	
}
*/


WeatherForecast& WeatherForecast::operator-=(const DailyForecast& forecast) {
	auto iter = std::find(forecasts.begin(), forecasts.end(), forecast);
	if(iter == forecasts.end()) throw std::out_of_range("Индекс вышел за пределы");
	forecasts.erase(iter);
	return *this;
}


const DailyForecast& WeatherForecast::operator()(time_t date) const {
	auto lambda = [date](const DailyForecast& f){return f.GetDate() == date;};
	auto iter = std::find_if(forecasts.begin(), forecasts.end(), lambda);
	if(iter == forecasts.end()) throw std::out_of_range("Прогноз на указанную дату не найден");
	return *iter;
}



DailyForecast WeatherForecast::FindColdestDay(time_t start_date, time_t end_date) const {
	if(forecasts.empty()) throw std::runtime_error("Нет доступных прогнозов");


	DailyForecast coldest_day = forecasts[0];
	double min_avg_temp = std::numeric_limits<double>::max();

	for(size_t i = 0; i < forecasts.size(); i++){
		const DailyForecast& forecast = forecasts[i];
		time_t forecast_date = forecast.GetDate();
		if(forecast_date >= start_date && forecast_date <= end_date) {
			double avg_temp = forecast.GetAverageDailyTemp();
			if(avg_temp < min_avg_temp) {
				min_avg_temp = avg_temp;
				coldest_day = forecast;	
			}
		}
	}
}


DailyForecast WeatherForecast::FindeNearestSunnyDay(time_t date) const {
	if(forecasts.empty()) throw std::runtime_error("Нет доступных прогнозов");

	DailyForecast nearest_sunny_day;
	bool found = false;
	time_t min_diff = std::numeric_limits<time_t>::max();

	for(size_t i = 0; i < forecasts.size(); i++) {
		const DailyForecast& forecast = forecasts[i];
		if(forecast.GetWeatherTypeName() == "SUNNY") {
			time_t diff = std::abs(forecast.GetDate() - date);
			if(diff < min_diff) {
				min_diff = diff;
				nearest_sunny_day = forecast;
				found = true;
			}	
		}
	}

	if(!found) throw std::runtime_error("Нет солненых дней");
	return nearest_sunny_day;
}


std::vector<DailyForecast> WeatherForecast::GetMonthlyForecasts(int year, Month month) const {
	if(year > 1900 || year > 2100) throw std::invalid_argument("Неверный год");


	std::vector<DailyForecast> monthly_forecasts;
	int target_month = static_cast<int>(month);
		
	for(size_t i = 0; i < forecasts.size(); i++){
		const DailyForecast& forecast = forecasts[i];

		std::time_t forecast_time = forecast.GetDate();
		std::tm* date_structure = std::localtime(&forecast_time);

		const int YEAR_OFFSET = 1900;
		const int MONTH_OFFSET = 1;

		int forecast_year = date_structure -> tm_year + YEAR_OFFSET;
		int forecast_month = date_structure -> tm_mon + MONTH_OFFSET;

		bool is_correct_year = (forecast_year == year);
		bool is_correct_month = (forecast_month == target_month);

		if(is_correct_year && is_correct_month) monthly_forecasts.push_back(forecast);

	}
	auto lambda = [](const DailyForecast& a, const DailyForecast& b) {return a.GetDate() < b.GetDate();};
	std::sort(monthly_forecasts.begin(), monthly_forecasts.end(), lambda);

	return monthly_forecasts;
	
}


///// merge duplicate, 

