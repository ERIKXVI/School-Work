import React, { useState } from 'react';

function SearchBar({ onSearch }) {
    const [city, setCity] = useState('');

    const handleSubmit = (event) => {
        event.preventDefault();
        onSearch(city);
        setCity(''); // Clear the search bar
    }

    return (
        <form onSubmit={handleSubmit}>
            <input 
                type="text" 
                value={city}
                onChange={(e) => setCity(e.target.value)}
                placeholder="Enter a city" 
            />
            <button type="submit">Search</button>
        </form>
    );
}

export default SearchBar;
