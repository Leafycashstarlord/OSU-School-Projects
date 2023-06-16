const jwt = require("jsonwebtoken")
const bcrypt = require("bcryptjs")
const { User } = require("../models")

const secretKey = "SuperSecret"

async function getUserByEmail(email) {
    try {
        const user = await User.findAll({where : { email : email}})
        if (user[0] != null) {
            console.log(user[0].dataValues)
            return user[0].dataValues
        }
        else {
            return null
        }
    } catch(err) {
        console.log(err)
        return null
    }
    
}

exports.getUserByEmail = getUserByEmail

function requireAuthentication (req, res, next) {
    console.log("== requireAuthentication()")
    const authHeader = req.get("Authorization") || ""
    const authHeaderParts = authHeader.split(" ")
    const token = authHeaderParts[0] === "Bearer" ?
        authHeaderParts[1] : null
    console.log("  -- token:", token)
    try {
        const payload = jwt.verify(token, secretKey)
        console.log("  -- payload:", payload)
        req.userid = payload.sub
        next()
    } catch (err) {
        console.error("== Error verifying token:", err)
        if (!token) {
            res.status(401).send({
                error: "Authentication token required"
            }) 
        } else {
            res.status(401).send({
                error: "Invalid authentication token"
            })
        }
    }
}

exports.requireAuthentication = requireAuthentication

async function requireAuthenticationCreateUser (req, res, next) {
    console.log("== requireAuthenticationCreateUser()")
    const authHeader = req.get("Authorization") || ""
    const authHeaderParts = authHeader.split(" ")
    const token = authHeaderParts[0] === "Bearer" ?
        authHeaderParts[1] : null
    console.log("  -- token:", token)
    try {
        if (req.body.role == "instructor" || req.body.role == "admin") {
            const payload = jwt.verify(token, secretKey)
            console.log("  -- payload:", payload)
            req.userid = payload.sub
            const user = await User.findOne({where: {id : req.userid}})
            if (user) {
                console.log("== admin attempt", user)
                if (user.dataValues.role != "admin") {
                    res.status(403).json({
                        error: "Attempt to create user with `instructor` or `admin` role, but provided login token of student"
                    })
                    return
                }
                else {
                    console.log("== ADMIN AUTHENTICATION SUCCESSFUL")
                }
            }
            else {
                console.log("wtf")
                return
            }
        }
        next()
    } catch (err) {
        console.error("== Error verifying token:", err)
        if (!token) {
            res.status(401).send({
                error: "Authentication token required"
            }) 
        } else {
            res.status(401).send({
                error: "Invalid authentication token"
            })
        }
    }
}

exports.requireAuthenticationCreateUser = requireAuthenticationCreateUser

async function validateUser(id, password) {
    const user = await getUserByEmail(id, true);
    if (user) {
        console.log("== user", password, user.password)
        const passwordHash = await bcrypt.hash(user.password, 8)
        console.log("== passwordHash", passwordHash)
        hashYes = await bcrypt.compare(password, passwordHash);
        authenticated = user && hashYes;
        return authenticated
    }
    return false
}

exports.validateUser = validateUser

exports.generateAuthToken = async function (email) {
    user = await getUserByEmail(email);
    const payload = { sub : user.id } 
    return jwt.sign(payload, secretKey, { expiresIn: '24h'})
}