var mysql = require('mysql');
var pool = mysql.createPool({
  connectionLimit : 10,
  host            : 'classmysql.engr.oregonstate.edu',
  user            : 'cs340_rollijac',
  password        : '#Lauren54',
  database        : 'cs340_rollijac'
});
module.exports.pool = pool;
