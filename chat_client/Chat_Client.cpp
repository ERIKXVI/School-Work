#include "./include/jdbc/mysql_driver.h"
#include "./include/jdbc/mysql_connection.h"
#include "./include/jdbc/cppconn/driver.h"
#include "./include/jdbc/cppconn/exception.h"
#include "./include/jdbc/cppconn/resultset.h"
#include "./include/jdbc/cppconn/statement.h"
#include "./include/jdbc/cppconn/prepared_statement.h"
#include <memory>
#include <iostream>
#include <string>

using namespace std;

void writeMessage(sql::Connection* con, const string& message) {
    unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO Messages (Text) VALUES (?)"));
    pstmt->setString(1, message);
    pstmt->executeUpdate();
}

void readMessages(sql::Connection* con) {
    unique_ptr<sql::Statement> stmt(con->createStatement());
    unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT Text FROM Messages"));

    while (res->next()) {
        cout << res->getString("Text") << endl;
    }
}

int main() {
    sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
    sql::Connection* con = nullptr;

    try
    {
        sql::ConnectOptionsMap connection_properties;
        connection_properties["hostName"] = "tcp://34.88.69.48:3306";
        connection_properties["userName"] = "chatclient";
        connection_properties["password"] = "Dumle2015";
        connection_properties["CLIENT_SSL_KEY"] = "/client-key.pem";
        connection_properties["CLIENT_SSL_CERT"] = "/client-cert.pem";
        connection_properties["CLIENT_SSL_CA"] = "/server-ca.pem";
        con = driver->connect(connection_properties);

    }
    catch (sql::SQLException& e) {
        std::cerr << "# ERR: SQLException in " << __FILE__;
        std::cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cerr << "# ERR: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    try {
        // Chat loop
        while (true) {
            // Display all messages
            if (con != nullptr) {
                readMessages(con);
            }

            // Get user input
            cout << "Enter a message (or 'quit' to quit): ";
            string message;
            getline(cin, message);

            // Quit if the user entered 'quit'
            if (message == "quit") {
                break;
            }

            // Write the message to the database
            if (con != nullptr) {
                writeMessage(con, message);
            }
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << ")\n";
    }

    delete con;
    return 0;
}