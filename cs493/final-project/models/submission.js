const sequelize = require('../lib/sequelize');
const { DataTypes } = require('sequelize');

const Submission = sequelize.define('submission', {
    assignmentId: { type: DataTypes.INTEGER, allowNull: false},
    studentId: { type: DataTypes.INTEGER, allowNull: false },
    timestamp: { type: DataTypes.DATE, allowNull: false },
    grade: { type: DataTypes.FLOAT, allowNull: false },
    file: { type: DataTypes.BLOB, length: "long", allowNull: false },
    filename: { type: DataTypes.STRING, allowNull: false }
});

exports.Submission = Submission

exports.SubmissionClientFields = [
    'assignmentId',
    'studentId',
    'timestamp',
    'grade',
    'file'
]