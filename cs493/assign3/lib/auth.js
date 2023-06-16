const jwt = require('jsonwebtoken')

const secretKey = "SuperSecret"

function generateAuthToken(userId){
    const payload = { sub: userId}
    return jwt.sign(payload, secretKey, { expiresIn: "24h"})
}
exports.generateAuthToken = generateAuthToken

function requireAuthentication(req, res, next){
    const authHeader = req.get('Authorization') || ''
    const authHeaderParts = authHeader.split(' ')

    const token = authHeaderParts[0] === 'Bearer' ? authHeaderParts[1] : null
    console.log(" -- token:", token)

    try{
        const payload = jwt.verify(token, secretKey)
        console.log(" -- payload:", payload)
        req.user = payload.sub
        next()
    }catch (err) {
        res.status(401).json({
            error: "Invalid authentication token provided"
        })
    }
}
exports.requireAuthentication = requireAuthentication