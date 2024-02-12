const express = require('express');
const axios = require('axios');
require('dotenv').config();

const app = express();
const port = process.env.PORT || 3001;

const API_KEY = process.env.OPENWEATHERMAP_API_KEY;

// Enable CORS 
const cors = require('cors');
app.use(cors());

app.get('/weather', async (req, res) => {
    const city = req.query.city;

    try {
        const response = await axios.get(`https://api.openweathermap.org/data/2.5/weather?q=${city}&units=metric&appid=${API_KEY}`);
        res.json(response.data);
    } catch (error) {
        console.error("Error fetching weather:", error); // Log the error to your console 
        res.status(500).json({ error: 'Error fetching weather data' });
    }
});

app.listen(port, () => {
    console.log(`Weather backend server listening on port ${port}`);
});
