const sequelize = require('../lib/sequelize');
const { DataTypes } = require('sequelize');

const Assignment = sequelize.define('assignment', {
    courseId: { type: DataTypes.INTEGER, allowNull: false },
    title: { type: DataTypes.STRING, allowNull: false },
    points: { type: DataTypes.INTEGER, allowNull: false },
    due: { type: DataTypes.DATE, allowNull: false }
});

exports.Assignment = Assignment

exports.AssignmentClientFields = [
    'courseId',
    'title',
    'points',
    'due'
]