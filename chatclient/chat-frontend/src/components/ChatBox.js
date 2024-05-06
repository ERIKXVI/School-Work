import React, { useState, useEffect } from 'react';
import io from 'socket.io-client';
import Message from './Message';

const socket = io('http://localhost:3001');

function ChatBox({ username }) {
    const [messages, setMessages] = useState([]);
    const [newMessage, setNewMessage] = useState('');

    useEffect(() => {
        fetch('http://localhost:3001/messages') // Get history on load
            .then(res => res.json())
            .then(setMessages);

socket.on('message', (message) => {
    console.log("Received message:", message);
    setMessages((messages) => [...messages, message]);
});

        // Clean up the effect
        return () => socket.off('message');
    }, []);

    const handleSubmit = (e) => {
        e.preventDefault();
        socket.emit('message', { sender: username, message: newMessage });
        setNewMessage('');
    };

    return (
        <div>
            {messages.map((message, index) => (
                <Message key={index} message={message} />
            ))}
            <form id="chat-form" onSubmit={handleSubmit}>
                <input
                    id="message-input"
                    value={newMessage}
                    onChange={(e) => setNewMessage(e.target.value)}
                />
                <button type="submit">Send</button>
            </form>
        </div>
    );
}

export default ChatBox;