import React, { useState, useEffect } from 'react';
import axios from 'axios';
import SearchBar from './SearchBar';
import WeatherDisplay from './WeatherDisplay';

function App() {
    const [weatherData, setWeatherData] = useState(null);
    const [error, setError] = useState(null);

   const handleSearch = async (city) => {
       try {
           const response = await axios.get(`http://localhost:3001/weather?city=${city}`);
           setWeatherData(response.data);
           setError(null);
       } catch (error) {
           setWeatherData(null);
           if (error.response) {
               setError(`Error: ${error.response.status} - ${error.response.statusText}`); 
           } else if (error.request) {
                setError("Error: No response from server. Is it running?"); 
           } else {
               setError("Error: Network Error"); 
           }
       }
   }

    return (
        <div>
            <h1>Weather App</h1>
            <SearchBar onSearch={handleSearch} />
            {error && <p>Error: {error}</p>}
            {weatherData && <WeatherDisplay data={weatherData} />} 
        </div>
    );
}

export default App;
