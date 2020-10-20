// File for the different routers
// These allow for the user to call different options
// Allows for the .rest file to integrate the functions
// This allows for CRUD operations 

const express = require("express")
const router = express.Router()
const Cats = require("../models/cats")

// Get all enties - no requirements 

router.get("/", async (req, res) => {
    
    const cats = await Cats.find()
    res.json(cats)
})

// Get specific - uses ID for get, returns one entry containing = id

router.get("/:id", getCats, (req, res) => {
    res.json(res.cat)

})

// Post a new 'cat' -> requires the different variables which are stored in the db 

router.post("/", async (req, res) => {
    const cats = new Cats({
        name: req.body.name,
        age: req.body.age,
        color: req.body.color,
        gender: req.body.gender,
        eyeColor: req.body.eyeColor
    })
    const newCat = await cats.save()
    res.json(newCat)
})

// This allows to update a specific entry in the db; in this case one cat found by id

router.patch("/id:", getCats, async (req, res) => {
    if (req.body.name != null) {
        res.cats.name = req.body.name
    }

    if (req.body.age != null) {
        res.cats.age = req.body.age
    }

    const updateCats = await res.cats.save()
    res.json(updateCats)


})

// Allows for deletion of entry 

router.delete("/:id", getCats, async (req, res) => {
    try {
    await res.cat.remove()
    res.json({message : "Deleted"})
    }
    catch {
        res.json({message: "Error, nothing to delete"}) // Prints error if no file to delete
                                                        // Otherwise throws exception
    }
})


// Function for referenceing cat data
async function getCats(req, res, next) {
    let cat

    cat = await Cats.findById(req.params.id)
    
res.cat = cat
next()

}

module.exports = router
