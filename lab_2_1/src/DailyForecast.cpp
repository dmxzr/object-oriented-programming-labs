#include "../lib/DailyForecast.hpp"




DailyForecast::DailyForecast(time_t date, double morning_temp, double day_temp,
                           double evening_temp, const WeatherType weather, 
                           double precipitation): 
                           date(date), morning_temp(morning_temp), 
                           day_temp(day_temp), evening_temp(evening_temp),
                           weather(weather), precipitation(precipitation)
                            {
                            	ValidateTemp();
                            };

DailyForecast::DailyForecast(time_t date, double temp, double precipitation):
							date(date), morning_temp(temp),
							day_temp(temp), evening_temp(temp),
							precipitation(precipitation) {
								ValidateTemp();
								AutoWeatherType();
							};


void DailyForecast::ValidateTemp() const {
	if(morning_temp < -273 || day_temp < -273 || evening_temp < -273) 
		throw std::invalid_argument("Температура не может быть ниже -273°C");
}


bool DailyForecast::IsCorrect() const {
	if((weather == WeatherType::SUN || weather == WeatherType::CLOUD)
	 	&& precipitation != 0)  return false;

	if(weather == WeatherType::SNOW &&
		std::max(morning_temp, std::max(day_temp, evening_temp)) > 0)
			return false;

	if(morning_temp < -100 || morning_temp > 60 ||
		day_temp < - 100 || day_temp > 60 ||
		evening_temp < - 100 || day_temp > 60)
			return false;

	if(precipitation > 1500 || precipitation < 0) return false;

	return true;
}


void DailyForecast::AutoWeatherType() {
	if(precipitation == 0) 
		if(day_temp > 20 ) weather = WeatherType::SUN;
		else weather = WeatherType::CLOUD;
		
	else {
		double min_temp = std::min(morning_temp, std::min(day_temp, evening_temp));
		if(min_temp <= 0) weather = WeatherType::SNOW;
		else weather = WeatherType::RAIN;
	}
}



DailyForecast& DailyForecast::operator+=(const DailyForecast& other) {
	if(date != other.date)
		throw std::invalid_argument("Объединять погоду можно только за одни и те же сутки");

	morning_temp = (morning_temp + other.morning_temp)/2;
	day_temp = (day_temp + other.day_temp)/2;
	evening_temp = (evening_temp + other.evening_temp)/2;
	precipitation = (precipitation + other.precipitation)/2;
	weather	= GetWorstWeather(weather, other.weather);

	return *this;
}


auto DailyForecast::operator<=>(const DailyForecast& other) const {
	return date <=> other.date;
}


double DailyForecast::GetAverageDailyTemp() const {
	return (morning_temp + day_temp + evening_temp)/3.0;
}


time_t DailyForecast::GetDate() const {
	return date;
}

double DailyForecast::GetMorningTemp() const {
	return morning_temp;
} 

double DailyForecast::GetDayTemp() const {
	return day_temp;
}


double DailyForecast::GetEveningTemp() const {
	return evening_temp;
}


WeatherType DailyForecast::GetWeatherType() const{
	return weather;
}

std::string DailyForecast::GetWeatherTypeName() const {
	switch (weather) {
		case WeatherType::SUN:
			return "Солнечно";
		case WeatherType::CLOUD:
			return "Облачно";
		case WeatherType::RAIN:
			return "Дождь";
		case WeatherType::SNOW:
			return "Снег";
	default:
		return "Неизвестно";
	}
}


double DailyForecast::GetPrecipitation() const {
	return precipitation;
}




void DailyForecast::SetDate(time_t new_date) {
	date = new_date;
}

void DailyForecast::SetMorningTemp(double temp) { 
	double old_temp = morning_temp;
	morning_temp = temp;
	try {
		ValidateTemp();
	} catch (const std::invalid_argument& e) {
		morning_temp = old_temp;
		throw;
	}
}


void DailyForecast::SetDayTemp(double temp) { 
	double old_temp = day_temp;
	day_temp = temp;
	try {
		ValidateTemp();
	} catch (const std::invalid_argument& e) {
		day_temp = old_temp;
		throw;
	}
}


void DailyForecast::SetEveningTemp(double temp) { 
	double old_temp = evening_temp;
	evening_temp = temp;
	try {
		ValidateTemp();
	} catch (const std::invalid_argument& e) {
		evening_temp = old_temp;
		throw;
	}
}


void DailyForecast::SetTemp(double morning, double day, double evening) {
	double old_morning = morning_temp;
	double old_day = day_temp; 
	double old_evening = evening_temp;

	morning_temp = morning;
	day_temp = day;
	evening_temp = evening;

	try {
		ValidateTemp();
	} catch (const std::invalid_argument& e) {
		morning_temp = old_morning;
		day_temp = old_day;
		evening_temp = old_evening;
		throw;
		}
}



void DailyForecast::SetWeatherType(WeatherType new_weather) {
	WeatherType old_weather = weather;
	weather = new_weather;

	if(!IsCorrect()) {
		weather = old_weather;
		throw std::invalid_argument("Некорректный тип погоды для текущих параметров");
	}
	
}



void DailyForecast::SetPrecipitation(double new_precipitation){
	double old_precipitation = precipitation;
	precipitation = new_precipitation;

	if(!IsCorrect()) {
		precipitation = old_precipitation;
		throw std::invalid_argument("Некорректный тип погоды для текущих параметров");
	}

	AutoWeatherType();
}




WeatherType DailyForecast::GetWorstWeather(const WeatherType weather_1, const WeatherType weather_2) {
		if(weather_1 == WeatherType::SNOW || weather_2 == WeatherType::SNOW)
			return WeatherType::SNOW;
		if(weather_1 == WeatherType::RAIN || weather_2 == WeatherType::RAIN)
			return WeatherType::RAIN;
		if(weather_1 == WeatherType::CLOUD || weather_2 == WeatherType::CLOUD)
			return WeatherType::CLOUD;
		return WeatherType::SUN;
	}
