const { Router } = require('express')
const { ValidationError } = require('sequelize')
const { requireAuthentication } = require('../lib/auth')
const { Review, ReviewClientFields } = require('../models/review')
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
 * Route to create a new review.
 */
router.post('/', requireAuthentication, async function (req, res, next) {
  try {
    const hasAccess = await userAccess(req.user, req.body.userId)
    if( !hasAccess ){
      res.status(403).json({
        error: "Unauthorized access"
      })
    }else{
      const review = await Review.create(req.body, ReviewClientFields)
      res.status(201).send({ id: review.id })
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
 * Route to fetch info about a specific review.
 */
router.get('/:reviewId', async function (req, res, next) {
  const reviewId = req.params.reviewId
  const review = await Review.findByPk(reviewId)
  if (review) {
    res.status(200).send(review)
  } else {
    next()
  }
})

/*
 * Route to update a review.
 */
router.patch('/:reviewId', requireAuthentication, async function (req, res, next) {
  const reviewId = req.params.reviewId
  const thisReview = await Review.findOne({where: {id: reviewId}})
  const hasAccess = await userAccess(req.user, thisReview.userId)
  if( !hasAccess ){
    res.status(403).json({
      error: "Unauthorized access"
    })
  }else{
    /*
     * Update review without allowing client to update businessId or userId.
     */
    const result = await Review.update(req.body, {
      where: { id: reviewId },
      fields: ReviewClientFields.filter(
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
 * Route to delete a review.
 */
router.delete('/:reviewId', requireAuthentication,async function (req, res, next) {
  const reviewId = req.params.reviewId
  const thisReview = await Review.findOne({where: {id: reviewId}})
  const hasAccess = await userAccess(req.user, thisReview.userId)
  if( !hasAccess ){
    res.status(403).json({
      error: "Unauthorized access"
    })
  }else{
    const result = await Review.destroy({ where: { id: reviewId }})
    if (result > 0) {
      res.status(204).send()
    } else {
      next()
    }
  }
})

module.exports = router