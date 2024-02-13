import React, { useState, useEffect } from 'react';
import io from 'socket.io-client';

import './App.css';
import LoginForm from './components/LoginForm';
import ChatBox from './components/ChatBox';

const socket = io('http://localhost:3001'); // Adjust for your backend port

function App() {
  const [isLoggedIn, setIsLoggedIn] = useState(false);
  // ...other state variables for messages, etc.

  useEffect(() => {
    // Example - listen for a 'connect' event from the backend
    socket.on('connect', () => {
      console.log('Connected to chat server!');
    });
  }, []);

  return (
      <div className="App">
        {isLoggedIn ? (
            <ChatBox socket={socket} /* ...other props */ />
        ) : (
            <LoginForm onLogin={() => setIsLoggedIn(true)} />
        )}
      </div>
  );
}

export default App;
