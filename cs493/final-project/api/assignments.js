const { Router } = require('express')
const { requireAuthentication } = require("../lib/auth")
const { ValidationError } = require('sequelize')
const fs = require('fs')
const { Assignment, Submission, User, Course, AssignmentClientFields, SubmissionClientFields } = require("../models")
const multer = require('multer')
const crypto = require('crypto')
const router = Router()



const fileTypes = {
    'text/plain': 'txt'
}

const upload = multer({
    storage: multer.diskStorage({
        destination: `${__dirname}/submissions`,
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

// Delete file from disk helper function
function deleteFile(path){
    return new Promise((resolve, reject) => {
        fs.unlink(path, (err) => {
            if (err){
                reject(err)
            }else{
                resolve()
            }
        })
    })
}

// router.get('/', async (req, res) => {
//     // Not a valid route, you cannot get all assignments via this route and must specify a course
//     // in the course route3
//     res.status(404).json({
//         error: "Specify a course to get assignments for"
//     })
// })

router.get('/:assignmentId', async (req, res, next) => {
    const assignmentId = req.params.assignmentId
    try {
        const assignment = await Assignment.findByPk(assignmentId)
        if (assignment) {
            res.status(200).json(assignment)
        }
        else {
            res.status(404).json({
                error: "Assignment not found"
            })
        }
    }
    catch (e) {
        next(e)
    }
})

router.post('/', requireAuthentication, async (req, res, next) => {
    // TODO Figure out why validateAgainstSchema() is not working
    try {
        // Check if the user is an instructor and teaching the course, or if the user is an admin
        // If not, return 403
        const course = await Course.findByPk(req.body.courseId)
        const user = await User.findByPk(req.userid)
        if (user.role != "admin") {
            if (user.role != "instructor" || user.id != course.instructorId) {
                res.status(403).json({
                    error: "You are not authorized to create assignments for this course"
                })
                return
            }
        }


        const id = await Assignment.create(req.body)
        res.status(201).json({
            id: id
        })
        return
    }
    catch (e) {
        // Catch foreign key constraint errors
        if (e.name == "SequelizeForeignKeyConstraintError") {
            res.status(400).json({
                error: "Course does not exist"
            })
            return
        }
        next(e)
    }
})

router.patch('/:assignmentId', requireAuthentication, async (req, res, next) => {
    const assignmentId = req.params.assignmentId
        try {
            // Check if the user is an instructor and teaching the course, or if the user is an admin
            // If not, return 403
            const assignment = await Assignment.findByPk(assignmentId)
            if (!assignment) {
                res.status(404).json({
                    error: "Assignment not found"
                })
                return
            }
            const course = await Course.findByPk(assignment.courseId)
            const user = await User.findByPk(req.userid)
            if (user.role != "admin") {
                if (user.role != "instructor" || user.id != course.instructorId) {
                    res.status(403).json({
                        error: "You are not authorized to update assignments for this course"
                    })
                    return
                }
            }

            // If the res.body does not have any fields related to the assignment, return 400
            // AssignmentClientFields is an array of fields that are allowed to be updated
            if (!Object.keys(req.body).some(field => AssignmentClientFields.includes(field))) {
                res.status(400).json({
                    error: "Request body must contain at least one of the following fields: " + AssignmentClientFields.join(", ")
                })
                return
            }

            await assignment.update(req.body)
            res.status(200).end()
        }
        catch (e) {
            // Catch SequelizeForeignKeyConstraintError
            if (e.name === "SequelizeForeignKeyConstraintError") {
                res.status(400).json({
                    error: e.message
                })
                return
            }
            next(e)
        }
})

router.delete('/:assignmentId', requireAuthentication, async (req, res, next) => {
    const assignmentId = req.params.assignmentId
    try {
        const assignment = await Assignment.findByPk(assignmentId)
        if (!assignment) {
            res.status(404).json({
                error: "Assignment not found"
            })
            return
        }
        // Check if the user is an instructor and teaching the course, or if the user is an admin
        // If not, return 403
        const course = await Course.findByPk(assignment.courseId)
        const user = await User.findByPk(req.userid)
        if (user.role != "admin") {
            if (user.role != "instructor" || user.id != course.instructorId) {
                res.status(403).json({
                    error: "You are not authorized to delete assignments for this course"
                })
                return
            }
        }

        // TODO: Delete all submissions for this assignment
        await Assignment.destroy({
            where: {
                id: assignmentId
            }
        })
        res.status(204).end()
    }
    catch (e) {
        next(e)
    }
})

//Post a submission
router.post('/:assignmentId/submissions', requireAuthentication, upload.single('file'), async (req, res, next) => {
    const assignmentId = req.params.assignmentId
    // If the assignmentID doesn't match the assignmentId in the body, return 400
    if (assignmentId != req.body.assignmentId) {
        res.status(400).json({
            error: "Assignment ID in the body does not match the assignment ID in the URL"
        })
        return
    }
    try {
        const assignment = await Assignment.findByPk(assignmentId)
        const course = await Course.findByPk(assignment.courseId)
        const user = await User.findByPk(req.userid)

        // If the user is not a student in this course, instructor of this course, or admin, return 403
        if (user.role != "admin") {
            if (user.role != "instructor" || user.id != course.instructorId) {
                if (user.role != "student" || user.id != course.getStudents({where: {id: req.body.studentId}})) {
                    res.status(403).json({
                        error : "You are not authorized to post a submission for this assignment"
                    })
                    return
                }
            }
        }

        // Read the file
        console.log(req.file.filename)
        const fileData = fs.readFileSync(req.file.path)
        const submission = await Submission.create({
            assignmentId: req.body.assignmentId,
            studentId: req.body.studentId,
            timestamp: req.body.timestamp,
            grade: req.body.grade,
            file: fileData,
            filename: req.file.filename
        }, SubmissionClientFields)
    
        try {
            fs.writeFileSync(req.file.path, submission.file)
        }
        catch (e) {
            next(e)
        }

        await deleteFile(req.file.path)
        res.status(201).send({id: submission.id})
        return
    }
    catch (e) {
        next(e)
    }
})

//Get a List of all the Submissions
router.get('/:assignmentId/submissions', requireAuthentication, async (req, res, next) => {
    try{
        const assignment = await Assignment.findByPk(req.params.assignmentId)
        const course = await Course.findByPk(assignment.courseId)
        const user = await User.findByPk(req.userid)
        if (user.role != "admin") {
            if (user.role != "instructor" || user.id != course.instructorId) {
                res.status(403).json({
                    error: "You are not authorized to update assignments for this course"
                })
                return
            }
        }

        /*
        * Compute page number based on optional query string parameter `page`.
        * Make sure page is within allowed bounds.
        */
        let page = parseInt(req.query.page) || 1
        page = page < 1 ? 1 : page
        const numPerPage = 10
        const offset = (page - 1) * numPerPage

        try{
            const result = await Submission.findAndCountAll({
                limit: numPerPage,
                offset: offset
            })

            submissions = result.rows.map(submission => {
                return {
                    id: submission.id,
                    assignmentId: submission.assignmentId,
                    studentId: submission.studentId,
                    timestamp: submission.timestamp,
                    grade: submission.grade,
                    file: `/media/${submission.filename}`
                }
            })

            /*
            * Generate HATEOAS links for surrounding pages.
            */
            const lastPage = Math.ceil(result.count / numPerPage)
            const links = {}
            if (page < lastPage) {
                links.nextPage = `/${req.params.id}/submissions?page=${page + 1}`
                links.lastPage = `/${req.params.id}/submissions?page=${lastPage}`
            }
            if (page > 1) {
                links.prevPage = `/${req.params.id}/submissions?page=${page - 1}`
                links.firstPage = '/${req.params.id}/submissions?page=1'
            }

            /*
            * Construct and send response.xx
            */
            res.status(200).json({
                submissions: submissions,
                pageNumber: page,
                totalPages: lastPage,
                pageSize: numPerPage,
                totalCount: result.count,
                links: links
            })
        }catch(e){
            next(e)
        }
    }catch (e){
        next(e)
    }
})

module.exports = router