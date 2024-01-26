import * as readline from 'readline';

let health = 100;
let dmg = 0;

function game () {
    console.clear();
    console.log("Welcome to this rpg game!");

    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout
    });

    rl.question("What is your name? ", (name: string) => {
        console.clear();
        console.log(`Welcome ${name}!`);
        rl.close();
    });

    console.log("You wake up in the back of a van, you have no idea where you are or how you got here. You look around and see that the side door is open. You can see a road and a forest.");

}

game();