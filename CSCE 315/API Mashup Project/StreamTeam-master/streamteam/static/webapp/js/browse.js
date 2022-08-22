var userServices;
var pageTS = 1;
var pageLT = 1;
var maxTS = 6;
var maxLT = 4;

function setGreeting() { // TODO: update to better
    const name = JSON.parse(window.localStorage.getItem('username'));
    document.getElementById("welcome").innerHTML = "Welcome, " + name + "!";
}

function requestRecommendations() {
    const request = new XMLHttpRequest();
    const usr = window.localStorage.getItem('username');
    const url = "/recommend/?username=" + usr + "&pageTS=" + pageTS + "&pageLT=" + pageLT;
    request.responseType = 'json';

    request.open('GET', url, true);

    request.addEventListener('loadstart', function () {
        document.getElementById('recommendations').style.display = "none";
        document.getElementById('loading').style.display = "block";
    });

    request.onload = function() {
        processRecommendations(request.response);
    }

    request.send();
}

function processRecommendations(response) {
    userServices = response['userServices'];
    // createCarousel(response['topMovies'],'tm');
    createCarousel(response['topShows'], 'ts');
    // createCarousel(response['topByGenre'],true);
    createCarousel(response['moreLikeThis'], 'lt');

    document.getElementById('recommendations').style.display = "block";
    document.getElementById('loading').style.display = "none";
}

function createCarousel(data, idtag) {
    for (let i=0; i < 5; i++) {
        let id = idtag + '-' + i.toString();
        const elem = document.getElementById(id);
        elem.src = data[i]['posterURLs']['185'];
        elem.setAttribute("data-content",JSON.stringify(data[i]));
        //console.log(elem.getAttribute("data-content"));
    }
}

function onSelect(element) {
    let data = JSON.parse(element.getAttribute('data-content'));
    document.getElementById("poster").src = element.src;
    document.getElementById("titleModal").style.display = "block";
    let title = document.getElementById("title");
    title.innerHTML = data.title;
    let rating = document.getElementById("rating");
    rating.innerHTML = "IMDB Rating: " + data.imdbRating;
    let description = document.getElementById("description");
    description.innerHTML = data.overview;
    let linkData = data.streamingInfo;
    let html = "";
    for (let key of Object.keys(linkData)) {
        let href = "href='" + linkData[key]['us']['link'] + "'";
       
        let hasService = false;
        for (let service of userServices) {
            if (service == key) {
                hasService = true;
                break;
            }
        }
        let css = (!hasService) ? "class='w3-grayscale-max w3-opacity-max' " : "";

        let img = "<img src='" + "/static/webapp/src/" + key + ".png' " + css + "style='width:64px;height:64px'>";
        html += "<a " + href + ">" + img + "</a>";
    }
    // console.log("html: " + html);
    document.getElementById('services').innerHTML = html;
  }

function nextPageTS() {
    pageTS = (pageTS+1) % maxTS;
    requestRecommendations();
}

function prevPageTS() {
    pageTS = (pageTS == 1) ? maxTS-1 : pageTS-1;
    console.log(pageTS);
    requestRecommendations();
}

function nextPageLT() {
    pageLT = (pageLT+1) % maxLT;
    requestRecommendations();
}

function prevPageLT() {
    pageLT = (pageLT == 1) ? maxPage-1 : maxLT-1;
    requestRecommendations();
}