function passOrderValues() {
    localStorage.setItem("number", document.getElementById("id_number").value);
    localStorage.setItem("topping1", document.getElementById("id_topping1").value);
    localStorage.setItem("topping2", document.getElementById("id_topping2").value);
    localStorage.setItem("size", document.getElementById("id_size").value);
    return false;
}

function passPizzasValues() {
    localStorage.setItem("number", document.getElementById('id_number').value);
    return false;
}
