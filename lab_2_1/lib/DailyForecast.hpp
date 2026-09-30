#ifndef _DAILY_FORECAST_HPP_
#define _DAILY_FORECAST_HPP_

#include <compare>
#include <iostream>
#include <time.h>


enum class WeatherType {
	SUN,	///< Солнечно.
	CLOUD,///< Облачно.
	RAIN,	///< Дождь.
	SNOW	///< Снег.
};


class DailyForecast {
private:
	time_t date; ///< Дата.
	double morning_temp;	///< Температура утром.
	double day_temp;		///< Температура днем.
	double evening_temp;	///< Температура вечером.
	static WeatherType weather;	///< Погодное явление.
	double precipitation;	///< Количество осадков.


	void ValidateTemp() const;
	void AutoWeatherType();
	WeatherType GetWorstWeather(const WeatherType weather_1, const WeatherType weather_2);
	
	
public:
	DailyForecast();

	DailyForecast(time_t date, double morning_temp, double day_temp,
		double evening_temp, WeatherType weather, double precipitation);

	DailyForecast(time_t date, double temp, double precipitation);	


	time_t GetDate() const;
	double GetMorningTemp() const; 
	double GetDayTemp() const;
	double GetEveningTemp() const;
	static WeatherType GetWeatherType();
	std::string GetWeatherTypeName() const;
	double GetPrecipitation() const;

	double GetAverageDailyTemp() const;
	bool IsCorrect() const;

	void SetDate(time_t date);
	void SetMorningTemp(double temp); 
	void SetDayTemp(double temp);
	void SetEveningTemp(double temp);
	void SetTemp(double morning_temp, double day_temp, double evening_temp);
	void SetWeatherType(WeatherType weather);
	void SetPrecipitation(double precipitation);

	

	DailyForecast& operator+=(const DailyForecast& other);
	auto operator<=>(const DailyForecast& other) const;

	
};






#endif /* _DAILY_FORECAST_HPP_ */
