// Schuyler Enneman
// MongoDB Web App 
// CS-499
// Milestone 4

// Many files and directories are required for this program, along with packages
// Node JS, Express, Mongoose, and MongoDB are required for this to work
// npm modules also installed
// This is the server file, primarily for routing and initializing npm 

// Restful API found from - https://www.youtube.com/watch?v=fgTGADljAeg&ab_channel=WebDevSimplified
// Express installation from - https://expressjs.com/en/starter/installing.html

console.log(process.env.DATABASE_URL) // initialize the dotenv file

const env = require('dotenv').config()
const express = require("express"); // Initialize express (node.js)
const app = express();
const mongoose = require("mongoose"); // Initialize mongoose (used for MongoDB modeling)

// This uses mongoose to connect the the local host on port 3000
mongoose.connect(process.env.MONGO_URL, { useNewUrlParser: true, useUnifiedTopology: true })
const db = mongoose.connection // Create database equal to the connecction 

app.use(express.json())

const aRouter = require("./animals/cats.js") // Router for cats information 
app.use("/cats", aRouter)

// Connects to port 3000 and alerts user to server start
app.listen(3000, () => console.log("Server Started - SNHU Capstone"))
