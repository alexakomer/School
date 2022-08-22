/* Common */
function clickMode() {
    let mode = window.localStorage.getItem('mode');
    toggleMode(mode);
}

function toggleMode(mode) {
    let element = document.getElementById('mode');
    if (mode == 'dark') {
        element.innerHTML = '<i>LIGHT</i>';
        window.localStorage.setItem('mode','light');
    } else {
        element.innerHTML = '<i>DARK</i>';
        window.localStorage.setItem('mode','dark');
    }
    document.body.classList.toggle("dark");
    document.getElementById('navbar').classList.toggle("dark");
    document.getElementById('top-navbar').classList.toggle("dark");
    document.getElementById('sidebar').classList.toggle("dark");
    document.getElementById('foot').classList.toggle("dark");
    document.getElementById('wrapper').classList.toggle("dark");
    document.getElementById('loading').classList.toggle("dark");
}

function checkDisplayBrowse() {
    if (window.localStorage.getItem('username'))
    {
        document.getElementById("login").innerHTML = "BROWSE";
    }
}

function setMode() {
    let mode = window.localStorage.getItem('mode');
    if (!mode){ 
        window.localStorage.setItem('mode','dark');
    } else {
        if (mode == 'light') {
            toggleMode('dark');
        }
    }
}

function googleTranslateElementInit() {
    new google.translate.TranslateElement({pageLanguage: 'en', layout: google.translate.TranslateElement.InlineLayout.SIMPLE}, 'google_translate_element');
}

function openModal(id) {
    document.getElementById(id).style.display='block';
}

function closeModal(id) {
    document.getElementById(id).style.display='none';
}

function toggleNav() { // Toggle between showing and hiding the sidebar when clicking the menu icon
    const sidebar = document.getElementById("sidebar");
    if (sidebar.style.display === 'block') {
        sidebar.style.display = 'none';
    } else {
        sidebar.style.display = 'block';
    }
}

function closeNav() { // Close the sidebar with the close button
    const sidebar = document.getElementById("sidebar");
    sidebar.style.display = "none";
}

function accountLoad() {
    intialize();
    checkLogout();
    setMode();
    getUsername();
}

function analyticsLoad() {
    checkLogout();
    setMode();
    requestInfo();
    document.getElementById("startTab").click();
}

function browseLoad() {
    checkLogout();
    setMode();
    setGreeting();
    requestRecommendations();
}

function landingLoad() {
    checkDisplayBrowse();
    setMode();
}

function loginLoad() {
    checkLogin();
    setMode();
}

function registerLoad() {
    checkLogin();
    setMode();
}

function searchLoad() {
    checkLogout();
    setMode();
    const button = document.getElementById('goButton');
    button.addEventListener('click', function(event) {
        event.preventDefault();
        requestData();
    });
}