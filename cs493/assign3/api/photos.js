const { Router } = require('express')
const { ValidationError } = require('sequelize')
const { requireAuthentication } = require('../lib/auth')
const { Photo, PhotoClientFields } = require('../models/photo')
const { User } = require('../models/user')

const router = Router()

/*
* Helper Functions
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

async function userAccess(userr, tarId){
  const temp = await getUserById(userr, false)
  const isAdmin = temp.admin
  return !(userr != tarId && isAdmin != true)
}

/*
 * Route to create a new photo.
 */
router.post('/', requireAuthentication, async function (req, res, next) {
  try {
    const hasAccess = await userAccess(req.user, req.body.userId)
    if( !hasAccess ){
      res.status(403).json({
        error: "Unauthorized access"
      })
    }else{
      const photo = await Photo.create(req.body, PhotoClientFields)
      res.status(201).send({ id: photo.id })
    }
  } catch (e) {
    if (e instanceof ValidationError) {
      res.status(400).send({ error: e.message })
    } else {
      next(e)
    }
  }
})

/*
 * Route to fetch info about a specific photo.
 */
router.get('/:photoId', async function (req, res, next) {
  const photoId = req.params.photoId
  const photo = await Photo.findByPk(photoId)
  if (photo) {
    res.status(200).send(photo)
  } else {
    next()
  }
})

/*
 * Route to update a photo.
 */
router.patch('/:photoId', requireAuthentication, async function (req, res, next) {
  const photoId = req.params.photoId
  const thisPhoto = await Photo.findOne({where: {id: photoId}})
  const hasAccess = await userAccess(req.user, thisPhoto.userId)
  if( !hasAccess ){
    res.status(403).json({
      error: "Unauthorized access"
    })
  }else{
    /*
     * Update photo without allowing client to update businessId or userId.
     */
    const result = await Photo.update(req.body, {
      where: { id: photoId },
      fields: PhotoClientFields.filter(
        field => field !== 'businessId' && field !== 'userId'
      )
    })
    if (result[0] > 0) {
      res.status(204).send()
    } else {
      next()
    }
  }
})

/*
 * Route to delete a photo.
 */
router.delete('/:photoId', requireAuthentication, async function (req, res, next) {
  const photoId = req.params.photoId
  const thisPhoto = await Photo.findOne({where: {id: photoId}})
  const hasAccess = await userAccess(req.user, thisPhoto.userId)
  if( !hasAccess ){
    res.status(403).json({
      error: "Unauthorized access"
    })
  }else{
    const result = await Photo.destroy({ where: { id: photoId }})
    if (result > 0) {
      res.status(204).send()
    } else {
      next()
    }
  }
})

module.exports = router