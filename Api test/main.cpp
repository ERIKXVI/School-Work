#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>

#pragma comment(lib, "wininet.lib")

int main() {
    HINTERNET hInternet = InternetOpen("MyApp", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) {
        std::cerr << "Error: Failed to open internet" << std::endl;
        return 1;
    }

    HINTERNET hUrl = InternetOpenUrl(hInternet, "https://jsonplaceholder.typicode.com/posts", NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hUrl) {
        std::cerr << "Error: Failed to open URL" << std::endl;
        InternetCloseHandle(hInternet);
        return 1;
    }

    std::string responseData;
    char buffer[1024];
    DWORD bytesRead;
    while (InternetReadFile(hUrl, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        responseData.append(buffer, bytesRead);
    }

    std::cout << responseData << std::endl;

    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);
    return 0;
}
