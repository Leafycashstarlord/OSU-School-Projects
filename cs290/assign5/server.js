/*
 * Write your routing code in this file.  Make sure to add your name and
 * @oregonstate.edu email address below.
 *
 * Name: Jackson Rollins
 * Email: rollijac@oregonstate.edu
 */

var path = require('path');
var express = require('express');
var exphbs = require('express-handlebars');
var postData = require('./postData.json');
console.log("== postData: ", postData);
var app = express();
var port = process.env.PORT || 6942;

app.engine('handlebars', exphbs({defaultLayout: 'main'}));
app.set('view engine', 'handlebars');

app.use(express.static('public'));

app.get('/', function(req, res, next){
  res.status(200).render('postPage', {
    posts: postData,
    showStuff: true
  });
});

app.get('/posts/:n', function (req, res, next){
  var number = req.params.n;
  if(postData[number] && number <= 7 && number >=0){
    res.status(200).render('postPage', {
      posts: postData[number],
      showStuff: false
    });
  }else{
    next();
  }
});

app.get('*', function (req, res) {
  res.status(404).render('404');
});

app.listen(port, function () {
  console.log("== Server is listening on port", port);
});
