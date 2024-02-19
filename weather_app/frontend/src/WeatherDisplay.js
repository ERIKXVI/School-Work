import React from 'react';

function WeatherDisplay({ data }) {
    const formatTime = (timestamp) => {
        return new Date(timestamp * 1000).toLocaleTimeString();
    }

    return (
        <div className="weather-card">
            {data.current && ( // Display current weather section
                <>
                    <h2>{data.current.name}, {data.current.sys.country}</h2>
                    {/* ... (Render other current weather details as before) */}
                </>
            )}

            {data.hourly && ( // Display hourly forecast section
                <div className="hourly-forecast">
                    <h2>Hourly Forecast</h2>
                    {data.hourly.map((hour) => (
                        <div key={hour.dt}>
                            <p>{formatTime(hour.dt)}</p>
                            {/* ... (Render hourly details) */}
                        </div>
                    ))}
                </div>
            )}

            {data.daily && ( // Display daily forecast section
                <div className="daily-forecast">
                    <h2>Daily Forecast</h2>
                    {data.daily.map((day) => (
                        <div key={day.dt}>
                            <p>{new Date(day.dt * 1000).toLocaleDateString()}</p>
                            {/* ... (Render daily details) */}
                        </div>
                    ))}
                </div>
            )}
        </div>
    );
}

export default WeatherDisplay;
