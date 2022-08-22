var services = {'netflix':0, 'prime':0, 'hulu':0, 'disney':0, 'hbo':0, 'peacock':0, 'paramount':0, 'starz':0, 'showtime':0, 'apple':0, 'mubi':0};


function store() {   //stores items in the localStorage
    localStorage.clear();
    var username = document.getElementById('username').value;
    window.localStorage.setItem('username',JSON.stringify(username));
}

function checkLogout() { // auto logout function
    if (!window.localStorage.getItem('username'))
    {
        localStorage.clear()
        window.location.href = "/";
    }
}

function checkLogin() { // auto login function
    if (window.localStorage.getItem('username'))
    {
        window.location.href = "/browse";
    }
}

function getUsername() { // pull username from local storage
    var name = JSON.parse(window.localStorage.getItem('username'));
    document.getElementById("username").innerHTML = name;
  }

function signOut() { // sign user out, back to landing
    localStorage.clear()
    window.location.href = "/";
}

function deleteAccount() { // remove user from database
    const request = new XMLHttpRequest();
    const usr = window.localStorage.getItem('username');
    const url = "/deleteAccount/?username=" + usr;

    request.open('GET', url, true);
    request.withCredentials = true;
    request.setRequestHeader("x-csrf-token", "fetch");    
    request.setRequestHeader("Accept", "application/json");
    request.setRequestHeader("Content-Type", "application/json; charset=utf-8");
    request.send();

    localStorage.clear()
    window.location.href = "/";
}

function serviceHandler(element) { // handle clicks on services for account page
    services[element.id] = (services[element.id] + 1) % 2;
    element.classList.toggle("w3-grayscale-max");
    element.classList.toggle("w3-opacity-max");
}

function intialize() { // helps display which services are already owned
    const request = new XMLHttpRequest();
    const usr = window.localStorage.getItem('username');
    const url = "/getServices/?username=" + usr;

    request.open('GET', url, true);
    request.withCredentials = true;
    request.setRequestHeader("x-csrf-token", "fetch");    
    request.setRequestHeader("Accept", "application/json");
    request.setRequestHeader("Content-Type", "application/json; charset=utf-8");
    request.responseType = 'json';


    request.onload = function() {
        processServices(request.response);
    }
    request.send();
}

function processServices(response) { // toggles previously owned services on
    let userServices = response['userServices'];
    for (let user of userServices)
    {
        services[user] = 1;
        let element = document.getElementById(user);

        element.classList.toggle("w3-grayscale-max");
        element.classList.toggle("w3-opacity-max");
    }
}

function submitServices() { // submits new set of services to database
    const request = new XMLHttpRequest();
    let usr = window.localStorage.getItem('username');

    newServices = [];
    for (let key in services) {
        if (services[key])
            newServices.push(key);
    }

    const url = "/account/?username=" + usr + "&newServices={" + String(newServices) + "}";

    request.open('GET', url, true);
    request.withCredentials = true;
    request.setRequestHeader("x-csrf-token", "fetch");    
    request.setRequestHeader("Accept", "application/json");
    request.setRequestHeader("Content-Type", "application/json; charset=utf-8");
    request.responseType = 'json';

    request.onload = function() {
        document.getElementById("changeDialog").innerHTML = "Information updated!";
    }

    request.send();
}

function submitRegistrationServices(element) { // same as above but for registration page
    id = element.id;
    const request = new XMLHttpRequest();

    let usr = document.getElementById("username").value;
    let pass = document.getElementById("password").value;

    window.localStorage.setItem('username',JSON.stringify(usr));

    newServices = [];
    for (let key in services) {
        if (services[key])
            newServices.push(key);
    }

    let url;

    if (id = "submitRegistration")
        url = "/register/?username=" + usr + "&password=" + pass + "&services={" + String(newServices) + "}";
    else 
        url = "/login/?username=" + usr + "&password=" + pass;


    request.open('GET', url, true);
    request.withCredentials = true;
    request.setRequestHeader("x-csrf-token", "fetch");    
    request.setRequestHeader("Accept", "application/json");
    request.setRequestHeader("Content-Type", "application/json; charset=utf-8");
    request.responseType = 'json';

    request.onload = function() {
        window.localStorage.setItem('username',JSON.stringify(usr));
        window.location.href = "/browse";
    }

    request.send();

    document.getElementById("changeDialog").innerHTML = "Information updated!";
}

function submitLogin() { // handles login page submission and redirect
    const request = new XMLHttpRequest();

    let usr = document.getElementById("username").value;
    let pass = document.getElementById("password").value;

    console.log("making get request!");

    const url = "/login/?username=" + usr + "&password=" + pass;

    request.open('GET', url, true);
    request.withCredentials = true;
    request.setRequestHeader("x-csrf-token", "fetch");    
    request.setRequestHeader("Accept", "application/json");
    request.setRequestHeader("Content-Type", "application/json; charset=utf-8");
    request.responseType = 'json';

    request.onload = function() {
        if(request.response['status']) {
            window.location.href = "/browse";
            window.localStorage.setItem('username',JSON.stringify(usr));
        }
        else
        {
            document.getElementById('loginStatus').innerHTML = "Login failed.";
            document.getElementById('loginStatus').style.display = 'block';
        }
    }

    request.send();
}