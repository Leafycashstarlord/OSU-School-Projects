const router = require('express').Router();

exports.router = router;

const { businesses } = require('./businesses');
const { reviews } = require('./reviews');
const { photos } = require('./photos');
const Business = require('../models/business');
const Review = require('../models/review');
const Photo = require('../models/photo');

/*
 * Route to list all of a user's businesses.
 */
router.get('/:userid/businesses', async function (req, res) {
  const userId = req.params.userid
  const userBusiness = await Business.findAll({where: {ownerid: userId}})
  res.status(200).json({
    businesses: userBusiness
  })
});

/*
 * Route to list all of a user's reviews.
 */
router.get('/:userid/reviews', async function (req, res) {
  const userId = req.params.userid
  const userReview = await Review.findAll({where: {userId: userId}})
  res.status(200).json({
    reviews: userReview
  })
});

/*
 * Route to list all of a user's photos.
 */
router.get('/:userid/photos', async function (req, res) {
  const userId = req.params.userid
  const userPhoto = await Photo.findAll({where: {userId: userId}})
  res.status(200).json({
    photos: userPhoto
  })
});
