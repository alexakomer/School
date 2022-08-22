var page;
var totalPages;
var hits = {"netflixHits":0, "primeHits":0, "huluHits":0, "disneyHits":0, "hboHits":0, 
"peacockHits":0, "paramountHits":0, "starzHits":0, "showtimeHits":0, "appleHits":0, "mubiHits":0};

function requestData() {
    const request = new XMLHttpRequest();
    const searchValue = document.querySelector('input').value;
    const pageValue = $('#pageNum').val();
    const url = "/retreive/?keyword=" + searchValue + "&page=" + pageValue + "&username=" + window.localStorage.getItem("username");
    request.responseType = 'json';

    request.open('GET', url, true);

    request.addEventListener('loadstart', function () {
        document.getElementById('resultHeader').style.display = "none";
        document.getElementById("resultOutput").innerHTML = "";
        document.getElementById('resultNone').style.display = "none";
        document.getElementById('resultFooter').style.display = "none";
        document.getElementById('loading').style.display = "block";
    });

    request.onload = async function() {
        hits = {"netflixHits":0, "primeHits":0, "huluHits":0, "disneyHits":0, "hboHits":0, 
                "peacockHits":0, "paramountHits":0, "starzHits":0, "showtimeHits":0, "appleHits":0, "mubiHits":0};
        var x = await processResponse(request.response);
        updateData(hits);
    }
    
    request.send();
}

function updateData(hits) {

    const request = new XMLHttpRequest();
    request.responseType = 'json';

    const usr = window.localStorage.getItem('username');

    const url = 
    "/update/?username=" + usr + "&netflixHits=" + hits["netflixHits"] + "&primeHits=" + hits["primeHits"] + "&huluHits=" + hits["huluHits"]
    + "&disneyHits=" + hits["disneyHits"] + "&hboHits=" + hits["hboHits"] + "&peacockHits=" + hits["peacockHits"] + "&paramountHits=" + hits['paramountHits']
    + "&starzHits=" + hits["starzHits"] + "&showtimeHits=" + hits["showtimeHits"] + "&appleHits=" + hits["appleHits"] + "&mubiHits=" + hits["mubiHits"];

    request.open('GET', url, true);
    request.withCredentials = true;
    request.setRequestHeader("x-csrf-token", "fetch");    
    request.setRequestHeader("Accept", "application/json");
    request.setRequestHeader("Content-Type", "application/json; charset=utf-8");

    request.send();
}


function processResponse(response) {
    if (response['searchResults'] != null) {
        createResultList(response['searchResults'], response['userServices']);
        createSearchNav(response['page'], response['totalPages']);
        document.getElementById("resultHeader").style.display = "block";
        document.getElementById("resultFooter").style.display = "flex";
    }
    else {
        document.getElementById('resultNone').style.display = "block";
    }
    document.getElementById("loading").style.display = "none";
    document.getElementById("resultOutput").style.display = "block";

    return new Promise(resolve => {
          resolve('resolved');
      });
}

function createResultList(searchResults, userServices) {
    for (let i = 0; i < searchResults.length; i++) {
        createResultEntry(searchResults[i], userServices);
    }
}

function createResultEntry(resultIndex, userServices) {
    let watchable = false;

    const divTag = document.createElement("div"); //div
    divTag.style.display = "flex";
    divTag.style.flexWrap = "wrap";
    divTag.style.paddingBottom = "10px";

    const img = document.createElement("img");
    img.src = resultIndex['posterURLs']['185'];
    divTag.appendChild(img);

    const rightTag = document.createElement("div"); //div
    rightTag.classList.add("result");
    if (document.body.classList.contains("dark")) {
        rightTag.style.background = "rgba(255,255,255,0.05)";
    } else {
        rightTag.style.background = "rgba(255,255,255,.5)";
    }

    const nameTag = document.createElement("h3"); //h3
    let title = document.createTextNode(resultIndex['title']);
    nameTag.style.margin = "10px";
    nameTag.appendChild(title);
    rightTag.appendChild(nameTag);

    const ratingTag = document.createElement("p"); //p
    let rating = document.createTextNode('IMDB Score: ' + resultIndex['imdbRating']);
    ratingTag.style.marginLeft = "10px";
    ratingTag.style.textAlign = "left";
    ratingTag.appendChild(rating);
    rightTag.appendChild(ratingTag);

    const linkData = resultIndex['streamingInfo'];
    let linkKeys = Object.keys(linkData);
    for (const lk of linkKeys) {
        hits[String(lk) + "Hits"] += 1
        let linkTag = document.createElement("a"); //a
        linkTag.setAttribute('href', linkData[lk]['us']['link']);
        linkTag.style.marginLeft = "10px";

        linkTag.addEventListener("click", function() {
            const request = new XMLHttpRequest();
            request.responseType = 'json';
        
            const usr = window.localStorage.getItem("username");

            const url = "/click/?username=" + usr + "&clicked=" + lk + "&id=" + resultIndex['imdbID'];

            request.open('GET', url, true);
            request.withCredentials = true;
            request.setRequestHeader("x-csrf-token", "fetch");    
            request.setRequestHeader("Accept", "application/json");
            request.setRequestHeader("Content-Type", "application/json; charset=utf-8");
        
            request.send();
        });
        
        let icon = document.createElement("img");
        icon.width = "64";
        icon.height = "64";
        icon.src = "/static/webapp/src/" + lk + ".png";
        icon.alt = lk;

        let hasService = false;
        for (let service of userServices) {
            if (service == lk) {
                hasService = true;
                break;
            }
        }
        if (!hasService) {
            icon.classList.add("w3-grayscale-max");
            icon.classList.add("w3-opacity-max");
        } else {
            watchable = true;
        }

        linkTag.appendChild(icon);
        rightTag.appendChild(linkTag);
    }

    if (!watchable) {
        divTag.classList.add("w3-grayscale-max");
        divTag.classList.add("w3-opacity-max");
    }
    
    divTag.appendChild(rightTag);
    document.getElementById("resultOutput").appendChild(divTag);
}

function createSearchNav(curr, total) {
    page = parseInt(curr);
    totalPages = parseInt(total);
    document.getElementById('pageNav').innerHTML = curr + " of " + total;
    if (page == 0) {
        document.getElementById('prevPage').visibility = 'hidden';
    }
    else if (page == totalPages) {
        document.getElementById('nextPage').visibility = 'hidden';
    }
}

function prevPage() {
    let prevPage = page > 1 ? page-1 : page;
    document.getElementById('pageNum').value = prevPage;
    requestData();
}

function nextPage() {
    let nextPage = page < totalPages ? page + 1 : page;
    document.getElementById('pageNum').value = nextPage;
    requestData();
}

function updateResultColor() {
    let mode = window.localStorage.getItem('mode');
    let opacity = (mode == 'light') ? '0.5' : '0.05';
    let results = document.getElementById('resultBody').querySelectorAll('.result');
    for (let i=0; i < results.length; i++) {
        results[i].style.background = "rgba(255,255,255," + opacity + ")";
    }  
}