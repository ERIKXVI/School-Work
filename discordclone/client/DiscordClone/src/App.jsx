import React, { useState, useEffect } from 'react';
import { invoke } from '@tauri-apps/api/tauri';
import { listen } from '@tauri-apps/api/event';
import './App.css'; // Import the CSS file

function App() {
  const [message, setMessage] = useState('');
  const [messages, setMessages] = useState([]);
  const [server, setServer] = useState('ws://127.0.0.1:3000/ws');
  const [isMenuOpen, setIsMenuOpen] = useState(false);
  const toggleMenu = () => {
    setIsMenuOpen(!isMenuOpen);
  };

  useEffect(() => {
    invoke('connect_to_server', {
      url: server,
    })
        .then(() => {
          console.log('Connected to server successfully');
        })
        .catch((error) => {
          console.error('Failed to connect to server:', error);
        });

    listen('message', (event) => {
      console.log('Received message:', event.payload);
      setMessages(prevMessages => [...prevMessages, event.payload]);
    });
  }, []);

  const sendMessage = (message) => {
    invoke('send_message', { message: message })
        .then(() => {
          console.log('Message sent successfully');
        })
        .catch((error) => {
          console.error('Failed to send message:', error);
        });
    setMessage('')
  }

  return (
      <div className="App">
        <header className="App-header">
          <button className="menu-button" onClick={toggleMenu} style={{zIndex: 101}}>Menu</button>
          <div className={`server-info ${isMenuOpen ? 'open' : ''}`}>Server: {server}</div>
          <div className={`chat-container ${isMenuOpen ? 'open' : ''}`}>
            <div className={`sidebar ${isMenuOpen ? 'open' : ''}`}>
              Chats
              <button className="new-chat-button">Start new chat</button>
            </div>
            <div className="chat">
              <div className="messages">
                <p>{messages.join('\n')}</p>
              </div>
              <div className="input-container">
                <input type="text" value={message} onChange={e => setMessage(e.target.value)}/>
                <button onClick={() => sendMessage(message)}>Send</button>
              </div>
            </div>
          </div>
        </header>
      </div>
  )
}

export default App;