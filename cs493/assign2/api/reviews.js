const router = require('express').Router();
const { ValidationError } = require('sequelize');
const { validateAgainstSchema, extractValidFields } = require('../lib/validation');

const Review = require('../models/review');

exports.router = router;

/*
 * Schema describing required/optional fields of a review object.
 */
const reviewSchema = {
  userid: { required: true },
  businessid: { required: true },
  dollars: { required: true },
  stars: { required: true },
  review: { required: false }
};


/*
 * Route to create a new review.
 */
router.post('/', async function (req, res, next) {
  try {
    const review = await Review.create(req.body)
    res.status(201).send({id: review.id})
  }catch(err){
    if(err instanceof ValidationError){
      res.status(400).send({err: err.message})
    }else{
      next(err)
    }
  }
});

/*
 * Route to fetch info about a specific review.
 */
router.get('/:reviewID', async function (req, res, next) {
  const reviewId = req.params.reviewID
  const review = await Review.findByPk(reviewId)
  if(review){
    res.status(200).send(review)
  }else{
    next()
  }
});

/*
 * Route to update a review.
 */
router.put('/:reviewID', async function (req, res, next) {
  const reviewId = req.params.reviewID
  const result = await Review.update(req.body, {
    where: {id: reviewId}
  })
  if(result[0]>0){
    res.status(204).send()
  }else{
    next()
  }
});

/*
 * Route to delete a review.
 */
router.delete('/:reviewID', async function (req, res, next) {
  const reviewId = req.params.reviewID
  const result = await Review.destroy({where: {id: reviewId}})
  if(result > 0){
    res.status(204).send()
  }else{
    next()
  }
});