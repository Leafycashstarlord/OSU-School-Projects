/*
 * Write your client-side JS code in this file.  Don't forget to include your
 * name and @oregonstate.edu email address below.
 *
 * Name: Jackson Rollins
 * Email: rollijac@oregonstate.edu
 */

 //Page Events
document.getElementById("filter-update-button").addEventListener("click", updateSearchFilters);
document.getElementById("sell-something-button").addEventListener("click", createOrDeletePostScreen);
document.getElementById("modal-close").addEventListener("click", createOrDeletePostScreen);
document.getElementById("modal-cancel").addEventListener("click", createOrDeletePostScreen);
document.getElementById("modal-accept").addEventListener("click", createPost);

//Global Variables, definitions, and assignments
var posts = [];
var current_post = document.getElementById("posts").firstElementChild;
var size = document.getElementById("posts").childElementCount;
posts.push(current_post);

for(var i = 1; i < size; i++){
    posts.push(current_post.nextElementSibling);
    current_post = current_post.nextElementSibling;
}

//Retrieves and saves each of the filters. Also clears all posts and screen and reposts them.
function updateSearchFilters(){
    var filterText = document.getElementById("filter-text").value.toLowerCase();
    var min = document.getElementById("filter-min-price").value;
    var max = document.getElementById("filter-max-price").value;

    var city = "";
    var cities = document.getElementById("filter-city");
    var list_size = cities.childElementCount;
    for(var i = 0; i < list_size; i++){
        if(cities.children[i].selected){
            city = cities.children[i].text.toLowerCase();
            break;
        }
    }

    var conditions = [];
    var conditionList = document.getElementById("filter-condition");
    for(var i = 1; i < 6; i++){
        if(conditionList.children[i].firstElementChild.checked){
            conditions.push(conditionList.children[i].lastElementChild.textContent.toLowerCase());
        }
    }

    var postElement = document.getElementById("posts");
    var size = postElement.children.length;
    for(var i = 0; i < size; i++){
        postElement.removeChild(postElement.firstElementChild);
    }

    repost(posts, city, conditions, min, max, filterText, postElement);
}

//Reposts each post that qualifies under the filter constraints
function repost(posts, city, conditions, min, max, filterText, postElement){
    for(var i = 0; i < posts.length; i++){
        var post = posts[i];
        var canPost = false;
        var verifyCondition = false;
        var postTitle = post.firstElementChild.lastElementChild.firstElementChild.text.toLowerCase();
        var postPrice = parseInt(post.getAttribute("data-price"));
        var postCity = post.getAttribute("data-city").toLowerCase();
        var postCondition = post.getAttribute("data-condition");

        if((postCity == city) || (city == "any")){
            if(postTitle.includes(filterText)){
                for(var j = 0; j < conditions.length; j++){
                    if(postCondition == conditions[j]){
                        verifyCondition = true;
                        break;
                    }
                }
                if((verifyCondition) || (conditions.length == 0)){
                    if((min == "") && (max == "")){
                        canPost = true;
                    }
                    else if((min != "") && (max == "") && (postPrice >= min)){
                        canPost = true;
                    }
                    else if((min == "") && (max != "") && (postPrice <= max)){
                        canPost = true;
                    }
                    else if((postPrice >= min) && (postPrice <= max)){
                        canPost = true;
                    }
                }
            }
        }
        if(canPost == true){
            postElement.appendChild(post);
        }
    }
}

//Creates or deletes the new post screen
function createOrDeletePostScreen(){
    document.getElementById("post-text-input").value = "";
    document.getElementById("post-photo-input").value = "";
    document.getElementById("post-price-input").value = "";
    document.getElementById("post-city-input").value = "";
    document.getElementById("post-condition-new").checked = true;
    document.getElementById("modal-backdrop").classList.toggle('hidden');
    document.getElementById("sell-something-modal").classList.toggle('hidden');
}

//Checks the new post inputs to see if they are all filled out
function checkNewPostInputs(){
    if((document.getElementById("post-text-input").value == "") || (document.getElementById("post-photo-input").value == "") || (document.getElementById("post-price-input").value == "") || (document.getElementById("post-city-input").value == "")){
            return false;
    }else{
        return true;
    }
}

//Creates the new post based off the inputs on the new post screen
function createPost(){
    if(!checkNewPostInputs()) {
        alert("Please fill in all entries.");
        return;
    }

    var lastPost = document.getElementById("posts").lastElementChild;
    var postClone = lastPost.cloneNode(true);
    var condition = "";

    if(document.getElementById("post-condition-new").checked){
        condition = "new";
    }
    else if(document.getElementById("post-condition-excellent").checked){
        condition = "excellent";
    }
    else if(document.getElementById("post-condition-good").checked){
        condition = "good";
    }
    else if(document.getElementById("post-condition-fair").checked){
        condition = "fair";
    }
    else if(document.getElementById("post-condition-poor").checked){
        condition = "poor";
    }

    postClone.setAttribute("data-price", document.getElementById("post-price-input").value);
    postClone.setAttribute("data-city", document.getElementById("post-city-input").value);
    postClone.setAttribute("data-condition", condition);
    postClone.firstElementChild.firstElementChild.firstElementChild.setAttribute("src", document.getElementById("post-photo-input").value);
    postClone.firstElementChild.firstElementChild.firstElementChild.removeAttribute("alt");
    postClone.firstElementChild.lastElementChild.firstElementChild.textContent = document.getElementById("post-text-input").value;
    postClone.firstElementChild.lastElementChild.firstElementChild.nextElementSibling.textContent = "$" + document.getElementById("post-price-input").value;
    postClone.firstElementChild.lastElementChild.lastElementChild.textContent = "(" + document.getElementById("post-city-input").value + ")";

    posts.push(postClone);
    document.getElementById("posts").appendChild(postClone);
    createOrDeletePostScreen();
}