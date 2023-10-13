const { Console } = require('console');
var mysql = require('mysql2');

var con = mysql.createConnection({
  host: "127.0.0.1",
  user: "root",
  password: "Dumle2015",
  database: "MySQL80",
  port: "3307"
});

con.connect(function(err) {
  if (err) {
    console.error('Error connecting to the database: ' + err.message);
    throw err;
  }

  console.log("Connected!");

  con.query("USE MySQL80", function (err, result) {
    if (err) {
      console.error('Error selecting the database: ' + err.message);
      throw err;
    }

    console.log("Database selected.");

    con.query("SHOW TABLES LIKE 'dogs'", function (err, result) {
      if (err) {
        console.error('Error checking if the table exists: ' + err.message);
        throw err;
      }

      if (result.length === 0) {
        var createTableSQL = "CREATE TABLE dogs (name VARCHAR(255), Race VARCHAR(255))";
        
        con.query(createTableSQL, function (err, result) {
          if (err) {
            console.error('Error executing the query to create the table: ' + err.message);
            throw err;
          }

          console.log("Table 'dogs' created successfully.");
        });
      } else {
        console.log("Table 'dogs' already exists, skipping creation.");
      }

const readline = require("readline");

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
})

    console.log("Welcome!", "\n", "1. Add Dogs", "\n", "2.Remove A dog", "\n", "3.list all dogs", "\n", "4.exit")

    rl.question("Select an option (1/2/3/): ", (choice) => {
        switch (choice) {
            case "1":
                rl.question("Enter the dog\'s name: ", (name) => {
                    rl.question("Enter the dog\'s race: ", (race) => {
                        const insertDogSQL = "INSERT INTO dogs (name, race) VALUES (?, ?)";
                        con.query(insertDogSQL, [name, race], (err, result) => {
                            if (err) {
                                console.error("Error inserting dog data: " + err.message);
                                throw err;
                            }
                            console.log("Dog data inserted successfully.");
                        });
                        rl.close();
                    });
                });
            break;
        case "2":
            rl.question("Enter the name of the dog you want to remove: ", (name) => {
                const deleteDogSQL = "DELETE FROM dogs WHERE name = ?";
                con.query(deleteDogSQL, [name], (err, result) => {
                    if (err) {
                        console.error("Error removing the dog: " + err.message);
                        throw err;
                    }
                    Console.log("Dog removed successfully.");
                });
                rl.close();
            })
            break;
        case "3":
           const selectAllDogsSQL = "SELECT * FROM dogs";
           con.query(selectAllDogsSQL, (err, result) => {
            if (err) {
                console.error("Error fetching dogs: " + err.message);
                throw err;
            }

            if (resourceLimits.length === 0) {
                console.log("No dogs found.");
            } else {
                console.log("List of dogs:");
                resourceLimits.forEach((dog) => {
                    console.log("Name: ${dog.name}, Race: ${dog.Race}");
                });
            }
            rl.close();
           })
           break;
           case "4":
            console.log("Quiting the program.");
            con.end(function(err) {
                if (err) {
                    console.error("Error closing the database connection: " + err.message);
                }
                console.log("Connection closed.");
            })
            rl.close();
            break
            default:
                console.log("Invalid choice.");
                rl.close();
        }
    });
});
