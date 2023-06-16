const router = require('express').Router();
const { validateAgainstSchema, extractValidFields } = require('../lib/validation');

const { ValidationError } = require('sequelize')
const Photo = require('../models/photo');

exports.router = router;

/*
 * Schema describing required/optional fields of a photo object.
 */
const photoSchema = {
  userid: { required: true },
  businessid: { required: true },
  caption: { required: false }
};


/*
 * Route to create a new photo.
 */
router.post('/', async function (req, res, next) {
  try {
    const photo = await Photo.create(req.body)
    res.status(201).send({id: photo.id})
  }catch(err) {
    if(err instanceof ValidationError){
      res.status(400).send({err: err.message})
    }else{
      next(err)
    }
  }
});

/*
 * Route to fetch info about a specific photo.
 */
router.get('/:photoID', async function (req, res, next) {
  const photoId = req.params.photoId
  const photo = await Photo.findByPk(photoId)
  if(photo){
    res.status(200).send(photo)
  }else{
    next()
  }
});

/*
 * Route to update a photo.
 */
router.put('/:photoID', async function (req, res, next) {
  const photoId = req.params.photoID
  const result = await Photo.update(req.body, {
    where: {id: photoId}
  })
  if(result[0] > 0){
    res.status(204).send()
  }else{
    next()
  }
});

/*
 * Route to delete a photo.
 */
router.delete('/:photoID', async function (req, res, next) {
  const photoId = req.params.photoID
  const result = await Photo.destroy({where: {id: photoId}})
  if(result > 0){
    res.status(204).send()
  }else{
    next()
  }
});