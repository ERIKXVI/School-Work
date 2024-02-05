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
        console.log("You wake up in the back of a van, you have no idea where you are or how you got here. You look around and see that the side door is open. You can see a road and a forest.");
        rl.close();
    });
}
game();
