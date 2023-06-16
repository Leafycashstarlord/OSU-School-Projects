const { Router } = require('express')
const fs = require('fs');
const { validateAgainstSchema, extractValidFields } = require("../lib/validation")
const { requireAuthentication } = require("../lib/auth")
const { ValidationError } = require('sequelize')
const { Course, User, Assignment, courseFields } = require("../models")

const router = Router()

// User.belongsToMany(Course, {through: "userCourse"})
// Course.belongsToMany(User, {through: "userCourse"})

router.get('/', async function (req, res, next) {
    /*
     * Compute page number based on optional query string parameter `page`.
     * Make sure page is within allowed bounds.
     */
    let page = parseInt(req.query.page) || 1
    page = page < 1 ? 1 : page
    const numPerPage = 10
    const offset = (page - 1) * numPerPage
  
    try {
      const result = await Course.findAndCountAll({
        limit: numPerPage,
        offset: offset
      })
  
      /*
       * Generate HATEOAS links for surrounding pages.
       */
      const lastPage = Math.ceil(result.count / numPerPage)
      const links = {}
      if (page < lastPage) {
        links.nextPage = `/courses?page=${page + 1}`
        links.lastPage = `/courses?page=${lastPage}`
      }
      if (page > 1) {
        links.prevPage = `/courses?page=${page - 1}`
        links.firstPage = '/courses?page=1'
      }
  
      /*
       * Construct and send response.
       */
      res.status(200).json({
        courses: result.rows,
        pageNumber: page,
        totalPages: lastPage,
        pageSize: numPerPage,
        totalCount: result.count,
        links: links
      })
    } catch (e) {
      next(e)
    }
})

// NOTE: REMOVE THE INCLUDE USER
router.get('/:courseId', async function (req, res, next) {
  const courseId = req.params.courseId
  try {
    const course = await Course.findByPk(courseId)
    if (course) {
      res.status(200).send(course)
    } else {
      next()
    }
  } catch (e) {
    next(e)
  }
})

router.post('/', requireAuthentication, async function (req, res, next) {
  
    const curr = await User.findByPk(req.userid)
    if (curr.role != "admin") {
      res.status(403).json({
        error: "Unauthorized to access the specified resource"
      });
      return
    }
    try {
      const course = await Course.create(req.body, courseFields)
      res.status(201).send({ id: course.id })
    } catch (e) {
      if (e instanceof ValidationError) {
        res.status(400).send({ error: e.message })
      } else {
        next(e)
      }
    }
})


router.patch('/:courseId', requireAuthentication, async function (req, res, next) {
  const courseId = req.params.courseId
  const curr = await User.findByPk(req.userid)
  const course = await Course.findByPk(courseId)
    if (curr.role != "admin" || (curr.role == "instructor" && course.instructorId == curr.id)) {
    res.status(403).json({
      error: "Unauthorized to access the specified resource"
    });
    return
  }
  try {
    const result = await Course.update(req.body, {
      where: { id: courseId },
      fields: courseFields
    })
    if (result[0] > 0) {
      res.status(204).send()
    } else {
      next()
    }
  } catch (e) {
    next(e)
  }
})

router.delete('/:courseId', requireAuthentication, async function (req, res, next) {   
    const courseId = req.params.courseId
    const curr = await User.findByPk(req.userid)
    if (curr.role != "admin") {
      res.status(403).json({
        error: "Unauthorized to access the specified resource"
      });
      return
    }
    try {
      const result = await Course.destroy({ where: { id: courseId }})
      if (result > 0) {
        res.status(204).send()
      } else {
        next()
      }
    } catch (e) {
      next(e)
    }
})

router.get('/:courseId/students', requireAuthentication, async function (req, res, next) {
  const courseId = req.params.courseId
  const curr = await User.findByPk(req.userid)
  const courseTest = await Course.findByPk(courseId)
  if (curr.role != "admin" || (curr.role == "instructor" && courseTest.instructorId == curr.id)) {
    res.status(403).json({
      error: "Unauthorized to access the specified resource"
    });
    return
  }
    try {
      const course = await Course.findOne({
        where : { id : req.params.courseId}, 
        include:  {model: User}})
      const students = []

      if (!course) {
        res.status(404).send({
          error: "Specified course not found"
        })
        return
      }

      for (const x of await course.getUsers({where: {role: "student"}})){
        const student = {
          name: x.name,
          email: x.email,
          password: x.password,
          role: x.role
        }
        students.push(student)
      }
      // const course = await userCourse.findAll()
      if (course) {
        res.status(200).send({students: students})
      } else {
        next()
      }
    } catch (e) {
      next(e)
    }
})

// NOTE: Add error checking to make sure its actual user being added
router.post('/:courseId/students', requireAuthentication, async function (req, res, next) {
  const courseId = req.params.courseId
  const curr = await User.findByPk(req.userid)
  const courseTest = await Course.findByPk(courseId)
  if (curr.role != "admin" || (curr.role == "instructor" && courseTest.instructorId == curr.id)) {
    res.status(403).json({
      error: "Unauthorized to access the specified resource"
    });
    return
  }
  try {
      let course = await Course.findByPk(courseId)
      if (course){
        for (const element of req.body.remove){
          // const temp = await User.findOne({
          //   where : { id : parseInt(element)}
          // })
          // if (temp != null){
          //   console.log("1: ", course)
          //   temp.removeCourse(course)
          //   course.removeUser(temp)
          // }
          const user = await User.findByPk(parseInt(element))
          if (user != null){
            course.removeUser(user)
          }
        }
        for (const element of req.body.add){
          // const temp2 = await User.findOne({
          //   where : { id : parseInt(element)} 
          // })
          // // console.log("2: ", course)
          // if (temp2 != null){
          //   temp2.addCourse(course)
          //   // console.log("3: ", temp2)
          // }
          const user = await User.findByPk(parseInt(element))
          if (user != null){
            course.addUser(user)
          }
        }
        res.status(201).send()
      } else {
        next()
      }
    } catch (e) {
      if (e instanceof ValidationError) {
        res.status(400).send({ error: e.message })
      } else {
        next(e)
      }
    }
})

router.get('/:courseId/roster', requireAuthentication, async function (req, res, next) {
  const courseId = req.params.courseId
  const curr = await User.findByPk(req.userid)
  const courseTest = await Course.findByPk(courseId)
  if (curr.role != "admin" || (curr.role == "instructor" && courseTest.instructorId == curr.id)) {
    res.status(403).json({
      error: "Unauthorized to access the specified resource"
    });
    return
  }
  try {
    const course = await Course.findOne({ where : { id : req.params.courseId}})
    const students = []
    for (const x of await course.getUsers({where: {role: "student"}})){
      const user = {
        id: x.id,
        name : x.name,
        email : x.name
      }
      students.push(user)
    }
    if (students.length > 0) {
      const csvData = students.map(x => Object.values(x).join(",")).join('\n')
      // const actualCsvData = "data:text/csv;charset=utf-8," + csvData
      // var encodedUri = encodeURI(actualCsvData)
      const path = "./student-data.csv"
      fs.writeFile(path, csvData, err => {
        if (err){
          console.log("ERROR: Writing csv")
        }
        else {
          console.log("Written successfuly")
        }
      })
      var read = fs.createReadStream(path)
      // res.status(200).send(read)
      res.writeHead(200, {'Content-Type': 'text/csv'})
      // var read = fs.createReadStream(path)
      read.pipe(res)
    } else {
      res.status(400).send({ error: "No students enrolled in this course"})
    }
  } catch (e) {
    next(e)
  }
})

router.get('/:courseId/assignments', async function (req, res, next) {
  // If the course doesn't exist, return 404
  const course = await Course.findByPk(req.params.courseId)
  if (!course) {
    res.status(404).send({
      error: "Specified course not found"
    })
    return
  }

  // Paginated list of assignments for a course
  const courseId = req.params.courseId
  const page = req.query.page || 1
  const numPerPage = parseInt(req.query.perPage) || 10
  const offset = (page - 1) * numPerPage
  try {
    const result = await Assignment.findAndCountAll({
      where: { courseId: courseId },
      limit: numPerPage,
      offset: offset,
      order: [['createdAt', 'DESC']]
    })

    const lastPage = Math.ceil(result.count / numPerPage)
    const links = {}
    if (page < lastPage) {
      links.nextPage = `/courses/${courseId}/assignments?page=${page + 1}`
      links.lastPage = `/courses/${courseId}/assignments?page=${lastPage}`
    }
    if (page > 1) {
      links.prevPage = `/courses/${courseId}/assignments?page=${page - 1}`
      links.firstPage = `/courses/${courseId}/assignments?page=1`
    }

    res.status(200).send({
      assignments: result.rows,
      page: page,
      totalPages: lastPage,
      pageSize: numPerPage,
      totalCount: result.count,
      links: links
    })
  } catch (e) {
    next(e)
  }
})

module.exports = router