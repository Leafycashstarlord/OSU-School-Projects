const sequelize = require("../lib/sequelize")
const { DataTypes } = require("sequelize")

const Course = sequelize.define('course', {
    subject: {type: DataTypes.STRING, allowNull: false},
    number: {type: DataTypes.STRING, allowNull: false},
    title: {type: DataTypes.STRING, allowNull: false},
    term: {type: DataTypes.STRING, allowNull: false},
    instructorId: {type: DataTypes.INTEGER, allowNull: true} // Allow null for now so we can delete instructors
})

exports.Course = Course
exports.courseFields = [
    'subject',
    'number',
    'title',
    'term',
    'instructorId'
]