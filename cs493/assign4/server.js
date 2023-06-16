/*
 * This require() statement reads environment variable values from the file
 * called .env in the project directory.  You can set up the environment
 * variables in that file to specify connection information for your own DB
 * server.
 */
require('dotenv').config()

const express = require('express')
const morgan = require('morgan')

const api = require('./api')
const { connectToDb } = require('./lib/mongo')
const { connectToRabbitMQ, getChannel } = require('./lib/rabbitmq')
const { getPhotoDownloadStream, getPhotoById, getPhotoByFilename, getDownloadStreamById } = require('./models/photo')
const { ObjectId, GridFSBucket } = require('mongodb')

const queue = 'photos'
const app = express()
const port = process.env.PORT || 8000

/*
 * Morgan is a popular logger.
 */
app.use(morgan('dev'))

app.use(express.json())
app.use(express.static('public'))

/*
 * All routes for the API are written in modules in the api/ directory.  The
 * top-level router lives in api/index.js.  That's what we include here, and
 * it provides all of the routes.
 */
app.use('/', api)


app.get('/media/photos/:id', function (req, res, next) {
    try {
        getDownloadStreamById(req.params.id).on('file', function (file) {
            res.status(200).type(file.metadata.mimetype)
        }).on('error', function (err) {
            if(err.code === 'ENOENT') {
                next()
            }else{
                next(err)
            }
        }).pipe(res)
    } catch (err) {
        res.status(500).send({
        error: "Unable to fetch photo.  Please try again later."
        })
    }
})

app.get('/media/thumbs/:id', async function (req, res, next) {
    try {
        const downloadStream = await getThumbnailDownloadStream(req.params.id)
        downloadStream.pipe(res)
    } catch (err) {
        res.status(500).send({
            error: "Unable to fetch thumbnail.  Please try again later."
        })
    }
})

async function getThumbnailDownloadStream(id) {
    const db = getDbReference()
    const bucket = new GridFSBucket(db, { bucketName: 'thumbnails' })

    const results = await bucket.find({ 'metadata.photoId': new ObjectId(id) }).toArray()
    const thumbnailId = results[0]._id

    return bucket.openDownloadStream(new ObjectId(thumbnailId))
}


app.use('*', function (req, res, next) {
    res.status(404).json({
        error: "Requested resource " + req.originalUrl + " does not exist"
    })
})

/*
 * This route will catch any errors thrown from our API endpoints and return
 * a response with a 500 status to the client.
 */
app.use('*', function (err, req, res, next) {
    console.error("== Error:", err)
    res.status(500).send({
        err: "Server error.  Please try again later."
    })
})

connectToDb( async function () {
    await connectToRabbitMQ(queue)
    app.listen(port, function () {
        console.log("== Server is running on port", port)
    })
})
