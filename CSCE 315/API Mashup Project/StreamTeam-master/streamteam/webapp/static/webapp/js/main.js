/* Common */
function clickMode() {
    let mode = window.localStorage.getItem('mode');
    toggleMode(mode);
}

function toggleMode(mode) { // toggle dark mode on and off
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
    try {
        document.getElementById('modal').classList.toggle("dark");
    } catch(Exception){
        // ignore
    }

}

function checkDisplayBrowse() { // prompt users to skip login with local storage
    if (window.localStorage.getItem('username'))
    {
        document.getElementById("login").innerHTML = "BROWSE";
    }
}

function setMode() { // toggle dark mode with persistent storage
    let mode = window.localStorage.getItem('mode');
    if (!mode){ 
        window.localStorage.setItem('mode','dark');
    } else {
        if (mode == 'light') {
            toggleMode('dark');
        }
    }
}

function googleTranslateElementInit() { // create google translate button
    new google.translate.TranslateElement({pageLanguage: 'en', layout: google.translate.TranslateElement.InlineLayout.SIMPLE}, 'google_translate_element');
}

function openModal(id) { // display modal
    document.getElementById(id).style.display='block';
}

function closeModal(id) { // hide modal
    document.getElementById(id).style.display='none';
}

function toggleNav() { // toggle between showing and hiding the sidebar when clicking the menu icon
    const sidebar = document.getElementById("sidebar");
    if (sidebar.style.display === 'block') {
        sidebar.style.display = 'none';
    } else {
        sidebar.style.display = 'block';
    }
}

function closeNav() { // close the sidebar with the close button
    const sidebar = document.getElementById("sidebar");
    sidebar.style.display = "none";
}

function accountLoad() { // onload for account
    intialize();
    checkLogout();
    setMode();
    getUsername();
    checkTranslate();
}

function analyticsLoad() { // onload for analytics
    checkLogout();
    setMode();
    requestInfo();
    document.getElementById("startTab").click();
    checkTranslate();
}

function browseLoad() { // onload for browse
    checkLogout();
    setMode();
    setGreeting();
    requestRecommendations();
    checkTranslate();
}

function landingLoad() { // onload for landing
    checkDisplayBrowse();
    setMode();
    checkTranslate();
}

function loginLoad() { // onload for login
    checkLogin();
    setMode();
    checkTranslate();
}

function registerLoad() { // onload for register
    checkLogin();
    setMode();
    checkTranslate();
}

function searchLoad() { // onload for search
    checkLogout();
    setMode();
    const button = document.getElementById('goButton');
    button.addEventListener('click', function(event) {
        event.preventDefault();
        requestData();
    });
    checkTranslate();
}

function checkTranslate() { // check language
    document.addEventListener('DOMSubtreeModified', function(e) {
        if (e.target.tagName === 'HTML' && window.google) {
            if (e.target.className.match('translated'))
                document.getElementById('navbar').classList.add('translateBar');
            else
                document.getElementById('navbar').classList.remove('translateBar');
        }
    }, true);
}