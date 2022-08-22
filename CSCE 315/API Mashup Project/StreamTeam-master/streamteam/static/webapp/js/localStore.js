// var submitButton = document.getElementById("submitButton");
// submitButton.addEventListener("click", store);
function retrieveRecords(){ //retrieves items in the localStorage
    var name = window.localStorage.getItem(username);
    console.log("retrieve records");
    var paragraph = document.createElement("p");
    var infor = document.createTextNode(name);
    paragraph.appendChild(infor);
    var element = document.getElementById("retrieve");
    element.appendChild(paragraph);
}