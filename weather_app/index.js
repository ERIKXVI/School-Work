const express = require('express');
const axios = require('axios');
require('dotenv').config();

const app = express();
const port = process.env.PORT || 3001;
const API_KEY = process.env.OPENWEATHERMAP_API_KEY;
const cors = require('cors');

app.use(cors());

app.get('/weather', async (req, res) => {
    const city = req.query.city;

    try {
        // Fetch lat/lon coordinates
        const geocodingResponse = await axios.get(`https://api.openweathermap.org/geo/1.0/direct?q=${city}&limit=1&appid=${API_KEY}`);
        const lat = geocodingResponse.data[0].lat;
        const lon = geocodingResponse.data[0].lon;

        // Get current weather
        const currentWeatherResponse = await axios.get(`https://api.openweathermap.org/data/2.5/weather?lat=${lat}&lon=${lon}&units=metric&appid=${API_KEY}`);

        // Get forecast
        const forecastResponse = await axios.get(`https://api.openweathermap.org/data/2.5/onecall?lat=${lat}&lon=${lon}&exclude=current,minutely,alerts&units=metric&appid=${API_KEY}`);

        const hourlyForecast = forecastResponse.data.hourly.slice(0, 12);
        const dailyForecast = processDailyForecast(forecastResponse.data.daily);

        res.json({
            current: currentWeatherResponse.data,
            hourly: hourlyForecast,
            daily: dailyForecast
        });

    } catch (error) {
        console.error("Error fetching weather data:", error);
        res.status(500).json({ error: 'Error fetching weather data' });
    }
});

// Helper function to format daily forecast
function processDailyForecast(dailyData) {
    return dailyData.map((day) => {
        return {
            date: new Date(day.dt * 1000).toLocaleDateString(),
            temp: {
                day: day.temp.day,
                min: day.temp.min,
                max: day.temp.max
            },
            description: day.weather[0].description,
            icon: day.weather[0].icon
        };
    });
}

app.listen(port, () => {
    console.log(`Weather backend server listening on port ${port}`);
});
