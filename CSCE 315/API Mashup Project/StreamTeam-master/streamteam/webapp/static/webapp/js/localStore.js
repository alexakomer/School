function retrieveRecords(){ //retrieves items in the localStorage
    var name = window.localStorage.getItem(username);
    var paragraph = document.createElement("p");
    var infor = document.createTextNode(name);
    paragraph.appendChild(infor);
    var element = document.getElementById("retrieve");
    element.appendChild(paragraph);
}