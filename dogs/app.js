const mysql = require('mysql2');
const readline = require('readline');
const { clearConsole } = require('console-clear');

var con = mysql.createConnection({
  host: "",
  user: "",
  password: "",
  database: "",
  port: ""
});

con.connect(function (err) {
  if (err) {
    console.error('Error connecting to the database: ' + err.message);
    throw err;
  }

  console.log('Connected!');

  con.query('USE MySQL80', function (err, result) {
    if (err) {
      console.error('Error selecting the database: ' + err.message);
      throw err;
    }

    console.log('Database selected.');

    con.query('SHOW TABLES LIKE "dogs"', function (err, result) {
      if (err) {
        console.error('Error checking if the table exists: ' + err.message);
        throw err;
      }

      if (result.length === 0) {
        var createTableSQL = 'CREATE TABLE dogs (name VARCHAR(255), race VARCHAR(255))';

        con.query(createTableSQL, function (err, result) {
          if (err) {
            console.error('Error executing the query to create the table: ' + err.message);
            throw err;
          }

          console.log('Table "dogs" created successfully');
          startMainMenu();
        });
      } else {
        console.log('Table "dogs" already exists, skipping creation.');
        startMainMenu();
      }
    });
  });
});

function startMainMenu() {
  const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });

  console.log('Welcome!\n1. Add Dogs\n2. Remove A dog\n3. List all dogs\n4. Exit');

  rl.question('Select an option (1/2/3/4): ', (choice) => {
    switch (choice) {
      case '1':
        rl.question("Enter the dog's name: ", (name) => {
          rl.question("Enter the dog's race: ", (race) => {
            const insertDogSQL = 'INSERT INTO dogs (name, race) VALUES (?, ?)';
            con.query(insertDogSQL, [name, race], (err, result) => {
              if (err) {
                console.error('Error inserting dog data: ' + err.message);
                throw err;
              }
              console.log('Dog data inserted successfully.');
              clearConsole();
              promptReturnToMainMenu(rl);
            });
          });
        });
        break;
      case '2':
        rl.question('Enter the name of the dog you want to remove: ', (name) => {
          const deleteDogSQL = 'DELETE FROM dogs WHERE name = ?';
          con.query(deleteDogSQL, [name], (err, result) => {
            if (err) {
              console.error('Error removing the dog: ' + err.message);
              throw err;
            }
            console.log('Dog removed successfully.');
            clearConsole();
            promptReturnToMainMenu(rl);
          });
        });
        break;
      case '3':
        const selectAllDogsSQL = 'SELECT * FROM dogs';
        con.query(selectAllDogsSQL, (err, result) => {
          if (err) {
            console.error('Error fetching dogs: ' + err.message);
            throw err;
          }

          if (result.length === 0) {
            console.log('No dogs found.');
          } else {
            console.log('List of dogs:');
            result.forEach((dog) => {
              console.log(`Name: ${dog.name}, Race: ${dog.race}`);
            });
          }
          clearConsole();
          promptReturnToMainMenu(rl);
        });
        break;
      case '4':
        console.log('Quitting the program.');
        con.end(function (err) {
          if (err) {
            console.error('Error closing the database connection: ' + err.message);
          }
          console.log('Connection closed.');
          rl.close();
        });
        break;
      default:
        console.log('Invalid choice.');
        clearConsole();
        promptReturnToMainMenu(rl);
    }
  });
}

function promptReturnToMainMenu(rl) {
  rl.question('Return to the main menu? (yes/no): ', (answer) => {
    if (answer.toLowerCase() === 'yes') {
      clearConsole();
      startMainMenu();
    } else {
      console.log('Goodbye!');
      rl.close();
    }
  });
}