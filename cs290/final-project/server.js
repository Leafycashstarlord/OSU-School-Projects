var fs = require('fs');
var path = require('path');
var express = require('express');
var exphbs = require('express-handlebars');



var app = express();

var port = process.env.PORT || 7540;

app.engine('handlebars', exphbs({ default: 'main'}));
app.set('view engine', 'handlebars');


app.use(express.json());
app.use(express.static('public'));

app.get('/',function(req,res,next){
	var scoreData=require('./scoreData.json');
	var taScore={
		taData: scoreData.ta,
		ta: true
	};
	var hawScore={
		hawData:scoreData.haw,
		ta: false
	};
	res.status(200).render('home',{
		taScore: taScore,
		hawScore: hawScore,
		beaver: true
	});
});

app.get('/:game', function(req, res, next){
	var scoreData = require('./scoreData.json')
	var game = req.params.game.toLowerCase();
	if(game == "ta"){
		var taScore={
			taData: scoreData.ta,
			ta: true
		};
		res.status(200).render('game',{
			taScore: taScore,
			ta: true
		});
	}else if(game == "haw"){
		var hawScore={
			hawData: scoreData.haw,
			ta: false
		};
		res.status(200).render('game',{
			hawScore: hawScore,	
			ta: false
		});
	}else{
		next();
	}

});

app.post('/:game/addScore', function(req, res, next){
	//console.log("== req.body: ", req.body);
	var game = req.params.game.toLowerCase();
	if(game == "ta" || game == "haw"){
		if (req.body && req.body.name && req.body.score){
			var scoreValues = req.body;
			//res.status(200).send("Successfully got score for "+ game + ": " + scoreValues.name + ", " + scoreValues.score);

			var response = storeScore(scoreValues, game);
			console.log("==Response: ", response);
			if (response == 200){
				res.status(200).send("Score stored successfully");
			}else{
				res.status(500).send("Error storing score");
			}

		}else{
			res.status(400).send("Request must have 'name' and 'score' values");
		}
	}else{
		res.status(404).send("Request must be one of the games");
	}
});


function storeScore(scoreValues, game){
	var maxIndex = 9;
	var scoreData = require('./scoreData.json')
	var gameData;
	if(game == "ta"){
		gameData = scoreData.ta;
	}else{
		gameData = scoreData.haw;
	}


	for(var i = 0; i <= maxIndex; i++){
		if(gameData[i] == undefined){
			gameData[i] = {name: scoreValues.name, score: scoreValues.score};
			break;
		}else if(gameData[i].score < scoreValues.score){
			for(var x = maxIndex-1; x >= i; x--){
				gameData[x+1] = gameData[x];
			}
			gameData[i] = {name: scoreValues.name, score: scoreValues.score};
			break;
		}
	}

	//gameData.push({
	//	name: scoreValues.name,
	//	score: scoreValues.score
	//});

	if(game == "ta"){
		scoreData.ta = gameData;
	}else{
		scoreData.haw = gameData;
	}

	console.log("Score data: ", scoreData);


	fs.writeFile(
		__dirname + '/scoreData.json',
		JSON.stringify(scoreData, null, 2),
		function (err, data) {
			if(err){
				console.log(" --err:", err);
				return 500;
			}
		}
	);
	return 200;
}


app.get('*', function(req, res){
	res.status(404).render('404');
});

app.listen(port, function() {
	console.log("== Server is listening on port", port);
});
