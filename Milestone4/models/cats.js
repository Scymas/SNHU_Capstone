// Schuyler Enneman
// Cats models file
// This file is set information for the model 
// Using a schema we can create multiple 'Cats' with different variables

const mongoose = require("mongoose")

//  Schema for containing cat information 
//  Cat name, age, color, gender, and eye color are stored here
const catschema = new mongoose.Schema({

    name: {
        type: String,
        required: true // Ensure that each type is required
    },

    age: {
        type: String,
        required: true
    },

    color: {
        type: String,
        required: true
    },

    gender: {
        type: String,
        required: true
    },

    eyeColor: {
        type: String,
        required: true
    },

})

module.exports = mongoose.model("Cats", catschema)
