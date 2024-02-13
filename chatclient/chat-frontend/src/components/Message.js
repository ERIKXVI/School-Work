import React from 'react';

function Message({ message }) {
    // Assume a simple message structure: { sender: 'username', text: 'message content' }
    return (
        <div className="message">
            <span className="sender">{message.sender}: </span>
            {message.text}
        </div>
    );
}

export default Message;
