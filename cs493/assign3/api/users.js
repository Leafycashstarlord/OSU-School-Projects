const { Router } = require('express')
const jwt = require('jsonwebtoken')
const { ValidationError } = require('sequelize')
const { Business } = require('../models/business')
const { Photo } = require('../models/photo')
const { Review } = require('../models/review')
const { User, UserClientFields} = require('../models/user')

const { generateAuthToken, requireAuthentication } = require('../lib/auth')
const bcrypt = require('bcrypt/dist/bcrypt')

const router = Router()
const secretKey = 'SuperSecret'


/*
* Helper FUnctions
*/
async function getUserById(userId, incPassword){
  if(incPassword){
    const thisUser = await User.findByPk(userId)
    return thisUser
  }else{
    const thisUser = await User.findByPk(userId, {
      attributes: {exclude: ['password']}
    })
    return thisUser
  }
}

async function hasAdminAccess(userr){
  const temp = await getUserById(userr, false)
  const isAdmin = temp.admin
  return isAdmin
}

async function userAccess(userr, tarId){
  const temp = await getUserById(userr, false)
  const isAdmin = temp.admin
  return !(userr != tarId && isAdmin != true)
}

async function validateUser(id, password){
  const thisUser = await getUserById(id, true)
  if(thisUser){
    console.log(" -- User exists")
  }
  if(thisUser && await bcrypt.compare(password, thisUser.password)){
    return true
  }else{
    return false
  }
}

/*
* Route to create a new user
*/
router.post('/', async function (req, res, next){
  try{
    if(req.body.admin){
      const authHeader = req.get('Authorization') || ''
      const authHeaderParts = authHeader.split(' ')

      const token = authHeaderParts[0] === 'Bearer' ? authHeaderParts[1] : null
      console.log(" -- token:", token)

      try{
        const payload = jwt.verify(token, secretKey)
        req.user = payload.sub

        const isAdmin = await hasAdminAccess(req.user)
        if(isAdmin){
          const user = await User.create(req.body, UserClientFields)
          res.status(201).send({id: user.id})
        }else{
          req.status(403).json({error: "Unauthorized to create user with admin perms"})
        }
      } catch (err) {
        res.status(401).json({error: "Invalid authentication token given", errortext: err})
      }
    }else{
      const user = await User.create(req.body, UserClientFields)
      res.status(201).send({id: user.id })
    }
  } catch (err) {
    if (err instanceof ValidationError){
      res.status(400).send({error: err.message})
    }else{
      next(err)
    }
  }
})

/*
* Route to login a user
*/
router.post('/login', async function (req, res, next) {
  if (req.body && req.body.email && req.body.password) {
    try {
      const thisUser = await User.findOne({where: {email: req.body.email}})
      const userId = thisUser.id
      const authenticated = await validateUser(userId, req.body.password)
      if (authenticated) {
        const token = generateAuthToken(userId)
        res.status(200).send({token: token})
      } else {
        res.status(401).send({
          error: "Invalid authentication credentials"
        })
      }
    } catch (err) {
      next(err)
    }
  }else{
    res.status(400).json({
      error: "Request body needs user ID and password."
    });
  }
})

/*
* Route to get user by id
*/
router.get('/:userId', requireAuthentication, async function (req, res) {
  const hasAccess = await userAccess(req.user, req.params.userId)
  
  if( !hasAccess ){
    res.status(403).json({
      error: "Unauthorized to access the specified resource"
    })
  }else{

    const userId = req.params.userId
    try {
      const thisUser = await getUserById(userId, false)
      res.status(200).json({
        user: thisUser
      })
    } catch (err) {
      if (err instanceof ValidationError) {
        res.status(400).send({ error: e.message })
      } else {
        next(err)
      }
    }
  }
})


/*
 * Route to list all of a user's businesses.
 */
router.get('/:userId/businesses', requireAuthentication, async function (req, res) {
  const hasAccess = await userAccess(req.user, req.params.userId)

  if( !hasAccess ){
    res.status(403).json({
      error: "Unauthorized access"
    })
  }else{
    const userId = req.params.userId
    const userBusinesses = await Business.findAll({ where: { ownerId: userId }})
    res.status(200).json({
      businesses: userBusinesses
    })
  }
})

/*
 * Route to list all of a user's reviews.
 */
router.get('/:userId/reviews', requireAuthentication, async function (req, res) {
  const hasAccess = await userAccess(req.user, req.params.userId)

  if( !hasAccess){
    res.status(403).json({
      error: "Unauthorized access"
    })
  }else{
    const userId = req.params.userId
    const userReviews = await Review.findAll({ where: { userId: userId }})
    res.status(200).json({
      reviews: userReviews
    })
  }
})

/*
 * Route to list all of a user's photos.
 */
router.get('/:userId/photos', requireAuthentication, async function (req, res) {
  const hasAccess = await userAccess(req.user, req.params.userId)
  if( !hasAccess ){
    res.status(403).json({
      error: "Unauthorized access"
    })
  }else{
    const userId = req.params.userId
    const userPhotos = await Photo.findAll({ where: { userId: userId }})
    res.status(200).json({
      photos: userPhotos
    })
  }
})

module.exports = router