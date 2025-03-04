console.log("script loaded!!");

// for the tooltip hovering part
document.addEventListener("DOMContentLoaded", function () {
  var tooltipTriggerList = [].slice.call(document.querySelectorAll('[data-bs-toggle="tooltip"]'));
  var tooltipList = tooltipTriggerList.map(function (tooltipTriggerEl) {
    return new bootstrap.Tooltip(tooltipTriggerEl);
  });
});

// get the button elements
let encryptButton = document.querySelector("#encryptButton");
let decryptButton = document.querySelector("#decryptButton");

// get the input elements
let keyInput = document.querySelector("#key");
let plainTextInput = document.querySelector("#plainText");
let cipherTextInput = document.querySelector("#cipherText");

// get the output elements
let encryptedOutput = document.querySelector("#encryptedOutput");
let decryptedOutput = document.querySelector("#decryptedOutput");

encryptButton.addEventListener("click", async () => {
  let inputKey = keyInput.value; // extract key and text
  let plainText = plainTextInput.value;

  console.log(inputKey, " ", plainText);

  // send this key and text to backend to process
  let response = await fetch("/encrypt", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ key: inputKey, text: plainText }),
  });

  // parse response from backend into a js object (hashmap basically)
  let result = await response.json();

  // encrypted text
  console.log(result["cipherText"]);

  // change the text area to display the ciphertext
  encryptedOutput.value = result["cipherText"];
});


decryptButton.addEventListener("click", async () => {
  let inputKey = keyInput.value;
  let cipherText = cipherTextInput.value;

  console.log(inputKey, " ", cipherText);

  let response = await fetch('/decrypt',{
    method: 'POST',
    headers: {"Content-type" : 'application/json'},
    body: JSON.stringify({key: inputKey, text: cipherText})
  });

  let result = await response.json();
  
  // decrypted text
  console.log(result['plainText']);

  decryptedOutput.value = result["plainText"];
});