console.log("script loaded!!");

// get the button elements
let encryptButton = document.querySelector("#encryptButton");
let decryptButton = document.querySelector("#decryptButton");

// get the input elements
let keyInput = document.querySelector("#key");
let textInput = document.querySelector("#plain_cipher_text");
let body = document.querySelector("body");

encryptButton.addEventListener("click", async () => {
  let inputKey = keyInput.value; // extract key and text
  let plainText = textInput.value;

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
});

decryptButton.addEventListener("click", async () => {
  let inputKey = keyInput.value;
  let cipherText = textInput.value;

  console.log(inputKey, " ", cipherText);

  let response = await fetch('/decrypt',{
    method: 'POST',
    headers: {"Content-type" : 'application/json'},
    body: JSON.stringify({key: inputKey, text: cipherText})
  });

  let result = await response.json();
  
  // decrypted text
  console.log(result['plainText']);
});
