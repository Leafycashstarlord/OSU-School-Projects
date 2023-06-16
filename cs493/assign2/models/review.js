const { DataTypes } = require('sequelize')

const sequelize = require('../lib/sequelize')

const Review = sequelize.define('review', {
  userid: { type: DataTypes.INTEGER, allowNull: false },
  dollars: { type: DataTypes.INTEGER, allowNull: false },
  stars: { type: DataTypes.INTEGER, allowNull: false },
  review: { type: DataTypes.TEXT, allowNull: true }
})

module.exports = Review