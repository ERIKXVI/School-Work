import React from 'react';

function WeatherDisplay({ data }) {
  return (
    <div className="weather-card">
      <h2>{data.name}, {data.sys.country}</h2> 
      <p>
        <img src={`http://openweathermap.org/img/wn/${data.weather[0].icon}@2x.png`} alt={data.weather[0].description} />
        {data.main.temp} °C 
      </p>
      <p>{data.weather[0].description}</p>
      <div className="details">
        <p>Feels like: {data.main.feels_like} °C</p>
        <p>Humidity: {data.main.humidity}%</p> 
        <p>Wind: {data.wind.speed} m/s</p> 
      </div>
    </div>
  );
}

export default WeatherDisplay;
