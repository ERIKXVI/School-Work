import React, { useState } from 'react';
import axios from 'axios';
import SearchBar from './SearchBar';
import WeatherDisplay from './WeatherDisplay';

function App() {
    const [weatherData, setWeatherData] = useState(null);
    const [error, setError] = useState(null);

    const handleSearch = async (city) => {
        try {
            const weatherResponse = await axios.get(`http://localhost:3001/weather?city=${city}`);
            setWeatherData(weatherResponse.data);
            setError(null);
        } catch (error) {
            setWeatherData(null);
            setError(error.message);
        }
    };

    return (
        <div className="app-container">
            <h1>Weather App</h1>
            <SearchBar onSearch={handleSearch} />
            {error && <p>Error: {error}</p>}
            {weatherData && <WeatherDisplay data={weatherData} />}
        </div>
    );
}

export default App;
