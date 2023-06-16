const express = require('express')
const morgan = require('morgan')
const redis = require("redis")

dotenv = require('dotenv').config()

const api = require('./api')
const sequelize = require('./lib/sequelize')

const app = express()
const port = process.env.PORT || 3000

const redisHost = process.env.REDIS_HOST || "localhost"
const redisPort = process.env.REDIS_PORT || "6379"
const redisClient = redis.createClient({
    url: `redis://${redisHost}:${redisPort}`
})

const { User, Course, Assignment, Submission } = require('./models')

app.use(morgan('dev'))
app.use(express.json())

const rateLimitWindowMillisconds = 60000
const rateLimitWindowMaxRequests = 10
const rateLimitRefreshRate = rateLimitWindowMaxRequests / rateLimitWindowMillisconds

async function rateLimit(req, res, next){
    let tokenBucket
    try{
        tokenBucket = await redisClient.hGetAll(req.ip)
    } catch (e) {
        next()
        return
    }

    tokenBucket = {
        tokens: parseFloat(tokenBucket.tokens) || rateLimitWindowMaxRequests,
        last: parseInt(tokenBucket.last) || Date.now()
    }

    const timestamp = Date.now()
    const ellapsedMillis = timestamp - tokenBucket.last
    tokenBucket.tokens += ellapsedMillis * rateLimitRefreshRate
    tokenBucket.tokens = Math.min(tokenBucket.tokens, rateLimitWindowMaxRequests)
    tokenBucket.last = timestamp

    if (tokenBucket.tokens >= 1) {
        tokenBucket.tokens -= 1
        await redisClient.hSet(req.ip, [
            [ "tokens", tokenBucket.tokens ],
            [ "last", tokenBucket.last ]
        ])
        next()
    }else{
        await redisClient.hSet(req.ip, [
            [ "tokens", tokenBucket.tokens ],
            [ "last", tokenBucket.last ]
        ])
        res.status(429).send({
            error: "Too many requests per minute"
        })
    }
}

app.use(rateLimit)

app.use('/', api)

app.get('/media/:filename', async (req, res) => {
    // All media are .txt files
    const filename = req.params.filename
    const media = await Submission.findOne({
        where: {
            filename: filename
        }
    })
    if (!media) {
        res.status(404).json({
            error: "Media " + filename + " not found"
        })
        return
    }
    res.setHeader('Content-Type', 'text/plain')
    res.send(media.file)
})
    

app.use('*', (req, res) => {
    res.status(404).json({
        error: "Requested resource " + req.originalUrl + " does not exist"
    })
})

app.use('*', (err, req, res, next) => {
    console.log("=== Server Error ===")
    console.error(err)
    res.status(500).json({
        error: "Internal Server Error"
    })
})

sequelize.sync().then(() => {
    redisClient.connect().then(function (){
        app.listen(port, async () => {
            console.log(`Server running on port ${port}`)
        
            // If debug environment variable is set, populate the database with some dummy data
            if (process.env.DEBUG) {
                await sequelize.query('SET FOREIGN_KEY_CHECKS = 0')
                await sequelize.sync({ force: true })
                await sequelize.query('SET FOREIGN_KEY_CHECKS = 1')

                const admin = await User.create({
                    name: "admin",
                    email: "admin@localhost",
                    password: "admin",
                    role: "admin"
                })
                const instructor = await User.create({
                    name: "instructor",
                    email: "instructor@localhost",
                    password: "instructor",
                    role: "instructor"
                })
                const student = await User.create({
                    name: "student",
                    email: "student@localhost",
                    password: "student",
                    role: "student"
                })
                const course = await Course.create({
                    subject: "CS",
                    number: "493",
                    title: "Cloud Application Development",
                    term: "Fall 2021",
                    instructorId: instructor.id
                })
                const assignment = await Assignment.create({
                    courseId: course.id,
                    title: "Assignment 1",
                    points: 100,
                    due: new Date(2021, 8, 1)
                })

                console.log("=== Dummy Data ===")
                console.log("Admin: " + admin.email + " / " + admin.password + " / " + admin.id)
                console.log("Instructor: " + instructor.email + " / " + instructor.password + " / " + instructor.id)
                console.log("Student: " + student.email + " / " + student.password + " / " + student.id)
                console.log("Course: " + course.subject + " " + course.number + " / " + course.title + " / " + course.id)
                console.log("Assignment: " + assignment.title + " / " + assignment.points + " / " + assignment.id)
            }
        })
    })
})