import React, { useState, useEffect } from 'react';
import { invoke } from '@tauri-apps/api/tauri';
import { listen } from '@tauri-apps/api/event';

function App() {
  const [message, setMessage] = useState('')
  const [messages, setMessages] = useState([])

  useEffect(() => {
    invoke('connect_to_server', {
      url: 'ws://localhost:3000/ws',
    })
      .catch((error) => console.error(error));

    listen('message', (event) => {
      setMessages(prevMessages => [...prevMessages, event.payload]);
    });
  }, []);

  const sendMessage = (message) => {
    invoke('send_message', { message: message })
      .then(() => {
        console.log('Message sent successfully');
      })
      .catch((error) => {
        console.log('Failed to send message:', error);
      });
    setMessage('')
  }

  return (
    <div className="App">
      <header className="App-header">
        <p>{messages.join('\n')}</p>
        <input type="text" value={message} onChange={e => setMessage(e.target.value)} />
        <button onClick={() => sendMessage(message)}>Send</button>
      </header>
    </div>
  )
}

export default App