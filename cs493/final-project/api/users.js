const { Router } = require('express')
const { DataTypes } = require("sequelize")
const { validateAgainstSchema, extractValidFields } = require("../lib/validation")
const { getUserByEmail, validateUser, requireAuthentication, requireAuthenticationCreateUser, generateAuthToken } = require("../lib/auth")
const { User, Course, userSchema, userFields } = require("../models")
const { ValidationError } = require('sequelize')

const router = Router()

User.belongsToMany(Course, {through: "User_Course"})
Course.belongsToMany(User, {through: "User_Course"})

router.get('/:id', requireAuthentication, async (req, res, next) => {
    const adminCheck = await User.findOne({where : { id : req.userid}})
    if (req.userid == req.params.id || (adminCheck && adminCheck.dataValues.role == "admin")) {
        const user = await User.findAll({where : { id : req.params.id}})
        console.log(user, user.length)
        if (user.length > 0) {
            console.log("stupid")
            if (user[0].dataValues.role == "student") {
                const student = await User.findAll({where : { id : req.params.id}, include:  {model: Course, attributes: [`id`]}})
                console.log("== STUDENT",student)
                const courseArray = []
                for (i = 0; i < student[0].dataValues.courses.length; i++) {
                    courseArray.push(student[0].dataValues.courses[i].id)
                }
                res.status(200).send({
                    name : student[0].dataValues.name,
                    email : student[0].dataValues.email,
                    password : student[0].dataValues.password,
                    role : student[0].dataValues.role,
                    courses : courseArray
                })
            }
            else if (user[0].dataValues.role == "instructor") {
                const courses = await Course.findAll({where : { instructorId : req.params.id}, attributes: [`id`]})
                console.log("== INSTRUCTOR", user)
                const courseArray = []
                for (i = 0; i < courses.length; i++) {
                    courseArray.push(courses[i].id)
                }
                res.status(200).send({
                    name : user[0].dataValues.name,
                    email : user[0].dataValues.email,
                    password : user[0].dataValues.password,
                    role : user[0].dataValues.role,
                    coursesTaught: courseArray
                })
            } else {
                res.status(200).send({
                    name : user[0].dataValues.name,
                    email : user[0].dataValues.email,
                    password : user[0].dataValues.password,
                    role : user[0].dataValues.role,
                })
            }
        } else {
            next()
        }
        // res.status(200).send({test: "test"});
    }
    else {
        res.status(403).json({error: "Authentication Failed"})
    }
})

router.post('/', requireAuthenticationCreateUser, async (req, res, next) => {
    if (validateAgainstSchema(req.body, userSchema)) {
        try {
            if (req.body.role != "admin" && req.body.role != "instructor" && req.body.role != "student") {
                res.status(400).json({
                    error: "Invalid body: Role field can be `student`, `instructor`, or `admin`."
                })
                return
            }
            
            user = await User.create(extractValidFields(req.body, userSchema), userFields)
            res.status(201).json({id: user.id})
        } catch (err){
            if (err instanceof ValidationError){
                res.status(400).json({
                    error: "A user already exists with that email."
                })
                return
            } else {
                next(err)
                return
            }
        }
    } else {
        res.status(400).json({
            error: "Invalid body: User schema requires `name`, `email`, `password`, `role`"
        })
    }
})

router.post('/login', async (req, res, next) => {
    if (req.body && req.body.email && req.body.password) {
        try {
            const authenticated = await validateUser(req.body.email, req.body.password)
            console.log(authenticated)
            if (authenticated) {
                console.log("== AUTHENTICATED")
                const token = await generateAuthToken(req.body.email)
                res.status(200).send({token: token});
            }
            else {
                res.status(401).send({ error : "Invalid authentication credentials"})
            }
            } catch (e) {
                next(e)
            }
      }
      else {
        res.status(400).send({ error : "Request body requires `email` and `password`"})
      }
})

module.exports = router