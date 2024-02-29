import React from 'react';

function WeatherDisplay({ data }) {
    const formatTime = (timestamp) => {
        return new Date(timestamp * 1000).toLocaleTimeString();
    }

    return (
        <div className="weather-card">
            {data && (
                <div>
                    <h2>{data.current.name}, {data.current.sys.country}</h2>

                    {/* Current Weather */}
                    <div className="current-weather">
                        <p>Temperature: {data.current.temp} °C</p>
                        <p>Feels like: {data.current.feels_like} °C</p>
                        <p>Description: {data.current.weather[0].description}</p>
                        <p>Wind Speed: {data.windSpeed} m/s</p>
                        <p>Humidity: {data.humidity}%</p>
                    </div>

                    {/* Hourly Forecast */}
                    <div className="hourly-forecast">
                        <h2>Hourly Forecast</h2>
                        {data.hourly.map((hour) => (
                            <div key={hour.dt}>
                                <p>{formatTime(hour.dt)}</p>
                                <p>Temperature: {hour.temp} °C</p>
                            </div>
                        ))}
                    </div>

                    {/* Daily Forecast */}
                    <div className="daily-forecast">
                        <h2>Daily Forecast</h2>
                        {data.daily.map((day) => (
                            <div key={day.date}> {/* Using date as key */}
                                <p>{day.date}</p>
                                <p>Description: {day.description}</p>
                                <p>Temp: {day.temp.min} °C / {day.temp.max} °C</p>
                            </div>
                        ))}
                    </div>
                </div>
            )}
        </div>
    );
}

export default WeatherDisplay;
