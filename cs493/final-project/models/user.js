const sequelize = require("../lib/sequelize")
const { DataTypes } = require("sequelize")

const userSchema = {
    name: {type: DataTypes.STRING, allowNull: false, unique: false},
    email: {type: DataTypes.STRING, allowNull: false, unique: true},
    password: {type: DataTypes.STRING, allowNull: false, unique: false},
    role: {type: DataTypes.STRING, allowNull: false, unique: false}
}

const User = sequelize.define("user", userSchema)


exports.User = User
exports.userSchema = userSchema
exports.userFields = Object.keys(userSchema)