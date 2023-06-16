const { User, userFields, userSchema } = require('./user')
const { Course, courseFields } = require('./course')
const { Assignment, AssignmentClientFields } = require('./assignment')
const { Submission, SubmissionClientFields } = require('./submission')

// Associations
User.hasMany(Course, { foreignKey: 'instructorId' })
Course.belongsTo(User, { foreignKey: 'instructorId', onDelete: 'SET NULL' })

Submission.belongsTo(User, { foreignKey: 'studentId', onDelete: 'CASCADE'})
Submission.belongsTo(Assignment, { foreignKey: 'assignmentId', onDelete: 'CASCADE'})
User.hasMany(Submission, { foreignKey: 'studentId' })
Assignment.hasMany(Submission, { foreignKey: 'assignmentId' })

Assignment.belongsTo(Course, { foreignKey: 'courseId', onDelete: 'CASCADE'})
Course.hasMany(Assignment, { foreignKey: 'courseId' })

Course.belongsToMany(User, { through: 'enrollment', foreignKey: 'courseId', onDelete: 'CASCADE' })
User.belongsToMany(Course, { through: 'enrollment', foreignKey: 'userId', onDelete: 'CASCADE' })

module.exports = {
    User,
    Course,
    Assignment,
    Submission,
    userFields,
    courseFields,
    AssignmentClientFields,
    SubmissionClientFields,
    userSchema
}
