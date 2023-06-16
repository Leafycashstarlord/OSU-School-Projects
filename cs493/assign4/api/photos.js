/*
 * API sub-router for businesses collection endpoints.
 */
const multer = require('multer')
const crypto = require('crypto')

const { Router } = require('express')
const { getChannel } = require('../lib/rabbitmq')

const { validateAgainstSchema } = require('../lib/validation')
const {
    PhotoSchema,
    insertNewPhoto,
    getPhotoById,
    savePhotoFile,
    removeUploadedPhoto
} = require('../models/photo')


const queue = 'photos'
const router = Router()

const fileTypes = {
    'image/jpeg': 'jpg',
    'image/png': 'png'
}

const upload = multer({
    storage: multer.diskStorage({
        destination: `${_dirname}/uploads`,
        filename: function(req, file, callback){
            const filename = crypto.pseudoRandomBytes(16).toString('hex')
            const extension = fileTypes[file.mimetype]
            callback(null, `${filename}.${extension}`)
        }
    }),
    fileFilter: function(req, file, callback){
        callback(null, !!fileTypes[file.mimetype])
    }
})

/*
 * POST /photos - Route to create a new photo.
 */
router.post('/', upload.single('image'), async (req, res) => {
    if(validateAgainstSchema(req.body, PhotoSchema) && req.file){
        try{
            iVar = {}
            if(req.body.caption){
                iVar = {
                    businessId: req.body.businessId,
                    caption: req.body.caption,
                    path: req.file.path,
                    filename: req.file.filename,
                    mimetype: req.file.mimetype
                }
            }else{
                iVar = {
                    businessId: req.body.businessId,
                    path: req.file.path,
                    filename: req.file.filename,
                    mimetype: req.file.mimetype
                }
            }

            const id = await savePhotoFile(iVar)
            const channel = getChannel()
            channel.sendToQueue(queue, Buffer.from(id.toString()))
            res.status(201).send({
                id: id
                links: {
                    photo: `/photos/${id}`,
                    business: `/businesses/${req.body.businessId}`
                }
            })
        } catch(err) {
            next(err)
        }
    }else{
        res.status(400).send({
            error: "Request body is not a valid photo object"
        })
    }
})

/*
 * GET /photos/{id} - Route to fetch info about a specific photo.
 */
router.get('/:id', async (req, res, next) => {
    try {
        const photo = await getPhotoById(req.params.id)
        if (photo) {
            const responseBody = {
                _id: photo._id,
                url: `/media/photot/${photo._id}`,
                thumbnail: `/media/thumbs/${photo._id}`,
                mimetype: photo.metadata.mimetype,
                businessId: photo.metadata.businessId
            }
            res.status(200).send(photo)
        } else {
            next()
        }
    } catch (err) {
        next(err)
    }
})

module.exports = router