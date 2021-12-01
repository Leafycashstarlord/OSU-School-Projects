var gameActive = false;
var clicks = 0;
var gameTimer;
var timerDisplay = document.getElementsByClassName('site-title')[0];
var timePassed = 0;
var score = 0;
function createEventListeners(){
	//var optionsButton = document.getElementById('options_button');
	//optionsButton.addEventListener('click', handleOptionsButtonClicked);

	//var closeOptionsButton = document.getElementById('close_modal');
	//closeOptionsButton.addEventListener('click', handleCloseOptionsButtonClicked);

	//document.getElementById('theme-update-button').addEventListener('click', function(){
	//	document.body.classList.toggle('black')
	//});

	//console.log("== current game: ",getGameFromURL());
	if(getGameFromURL() == "ta"){
		
		var taButton = document.getElementById('ta_button');
		taButton.addEventListener('click', handleTaButtonClicked);
	}else if(getGameFromURL() == "haw"){
		var hawButton = document.getElementById('haw_button');
		hawButton.addEventListener('mousedown', handleHawButtonMouseDown);
		hawButton.addEventListener('mouseup', handleHawGameStopped);
		hawButton.addEventListener('mouseout', handleHawGameStopped);
	}
	if(getGameFromURL() != null){
		var closeGameModalButton = document.getElementById("close_game_modal");
		var modalAcceptButton = document.getElementById("modal_accept");
		closeGameModalButton.addEventListener('click', closeGameModal);
		modalAcceptButton.addEventListener('click', handleModalAcceptButtonClicked);
	}


}

function getGameFromURL(){
	var url = window.location.href;
	var game;
	//console.log("== URL: ", url);
	if(url.includes("/ta")){
		return "ta";
	}else if(url.includes("/haw")){
		return "haw";
	}else{
		return null;
	}
}

function handleOptionsButtonClicked(event){
	var optionsModal = document.getElementById('options_modal');
	var backdrop = document.getElementById('modal-backdrop');
	backdrop.classList.remove("hidden");
	optionsModal.classList.remove("hidden");
	console.log("== Options Modal Opened!");
}

function handleCloseOptionsButtonClicked(event){
	closeOptions();
}

function closeOptions(){
	var optionsModal = document.getElementById('options_modal');
	var backdrop = document.getElementById('modal-backdrop');
	backdrop.classList.add("hidden");
	optionsModal.classList.add("hidden");
	console.log("== Options Modal Closed!");
}

function handleTaButtonClicked() {
	if(gameActive){
		//alert("clicked!");
		clicks++;
		//scoreDisplay.innerHTML = clicks;
	}else{
		clicks = 1;
		timePassed = 30.00;
		//scoreDisplay.innerHTML = clicks;
		gameActive = true;
		gameTimer = setInterval(runTaTime, 100);
	}
}

function runTaTime(){
	timePassed -= 0.1;
	timerDisplay.innerHTML = String(timePassed).substring(0, 4);
	if(timePassed <= 0){
		stopTaGame();
	}
}

function stopTaGame(){
	gameActive = false;
	clearInterval(gameTimer);
	score = clicks;
	clicks = 0;
	timerDisplay.innerHTML = "0.00";

	//sendScoreToServer(score, "Ryan", "ta");
	//open modal
	openGameModal();
	//alert("Game Over! Score = " + score);
}

function handleHawButtonMouseDown(){
	if(!gameActive){
		gameActive = true;
		gameTimer = setInterval(runHawTime, 100);
	}
}

function runHawTime(){
	timePassed += 0.1;
	timerDisplay.innerHTML = String(timePassed).substring(0, 4);
}

function handleHawGameStopped(){
	if(gameActive == true){
		gameActive = false;
		clearInterval(gameTimer);
		score = parseFloat(timePassed.toFixed(1));
		if(score > 0){
			openGameModal();
		}
		timePassed = 0;
		
		//sendScoreToServer(score, "Ryan", "haw");
	}
}


function sendScoreToServer(score, name, game){
	var addRequest = new XMLHttpRequest();
	var reqURL = '/' + game + '/addScore';
	addRequest.open('POST', reqURL);


	//var scoreReduced = score.toFixed(3);
	//score = parseFloat(scoreReduced);

	var reqBody = JSON.stringify({
		name: name,
		score: score
	});

	addRequest.setRequestHeader('Content-Type', 'application/json');
	
	addRequest.send(reqBody);

}


function handleModalAcceptButtonClicked(){
	var playerName = document.getElementById('player_name').value;
	if(playerName){
		sendScoreToServer(score, playerName, getGameFromURL());
		closeGameModal();
	}else{
		alert("A Username Is Required");
	}
}

function openGameModal(){
	var gameModal = document.getElementById('game_modal');
	var modalTitle = document.getElementsByClassName('modal-title')[0];
	var backdrop = document.getElementById('game-modal-backdrop');
	backdrop.classList.remove('hidden');
	modalTitle.innerHTML = "Score: " + score;
	gameModal.classList.remove('hidden');
}

function closeGameModal(){
	timerDisplay.innerHTML = "TaHaw";
	var gameModal = document.getElementById('game_modal');
	var backdrop = document.getElementById('game-modal-backdrop');
	backdrop.classList.add('hidden');
	gameModal.classList.add('hidden');
	window.location.reload();
}

//function updateScoreboards(){

//}

/*
var loops = 0;
setInterval(function(){
	var titleName = document.getElementsByClassName('site-title')[0];
	titleName.innerHTML = "TaHaw"+ loops;
	loops += 1;
}, 1000);
*/

function initializeSite(){
	createEventListeners();
}

initializeSite();