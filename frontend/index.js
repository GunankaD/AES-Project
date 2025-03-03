console.log("script loaded!!");

let encryptButton = document.querySelector("#encryptButton");
let decryptButton = document.querySelector("#decryptButton");

let keyInput = document.querySelector("#key");
let textInput = document.querySelector("#plain_cipher_text");
let body = document.querySelector("body");

encryptButton.addEventListener("click", () => {
  let key = keyInput.value;
  let plainText = textInput.value;
  
   // console.log(key, " ", plainText);
});

decryptButton.addEventListener("click", () => {
  let key = keyInput.value;
  let cipherText = textInput.value;

   // console.log(key, " ", cipherText);
});
