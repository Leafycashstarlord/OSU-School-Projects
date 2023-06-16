const router = require('express').Router();
const { validateAgainstSchema, extractValidFields } = require('../lib/validation');

const { reviews } = require('./reviews');
const { photos } = require('./photos');
const Business = require("../models/business.js");
const { ValidationError } = require('sequelize');
const Review = require('../models/review');
const Photo = require('../models/photo');

exports.router = router;

/*
 * Schema describing required/optional fields of a business object.
 */
const businessSchema = {
  ownerid: { required: true },
  name: { required: true },
  address: { required: true },
  city: { required: true },
  state: { required: true },
  zip: { required: true },
  phone: { required: true },
  category: { required: true },
  subcategory: { required: true },
  website: { required: false },
  email: { required: false }
};

/*
 * Route to return a list of businesses.
 */
router.get('/', async function (req, res) {

  /*
   * Compute page number based on optional query string parameter `page`.
   * Make sure page is within allowed bounds.
   */
  let page = parseInt(req.query.page) || 1
  page = page < 1 ? 1 : page
  const numPerPage = 10
  const offset = (page - 1) * numPerPage

  const result = await Business.findAndCountAll({
    limit: numPerPage,
    offset: offset
  })

  /*
   * Generate HATEOAS links for surrounding pages.
   */
  const lastPage = Math.ceil(result.count / numPerPage)
  const links = {};
  if (page < lastPage) {
    links.nextPage = `/businesses?page=${page + 1}`;
    links.lastPage = `/businesses?page=${lastPage}`;
  }
  if (page > 1) {
    links.prevPage = `/businesses?page=${page - 1}`;
    links.firstPage = '/businesses?page=1';
  }

  /*
   * Construct and send response.
   */
  res.status(200).json({
    businesses: result.rows,
    pageNumber: page,
    totalPages: lastPage,
    pageSize: numPerPage,
    totalCount: result.count,
    links: links
  });

});

/*
 * Route to create a new business.
 */
router.post('/', async function (req, res, next) {
  try {
    const business = await Business.create(req.body)
    console.log(" -- business:", business.toJSON)
    res.status(201).send({id: business.id})
  } catch(err) {
    if(err instanceof ValidationError){
      res.status(400).send({err: err.message})
    }else{
      next(err)
    }
  }
});

/*
 * Route to fetch info about a specific business.
 */
router.get('/:businessid', async function (req, res, next) {
  const businessId = req.params.businessid
  const businesss = await Business.findByPk(businessId, {
    include: [Photo, Review]
  })
  if(businesss){
    res.status(200).send(businessid)
  }else{
    next()
  }
});

/*
 * Route to replace data for a business.
 */
router.put('/:businessid', async function (req, res, next) {
  const businessId = req.params.businessid
  const result = await Business.update(req.body, {
    where: {id: businessId}
  })
  if(result[0]>0){
    res.status(204).send()
  }else{
    next()
  }
});

/*
 * Route to delete a business.
 */
router.delete('/:businessid', async function (req, res, next) {
  const businessId = req.params.businessid

  const result = await Business.destroy({where: {id: businessId}})
  if(result>0){
    res.status(204).send()
  }else{
    next()
  }
});