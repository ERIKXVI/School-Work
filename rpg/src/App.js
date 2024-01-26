"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var readline = require("readline");
var health = 100;
var dmg = 0;
function game() {
    console.clear();
    console.log("Welcome to this rpg game!");
    var rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout
    });
    rl.question("What is your name? ", function (name) {
        console.clear();
        console.log("Welcome ".concat(name, "!"));
        rl.close();
    });
}
game();
