var services = {'netflix':0, 'prime':0, 'hulu':0, 'disney':0, 'hbo':0, 'peacock':0, 'paramount':0, 'starz':0, 'showtime':0, 'apple':0, 'mubi':0};


function store() {   //stores items in the localStorage
    localStorage.clear();
    var username = document.getElementById('username').value;
    window.localStorage.setItem('username',JSON.stringify(username));
}

function checkLogout() {
    if (!window.localStorage.getItem('username'))
    {
        localStorage.clear()
        window.location.href = "/";
    }
}

function checkLogin() {
    if (window.localStorage.getItem('username'))
    {
        window.location.href = "/browse";
    }
}

function getUsername() {
    var name = JSON.parse(window.localStorage.getItem('username'));
    document.getElementById("username").innerHTML = name;
  }

function signOut() {
    localStorage.clear()
    window.location.href = "/";
}

function deleteAccount() {
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

function serviceHandler(element) {
    services[element.id] = (services[element.id] + 1) % 2;
    element.classList.toggle("w3-grayscale-max");
    element.classList.toggle("w3-opacity-max");
    // console.log(services);
}

function intialize() {
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

function processServices(response) {
    let userServices = response['userServices'];
    for (let user of userServices)
    {
        services[user] = 1;
        let element = document.getElementById(user);
        // console.log(user);
        // console.log(element);
        element.classList.toggle("w3-grayscale-max");
        element.classList.toggle("w3-opacity-max");
        // console.log(element);
    }
    // services
}

function submitServices() {
    const request = new XMLHttpRequest();
    const usr = window.localStorage.getItem('username');

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

    request.send();

    document.getElementById("changeDialog").innerHTML = "Information updated!";
}

function submitRegistrationServices() {
    const request = new XMLHttpRequest();

    let usr = document.getElementById("username").value;
    let pass = document.getElementById("password").value;

    window.localStorage.setItem('username',JSON.stringify(usr));

    newServices = [];
    for (let key in services) {
        if (services[key])
            newServices.push(key);
    }

    console.log("making get request!");

    const url = "/register/?username=" + usr + "&password=" + pass + "&services={" + String(newServices) + "}";

    request.open('GET', url, true);
    request.withCredentials = true;
    request.setRequestHeader("x-csrf-token", "fetch");    
    request.setRequestHeader("Accept", "application/json");
    request.setRequestHeader("Content-Type", "application/json; charset=utf-8");
    request.responseType = 'json';

    request.onload = function() {
        window.location.href = "/browse";
    }

    request.send();

    document.getElementById("changeDialog").innerHTML = "Information updated!";
}