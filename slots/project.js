const prompt = require("prompt-sync")();

const ROWS = 3;
const COLS = 3;

const SYMPOLS_COUNT = {
    "A": 2,
    "B": 4,
    "C": 6,
    "D": 8
}

const SYMPOLS_VALUES = {
    "A": 5,
    "B": 4,
    "C": 3,
    "D": 2
}

const deposit = () => {
    while (true) {
        const depositAmount = prompt("Enter a deposit Amount: ");
        const numberDepositAmount = parseFloat(depositAmount);

        if (isNaN(numberDepositAmount) || numberDepositAmount <= 0) {
            console.log("Invalid deposit amount, please try again.")
        } else {
            return numberDepositAmount;
        }  
    }
};

const getNumberOfLines = () => {
    while (true) {
        const Lines = prompt("Enter the number of lines to bet on (1-3): ");
        const numberOfLines = parseFloat(Lines);

        if (isNaN(numberOfLines) || numberOfLines <= 0 || numberOfLines > 3) {
            console.log("Invalid number of lines, please try again.")
        } else {
            return numberOfLines;
        }  
    }
};

const getbet = (balance, lines) => {
    while (true) {
        const bet = prompt("Enter the bet per line: ");
        const numberbet = parseFloat(bet);

        if (isNaN(numberbet) || numberbet <= 0 || numberbet > balance / lines) {
            console.log("Invalid bet, please try again.")
        } else {
            return numberbet;
        }  
    }
}

const spin = () => {
    const symbols = [];
    for (const [symbol, count] of Object.entries(SYMPOLS_COUNT)) {
        for (let i = 0; i < count; i++) {
            symbols.push(symbol);
        }
    }

    const reels = [];
    for (let i = 0; i < COLS; i++) {
        reels.push([]);
        const reelSymbols = [...symbols];
        for (let j = 0; j < ROWS; j++) {
            const randomIndex = Math.floor(Math.random() * reelSymbols.length);
            const selectedSymbol = reelSymbols[randomIndex];
            reels[i].push(selectedSymbol);
            reelSymbols.splice(randomIndex, 1);
        }
    }
    return reels;
}

const transpose = (reels) => {
    const rows = [];

    for (let i = 0; i < ROWS; i++) {
        rows.push([]);
        for (let j = 0; j < COLS; j++) {
            rows[i].push(reels[j][i]);
        }
    }
    return rows;
}

const printRows = (rows) => {
    for (const row of rows) {
        let rowString = "";
        for (const [i, symbol] of row.entries()) {
            rowString+= symbol
            if (i != row.length -1) {
                rowString += " | "
            }
        }
        console.log(rowString)
    }
}

const getWinnings = (rows, bet, lines) => {
    let winings = 0;
    
    for (let row = 0; row < lines; row++) {
        const symbols = rows[row];
        let allSame = true;

        for (const symbol of symbols) {
            if (symbol != symbols[0]) {
                allSame = false;
                break;
            }
        }

        if (allSame) {
            winings += bet * SYMPOLS_VALUES[symbols[0]]
        }
    }

    return winings;
}

const game = () => {
    let balance = deposit()

    while (true) {
    console.log("Your balance is $" + balance)
    const numberOfLines = getNumberOfLines()
    const bet = getbet(balance, numberOfLines);
    balance -= bet * numberOfLines;
    const reels = spin()
    const rows = transpose(reels)
    printRows(rows);
    const winnings = getWinnings(rows, bet, numberOfLines)
    balance += winnings;
    console.log("You won, $" + winnings.toString());

    if (balance <= 0) {
        console.log("Your broke go kill yourself")
        break
    } 

    const playAgain = prompt("Do you wanna play again? (y/n) ")

    if (playAgain != "y") break;
    }
}

game()