#include <iostream>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

int main() {
	// Initialize GLFW
	glfwInit();

	// Create a window (frameless)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // Make window frameless
	GLFWwindow* window = glfwCreateWindow(800, 600, "My Window", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwShowWindow(window);

	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	std::cout << "Window Size: (" << windowWidth << ", " << windowHeight << ")" << std::endl;

	// Setup ImGui context and bindings
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Optional: Set ImGui style
	ImGui::StyleColorsDark();

	while (!glfwWindowShouldClose(window)) {
		// Handle GLFW events
		glfwPollEvents();

		// Start a new ImGui frame
		ImGui::NewFrame();
		ImGui::SetNextWindowSize(ImVec2(400, 400));
		// Your ImGui UI code here
		ImGui::Begin("My Window");
		ImGui::Text("Hello, ImGui!");
		ImGui::End();

		// Clear screen (adjust color or use transparency if desired)
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Render ImGui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap buffers
		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

/*#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

struct account
{
	int id;
	string name;
	double balance;
	string pin;
};

// generate a random 4 digit number
int generateID() {
	srand(time(NULL));
	int id = rand() % 10000 + 1000;
	return id;
}

bool checkPin(string enteredPin, string storedPin)
{
	return enteredPin == storedPin;
}

void createAccount(vector<account>& accounts)
{
	account newaccount;
	newaccount.id = generateID();
	cout << "Enter account name: ";
	cin >> newaccount.name;
	cout << "Enter your initial balance: ";
	cin >> newaccount.balance;
	cout << "Enter your pin: ";
	cin >> newaccount.pin;
	cout << "Account created. Your account id is: " << newaccount.id << endl;
	accounts.push_back(newaccount);
};

int login(vector<account>& accounts)
{
	int accountid;
	string pin;
	cout << "Enter your account id: ";
	cin >> accountid;
	cout << "Enter your pin: ";
	cin >> pin;
	for (int i = 0; i < accounts.size(); i++)
	{
		if (accounts[i].id == accountid)
		{
			if (checkPin(pin, accounts[i].pin))
			{
				cout << "Login successful " << accounts[i].name << "!" << endl;
				return i;
			}
		}
	}
	cout << "Account can not be found. Please try again." << endl;
	return -1;
}

void deposit(account& account)
{
	double amount;
	cout << "Enter the amount you want to deposit: ";
	cin >> amount;
	account.balance += amount;
	cout << "Deposit successful. Your new balance is: " << account.balance << endl;
}

void withdraw(account& acc)
{
	double amount;
	cout << "Enter the amount you want to withdraw: ";
	cin >> amount;
	if (amount > acc.balance)
	{
		cout << "Insufficient funds. Please try again." << endl;
	}
	else {
		acc.balance -= amount;
		cout << "Withdrawal successful. Your new balance is: " << acc.balance << endl;
	}
}

void deleteAccount(vector<account>& accounts, int index)
{
	cout << "Are you sure you want to delete your account? (y/n)" << endl;
	char choice;
	cin >> choice;
	if (choice == 'y')
	{
	accounts.erase(accounts.begin() + index);
		cout << "Account deleted." << endl;
	}
	else
	{
		cout << "Account not deleted." << endl;
	}
}

void displayMenu()
{
	cout << "Please select an option:" << endl;
	cout << "1. Login" << endl;
	cout << "2. Create account" << endl;
	cout << "3. Delete account" << endl;
	cout << "4. Exit" << endl;
}

void displayAccountMenu()
{
	cout << "Please select an option:" << endl;
	cout << "1. Deposit" << endl;
	cout << "2. Withdraw" << endl;
	cout << "3. Check balance" << endl;
	cout << "4. Logout" << endl;
}

int main()
{
	system ("cls");
	vector<account> accounts;
	ifstream accountfile("accounts.txt");
	ifstream logfile("log.txt");

	int choice;
	do {
		displayMenu();
		cin >> choice;
		switch (choice)
		{
		case 1: {
			int index = login(accounts);
			if (index != -1) {
				int choice;
				do {
					system("cls");
					displayAccountMenu();
					cin >> choice;
					switch (choice) {
					case 1:
						deposit(accounts[index]);
						break;
					case 2:
						withdraw(accounts[index]);
						break;
					case 3:
						cout << "Balance: " << accounts[index].balance << endl;
						break;
					case 4:
						break;
					default:
						cout << "Invalid choice. Please try again." << endl;
						break;
					}
				} while (choice != 4);
			}
			break;
		}

		case 2: 
			createAccount(accounts);
			break;

		case 3: 
		{
			int index = login(accounts);
			if (index != -1)
			{
				deleteAccount(accounts, index);
			}
			break;
		}

		case 4: 
			cout << "Goodbye!" << endl;
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
			break;
		}
	} while (choice != 4);
	
	ofstream accountOutput("accounts.txt");
	for (int i = 0; i < accounts.size(); i++)
	{
		accountOutput << accounts[i].id << "," << accounts[i].name << "," << accounts[i].balance << "," << accounts[i].pin << endl;
	}
	accountOutput.close();

	ofstream logOutput("log.txt", ios::app);
	logOutput << "Program ended." << time(NULL) << endl;
	logOutput.close();

	return 0;
}*/