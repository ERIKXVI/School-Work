#include <windows.h>
#include <cwchar>

#pragma comment(lib, "ws2_32.lib") // Add this line

#define ID_USERNAME 101
#define ID_SAFE_CHAT 102
#define ID_UNSAFE_CHAT 103

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND hwndChat, hwndInput, hwndUsername, hwndSafeChat, hwndUnsafeChat;

    switch (uMsg)
    {
    case WM_CREATE:
        hwndUsername = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 10, 10, 200, 25, hwnd, (HMENU)ID_USERNAME, NULL, NULL);
        hwndSafeChat = CreateWindow(L"BUTTON", L"Join Safe Chat", WS_VISIBLE | WS_CHILD, 220, 10, 150, 25, hwnd, (HMENU)ID_SAFE_CHAT, NULL, NULL);
        hwndUnsafeChat = CreateWindow(L"BUTTON", L"Join Unsafe Chat", WS_VISIBLE | WS_CHILD, 380, 10, 150, 25, hwnd, (HMENU)ID_UNSAFE_CHAT, NULL, NULL);
        hwndChat = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY, 0, 50, 200, 100, hwnd, (HMENU)1, NULL, NULL);
        hwndInput = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL, 0, 150, 200, 50, hwnd, (HMENU)2, NULL, NULL);
        CreateWindow(L"BUTTON", L"Send", WS_VISIBLE | WS_CHILD, 0, 200, 200, 25, hwnd, (HMENU)3, NULL, NULL);
        break;
    case WM_SIZE:
        MoveWindow(hwndChat, 0, 50, LOWORD(lParam), HIWORD(lParam) - 125, TRUE);
        MoveWindow(hwndInput, 0, HIWORD(lParam) - 75, LOWORD(lParam), 50, TRUE);
        MoveWindow(GetDlgItem(hwnd, 3), 0, HIWORD(lParam) - 25, LOWORD(lParam), 25, TRUE);
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == 3)
        {
            int len = GetWindowTextLength(hwndInput) + 1;
            wchar_t* text = new wchar_t[len];
            GetWindowText(hwndInput, text, len);

            wchar_t username[256];
            GetWindowText(hwndUsername, username, 256);

            wchar_t message[512];
            swprintf(message, 512, L"%s: %s", username, text);

            // Here you can send the message to the server
            // ...

            delete[] text;
        }
        else if (LOWORD(wParam) == ID_SAFE_CHAT)
        {
            // Join safe server
            int len = GetWindowTextLength(hwndUsername) + 1;
            wchar_t* username = new wchar_t[len];
            GetWindowText(hwndUsername, username, len);

            // Initialize Winsock
            WSADATA wsaData;
            int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
            if (iResult != 0) {
                MessageBox(NULL, L"WSAStartup failed", L"Error", MB_ICONEXCLAMATION | MB_OK);
                delete[] username;
                break;
            }

            // Create a socket
            SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (ConnectSocket == INVALID_SOCKET) {
                MessageBox(NULL, L"Error at socket", L"Error", MB_ICONEXCLAMATION | MB_OK);
                WSACleanup();
                delete[] username;
                break;
            }

            // Connect to the server
            sockaddr_in clientService;
            clientService.sin_family = AF_INET;
            clientService.sin_addr.s_addr = inet_addr("192.168.0.102"); // Replace with your server's IP address
            clientService.sin_port = htons(12345); // Replace with your server's port number

            if (connect(ConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
                MessageBox(NULL, L"Failed to connect", L"Error", MB_ICONEXCLAMATION | MB_OK);
                closesocket(ConnectSocket);
                WSACleanup();
                delete[] username;
                break;
            }

            // Send the username to the server
            char buffer[512];
            size_t convertedChars = 0;
            wcstombs_s(&convertedChars, buffer, 512, username, _TRUNCATE);
            send(ConnectSocket, buffer, static_cast<int>(strlen(buffer)), 0);

            // Clean up
            delete[] username;
        }

        else if (LOWORD(wParam) == ID_UNSAFE_CHAT)
        {
            // Join unverified server
            wchar_t ip[16];
            GetWindowText(hwndInput, ip, 16);
            // Connect to the server at the entered IP address
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"ChatClient";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Chat Client", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 700, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}