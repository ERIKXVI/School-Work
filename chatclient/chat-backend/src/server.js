const express = require('express');
const cors = require('cors');
const sqlite3 = require('sqlite3').verbose();
const http = require('http');
const socketIO = require('socket.io');

const app = express();
const server = http.createServer(app);
const io = socketIO(server, {
    cors: {
        origin: 'http://192.168.136.1:3000', // Replace with your frontend origin
        methods: ["GET", "POST"]
    }
});

// Basic Middleware
app.use(cors({ origin: 'http://192.168.136.1:3000' })); // Apply CORS globally for HTTP routes
app.use(express.json());

// Connect to SQLite
const db = new sqlite3.Database('./chat.db', sqlite3.OPEN_READWRITE | sqlite3.OPEN_CREATE, (err) => {
    if (err) return console.error(err.message);
    console.log('Connected to SQLite database.');
});

// Create messages table (if it doesn't exist)
db.run(`CREATE TABLE IF NOT EXISTS messages (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    sender TEXT, 
    message TEXT,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
)`);

// Basic API Route for Message History
app.get('./messages', (req, res) => {
    db.all('SELECT * FROM messages', (err, rows) => {
        if (err) return res.status(500).send(err);
        res.json(rows);
    });
});

// Socket.IO Logic
io.on('connection', (socket) => {
    console.log('User connected.');

    // Emit initial message history on connection
    db.all('SELECT * FROM messages', (err, messages) => {
        socket.emit('messages', messages);
    });

    socket.on('message', (data) => {
        console.log("Received message:", data);
        const { sender, message } = data;
        db.run('INSERT INTO messages (sender, message) VALUES (?, ?)', [sender, message], (err) => {
            if (err) return console.error(err.message);
            io.emit('message', data); // Broadcast
        });
    });

    socket.on('disconnect', () => {
        console.log('User disconnected.');
    });
});

const port = 3001;
server.listen(port, () => console.log(`Server running on port ${port}`));
