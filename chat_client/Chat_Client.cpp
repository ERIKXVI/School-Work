#include "./include/jdbc/mysql_driver.h"
#include "./include/jdbc/mysql_connection.h"
#include "./include/jdbc/cppconn/driver.h"
#include "./include/jdbc/cppconn/exception.h"
#include "./include/jdbc/cppconn/resultset.h"
#include "./include/jdbc/cppconn/statement.h"
#include <iostream>
#include <string>

using namespace std;

sql::mysql::MySQL_Driver* driver;
sql::Connection* con;

void writeMessage(const string& message) {
    unique_ptr<sql::Statement> stmt(con->createStatement());
    stmt->execute("INSERT INTO Messages (Text) VALUES ('" + message + "')");
}

void readMessages() {
    unique_ptr<sql::Statement> stmt(con->createStatement());
    unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT Text FROM Messages"));

    while (res->next()) {
        cout << res->getString("Text") << endl;
    }
}

int main() {
    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://<Cloud_SQL_Instance_IP>:3306", "<username>", "<password>");
        con->setSchema("<database_name>");
    }
    catch (sql::SQLException& e) {
        cerr << "Failed to connect to the database. Error: " << e.what() << endl;
        return 1; // Return an error code
    }

    // Chat loop
    while (true) {
        // Display all messages
        readMessages();

        // Get user input
        cout << "Enter a message (or 'quit' to quit): ";
        string message;
        getline(cin, message);

        // Quit if the user entered 'quit'
        if (message == "quit") {
            break;
        }

        // Write the message to the database
        writeMessage(message);
    }

    delete con;
    return 0;
}