const express = require('express')
const logger = require('./logger')

const app = express()

const businesses = require('./data/businesses.json')
const reviews = require('./data/reviews.json')
const photos = require('./data/photos.json')

app.use(express.json())
app.use(logger)

app.listen(8000, function(){
    console.log("== Server is listening on port 8000")
})

//Get all Businesses
app.get('/data/business', (req, res, next) => {
    console.log("== req.query:", req.query)
    let page = parseInt(req.query.page) || 1
    const pageSize = 10
    const lastPage = Math.ceil(businesses.length / pageSize)
    page = (page < 1) ? 1 : page
    page = (page > lastPage) ? lastPage : page

    const start = (page - 1) * pageSize
    const end = start + pageSize
    const businessPage = businesses.slice(start, end)

    const links = {}
    if(page < lastPage) {
        links.nextPage = `/data/business?page=${page + 1}`
        links.lastPage = `/data/business?page=${lastPage}`
    }
    if(page > 1) {
        links.prevPage = `/data/business?page=${page - 1}`
        links.firstPage = `/data/business?page=1`
    }
    
    res.status(200).send({
        businesses: businessPage,
        page: page,
        pageSize: pageSize,
        lastPage: lastPage,
        total: businesses.length,
        links: links
    })
})

//Add a business
app.post('/data/business', (req, res, next) => {
    console.log(" -- req.body:", req.body)
    if(req.body && req.body.name && req.body.address && req.body.city && req.body.state && req.body.zip && req.body.phone && req.body.category && req.body.subcategory){
        res.status(201).send({
            id: businesses.length,
            ownerid: parseInt(req.body.ownerid) || businesses.length,
            name: req.body.name,
            address: req.body.address,
            city: req.body.city,
            state: req.body.state,
            zip: req.body.zip,
            phone: req.body.phone,
            category: req.body.category,
            subcategory: req.body.subcategory,
            website: req.body.website,
            email: req.body.email
        })
    }else{
        res.status(400).send({
            error: "Incorrect Required Fields"
        })
    }
})

//Specific Business
app.get('/data/business/:bID', (req, res, next) => {
    console.log(" -- req.params:", req.params)
    const bID = req.params.bID;
    if(businesses[bID]){
        res.status(200).send(businesses[bID])
    }else{
        next()
    }
})

//Edit Business Listing
app.put('/data/business/:bID', (req, res, next) => {
    var bID = parseInt(req.params.bID);
    if (businesses[bID]) {
        if (req.body && req.body.ownerid && req.body.name && req.body.address && req.body.city && req.body.state && req.body.zip && req.body.phone && req.body.category && req.body.subcategory) {
            businesses[bID] = req.body;

            res.status(200).json({
                business: "business edited",
                name: req.body.name,
                address: req.body.address,
                city: req.body.city,
                state: req.body.state,
                zip: req.body.zip,
                phone: req.body.phone,
                category: req.body.category,
                subcategory: req.body.subcategory,
                website: req.body.website,
                email: req.body.email
            });            
        } else {
            res.status(400).send({
                error: "Incorrect edit please resubmit."
            });
        }
    } else {
        next();
    } 
});

//Remove Business
app.delete('/data/business/:bID', (req, res, next) => {
    const bID = req.params.bID
    if(businesses[bID]){
        businesses[bID] = null
        res.status(204).end()
    }else{
        next();
    }
})

//Add Review
app.post('/data/reviews', (req, res, next) => {
    console.log(" -- req.body:", req.body)
    if(req.body && req.body.businessid && req.body.dollars && req.body.stars){
        res.status(201).send({
            id: reviews.length,
            userid: parseInt(req.body.userid) || reviews.length,
            businessid: parseInt(req.body.businessid),
            dollars: parseInt(req.body.dollars),
            stars: parseInt(req.body.stars),
            review: req.body.review
        })
    }else{
        res.status(400).send({
            error: "Incorrect Required Fields"
        })
    }
})
//Edit Review
app.put('/reviews/:rID', (req, res, next) => {
    var rID = parseInt(req.params.rID);
    if (reviews[rID]) {
        if (req.body && req.body.userid && req.body.businessid && req.body.dollars && req.body.stars) {
            reviews[rID] = req.body;

            res.status(200).json({
                review: "review edited",
                dollars: parseInt(req.body.dollars),
                stars: parseInt(req.body.stars),
                review: req.body.review
            });            
        } else {
            res.status(400).send({
                error: "Incorrect edit please resubmit."
            });
        }
    } else {
        next();
    } 
});

//Delete Review
app.delete('/data/reviews/:rID', (req, res, next) => {
    var rID = parseInt(req.params.rID);
    if (reviews[rID]) {
        reviews[rID] = null;
        res.status(204).end();
    } else {
        next();
    } 
})

//Add Photo
app.post('/data/photos', (req, res, next) => {
    console.log(" -- req.body:", req.body)
    if(req.body && req.body.businessid){
        res.status(201).send({
            id: photos.length,
            userid: parseInt(req.body.userid) || photos.length,
            businessid: parseInt(req.body.businessid),
            caption: req.body.caption
        })
    }else{
        res.status(400).send({
            error: "Incorrect Required Fields"
        })
    }
})

//Edit Photo
app.put('/data/photos/:pID', (req, res, next) => {
    var pID = parseInt(req.params.pID);
    if (photos[pID]) {
        if (req.body.caption) {
            photos[pID] = req.body;
            res.status(200).json({
              photo: "photo edited",
              caption: req.body.caption
            });            
        } else {
            res.status(400).send({
              error: "Incorrect edit please resubmit."
            });
        }
    } else {
        next();
    } 
});



//Delete Photo
app.delete('/data/photos/:pID', (req, res, next) => {
    const pID = req.params.pID
    if(photos[pID]){
        photos[pID] = null
        res.status(204).end()
    }else{
        next()
    }
})

//Businesses One Owns
app.get('/data/business', (req, res, next) => {
    if(req.body && req.body.ownerid){
        const oID = parseInt(req.body.ownerid)
        const oBusinesses = []
        for(var i = 0; i < businesses.length; i++){
            if(businesses[i].ownerid = oID){
                oBusinesses.push(businesses[i])
            }
        }
        res.status(200).send({
            businesses: oBusinesses
        })
    }else{
        res.status(400).send({
            error: "Incorrect Owner ID"
        })
    }
})

//Reviews One Owns
app.get('/data/reviews', (req, res, next) => {
    if(req.body && req.body.userid){
        const uID = parseInt(req.body.userid)
        const uReviews = []
        for(var i = 0; i < reviews.length; i++){
            if(reviews[i].ownerid = uID){
                uReviews.push(reviews[i])
            }
        }
        res.status(200).send({
            reviews: uReviews
        })
    }else{
        res.status(400).send({
            error: "Incorrect User ID"
        })
    }
})

//Photos One Owns
app.get('/data/photos', (req, res, next) => {
    if(req.body && req.body.userid){
        const uID = parseInt(req.body.userid)
        const uPhotos = []
        for(var i = 0; i < photos.length; i++){
            if(photos[i].ownerid = uID){
                uPhotos.push(photos[i])
            }
        }
        res.status(200).send({
            photos: uPhotos
        })
    }else{
        res.status(400).send({
            error: "Incorrect User ID"
        })
    }
})

//Universal 404 error
app.use("*", (req, res, next) => {
    res.status(404).send({
        error: `Requested URL doesn't exist: ${req.originalUrl}`
    })
})