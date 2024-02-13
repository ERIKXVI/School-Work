import React, { useState, useEffect } from 'react';
import io from 'socket.io-client';
import Message from './Message';

const socket = io('http://localhost:3001');

function ChatBox() {
    const [messages, setMessages] = useState([]);
    const [newMessage, setNewMessage] = useState('');
    const [username, setUsername] = useState('Anonymous'); // Placeholder

    useEffect(() => {
        fetch('http://localhost:3001/messages') // Get history on load
            .then(res => res.json())
            .then(setMessages);

        socket.on('message', (message) => {
            console.log("Frontend received message:", message);
            setMessages([...messages, message]);
        });
    }, []);

    const sendMessage = (e) => {
        e.preventDefault();
        console.log("Sending message with username:", username);
        socket.emit('message', { sender: username, message: newMessage }); // Correct object structure
        setNewMessage('');
    };

    return (
        <div className="chat-container">
            <div className="message-list">
                {messages.map((message, index) => (
                    <Message key={index} message={message} />
                ))}
            </div>
            <form onSubmit={sendMessage}>
                <input
                    type="text"
                    value={newMessage}
                    onChange={(e) => setNewMessage(e.target.value)}
                />
                <button type="submit">Send</button>
            </form>
        </div>
    );
}

export default ChatBox;
