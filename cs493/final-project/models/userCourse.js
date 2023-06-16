const sequelize = require("../lib/sequelize")
const { DataTypes } = require("sequelize")
const { ValidationError } = require('sequelize')
const { User } = require("../models/user")
const { Course } = require("../models/course")
const { Assignment } = require("../models/assignment")

const userCourse = sequelize.define('userCourse', {
    userId: {type: DataTypes.INTEGER, allowNull: false},
    courseId: {type: DataTypes.INTEGER, allowNull: false}
})

userCourse.hasMany(User)
userCourse.hasMany(Course)


exports.userCourse = userCourse
exports.courseFields = [
    'userId',
    'courseId'
]