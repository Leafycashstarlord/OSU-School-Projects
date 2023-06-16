const { DataTypes } = require('sequelize')

const sequelize = require('../lib/sequelize')
const bcrypt = require('bcryptjs')

const { Business } = require("./business")

const User = sequelize.define('user', {
    name: { type: DataTypes.STRING, allowNull: false},
    email: { type: DataTypes.STRING, allowNull: false},
    password: {
        type: DataTypes.STRING,
        allowNull: false,
        set(value) {
            this.setDataValue('password', bcrypt.hashSync(value, 8))
        }
    },
    admin: { type: DataTypes.BOOLEAN, defaultValue: false}
})

exports.User = User
exports.UserClientFields = [
    'name',
    'email',
    'password',
    'admin'
]